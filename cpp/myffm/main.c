#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_syswm.h>

#include <GL/glew.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <vdpau/vdpau_x11.h>
#include "vdpauDecoderContext.h"

#define SDL_AUDIO_BUFFER_SIZE 1024;

static bool glslsupport;
static GLuint texture;
Display *m_dpy;
Window win;
GLXWindow m_glWindow;
GLXContext m_glContext;
SDL_Surface *m_SDLSurface;

#define HISTORY_VIDEO_SURFACE_NUM 18
#define VIDEO_SURFACE_NUM 5 

VdpDevice vdpDevice;
VdpDecoder vdp_decoder;
VdpVideoMixer vdp_videoMixer;

int vdp_pixfmt = -1;
int vdp_width = 0;
int vdp_height = 0;
int ip_age[2];
int b_age;

struct vdpau_render_state surface_render[VIDEO_SURFACE_NUM]; //18
VdpVideoSurface history_surface[HISTORY_VIDEO_SURACE_NUM]; //5

int vdp_surface_render_index = 0;

typedef struct PacketQueue
{
	AVPacketList *first_pkt, *last_pkt;
	int nb_packets;
	int size;//+=packet->size
	SDL_mutex *mutex;
	SDL_cond *cond;
} PacketQueue;

static PacketQueue audioq;

void packet_queue_init(PacketQueue *q)
{
	memset(q, 0, sizeof(PacketQueue));
	q->mutex = SDL_CreateMutex();
	q->cond = SDL_CreateCond();
}

int packet_queue_put(PacketQueue *q, AVPacket *pkt)
{
	AVPacketList *pkt1;
	if(av_dup_packet(pkt) < 0)
	{
		fprintf(stderr, "dup packet filed\n");
		return -1;
	}
	pkt1 = av_malloc(sizeof(AVPacketList));
	pkt1->pkt = *pkt;
	pkt1->next = NULL;
	SDL_LockMutex(q->mutex);
	if(!q->last_pkt)
		q->first_pkt = pkt1;
	else
		q->last_pkt->next = pkt1;
	q->last_pkt = pkt1;
	q->nb_packets++;
	q->size += pkt1->pkt.size;
	SDL_CondSignal(q->cond);
	SDL_UnlockMutex(q->mutex);
	return 0;	
}
static int quit = 0;
static int packet_queue_get(PacketQueue *q, AVPacket *pkt, int block)
{
	AVPacketList *pkt1;
	int ret;
	SDL_LockMutex(q->mutex);
	while(1)
	{
		if(quit)
		{
			ret = -1;
			break;
		}
		pkt1 = q->first_pkt;
		if(pkt1)
		{
			q->first_pkt = pkt1->next;
			if(!q->first_pkt)
				q->last_pkt = NULL;
			q->nb_packets--;
			q->size -= pkt1->pkt.size;
			*pkt = pkt1->pkt;
			av_free(pkt1);
			ret = 1;
			break;
		}
		else if(!block)
		{
			ret = 0;
			break;
		}
		else
			SDL_CondWait(q->cond, q->mutex);
	}
	SDL_UnlockMutex(q->mutex);
	return ret;
}

int audio_decode_frame(AVCodecContext *aCodecCtx, AVPacket *pkt, AVPacket *pkt_temp, AVFrame *frame, uint8_t *audio_buf)
{
	int len1, data_size;
	int got_frame = 0;
	int new_packet = 0;

	while(1)
	{
		while(pkt_temp->size > 0 || (!pkt_temp->data && new_packet))
		{
			if(!frame)
			{
				if(!(frame = avcodec_alloc_frame()))
					return AVERROR(ENOMEM);
			}
			else
			{
				avcodec_get_frame_defaults(frame);
			}
			new_packet = 0;
			got_frame = 0;
			len1 = avcodec_decode_audio4(aCodecCtx, frame, &got_frame, pkt_temp);
			if(len1 < 0)
			{
				/*if error, skip frame*/
				pkt_temp->size = 0;
				av_free_packet(pkt_temp);
				continue;
			}
			pkt_temp->data += len1;
			pkt_temp->size -= len1;
			if(!got_frame)
			{
				/*stop sending empty packets if the decoder is finished*/
				continue;
				//break;
			}
			data_size = av_samples_get_buffer_size(NULL, aCodecCtx->channels, frame->nb_samples, aCodecCtx->sample_fmt, 1);
			memcpy(audio_buf, frame->data[0], frame->linesize[0]);
			return data_size;
		}
		if(pkt->data)
			av_free_packet(pkt);
		memset(pkt_temp, 0, sizeof(*pkt_temp));
		if(quit)
		{
			return -1;
		}
		if((new_packet = packet_queue_get(&audioq, pkt, 1)) < 0)
		{
			return -1;
		}
		*pkt_temp = *pkt;
	}
}

void audio_callback(void *userdata, uint8_t *stream, int len)
{
	AVCodecContext *aCodecCtx;
	aCodecCtx = (AVCodecContext*)userdata;
	int len1, audio_size;
	static uint8_t audio_buf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2];
	static unsigned int audio_buf_size = 0;
	static unsigned int audio_buf_index = 0;
	AVPacket *pkt = av_mallocz(sizeof(AVPacket));
	AVPacket *pkt_temp = av_mallocz(sizeof(AVPacket));
	AVFrame *frame = NULL;
	while(len > 0)
	{
		if(audio_buf_index >= audio_buf_size)
		{
			/*we have already sent all our data; get more */
			audio_size = audio_decode_frame(aCodecCtx, pkt, pkt_temp, frame, audio_buf);
			if(audio_size < 0)
			{
				/*if error, output silence*/
				audio_buf_size = 1024;
				memset(audio_buf, 0, audio_buf_size);
			}
			else
			{
				audio_buf_size = audio_size;	
			}
			audio_buf_index = 0;
		}
		len1 = audio_buf_size - audio_buf_index;
		if(len1 > len)
			len1 = len;
		memcpy(stream, (uint8_t*)audio_buf + audio_buf_index, len1);
		len -= len1;
		stream += len1;
		audio_buf_index += len1;
	}
}

int decode_interrupt_cb(void)
{
	return quit;
}

void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame)
{
	FILE *pFile;
	char szFilename[32] = {0};
	int y;
	//Open file
	sprintf(szFilename, "./ppm/frame%d.ppm", iFrame);
	printf("write to file: %s\n", szFilename);
	pFile = fopen(szFilename, "wb");
	if(pFile == NULL)
	{
		perror("open file error\n");
		return;
	}
	//Write header
	fprintf(pFile, "P6\n%d %d\n255\n", width, height);
	//Write pixel data
	for(y = 0; y < height; y++)
		fwrite(pFrame->data[0] + y * pFrame->linesize[0], 1, width * 3, pFile);
	//Close file
	fclose(pFile);
}

static GLuint texture;
void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);// 清屏为黑色
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)640/(float)480,0.1f,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearDepth(1.0f);													// 设置深度缓存
	glEnable(GL_DEPTH_TEST);											// 开启深度测试
	glDepthFunc(GL_LEQUAL);												// 选择深度测试方式
	glShadeModel(GL_SMOOTH);											// 阴暗处理采用平滑方式
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);					// 最精细的透视计算
	glGenTextures(1,&texture);
	glEnable(GL_TEXTURE_2D);
}

int main(int argc ,char **argv)
{
	av_register_all();
	AVFormatContext *pFormatCtx = NULL;
	AVInputFormat *file_iformat = NULL;
	
	//avio_set_interrupt_cb(decode_interrupt_cb);	
	//Open video file
	printf("open video file:%s\n", argv[1]);
	if(avformat_open_input(&pFormatCtx, argv[1], file_iformat, NULL) < 0)
	{
		printf("canot open input file: %s\n", argv[1]);
		return -1; //Cannot open file
	}
	printf("open input file: %s OK\n", argv[1]);
	//Retrieve stream information
	if(av_find_stream_info(pFormatCtx) < 0)
		return -1;//cannot find stream infomation
	//Dump information about file no to standard error
	av_dump_format(pFormatCtx, 0, argv[1], 0);

	int i;
	int videoStream;
	int audioStream;
	videoStream = -1;
	audioStream = -1;
	AVCodecContext *vCodecCtx;
	AVCodecContext *aCodecCtx;
	//Find the first video stream
	for(i = 0; i < pFormatCtx->nb_streams; i++)
	{
		if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO && videoStream < 0) 
		{
			videoStream = i;
		}
		if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO && audioStream < 0)
		{
			audioStream = i;	
		}
	}
	if(videoStream == -1)
	{
		printf("no video stream\n");
		return -1;//Did not find a video stream
	}
	if(audioStream == -1)
	{
		printf("no audio stream\n");
		return -1;//Did not find a audio stream
	}
	printf("find video strean: %d\n", videoStream);
	printf("find audio strean: %d\n", audioStream);

	//Get a pointer to the codec context for the video stream
	vCodecCtx = pFormatCtx->streams[videoStream]->codec;
	//set vCodecCtx for vdpau
	vCodecCtx->get_format = decoder_get_format;
	vCodecCtx->get_buffer = decoder_get_buffer;
	vCodecCtx->release_buffer = decoder_release_buffer;
	vCodecCtx->draw_horiz_band = decoder_draw_horiz_band;
	vCodecCtx->reget_buffer = decoder_get_buffer;
	vCodecCtx->slice_flags = SLICE_FLAG_CODEC_ORDER | SLICE_FLAG_ALLOW_FIELD;

	AVCodec *vCodec;
	vCodec = avcodec_find_decoder(vCodecCtx->codec_id);
	if(vCodec == NULL)
	{
		fprintf(stderr, "Unsupported video codec\n");
		return -1;//codec not find
	}
	//Open video codec
	if(avcodec_open(vCodecCtx, vCodec) < 0)
	{
		fprintf(stderr, "open video codec error\n");
		return -1;//Could not open codec
	}

	

	//Get a pointer to the codec context for the audio stream
	aCodecCtx = pFormatCtx->streams[audioStream]->codec;
	static SDL_AudioSpec wanted_spec, spec;
	wanted_spec.freq = aCodecCtx->sample_rate;
	wanted_spec.format = AUDIO_S16SYS;
	wanted_spec.channels = aCodecCtx->channels;
	wanted_spec.silence = 0;
	wanted_spec.samples = SDL_AUDIO_BUFFER_SIZE;
	wanted_spec.callback = audio_callback;
	wanted_spec.userdata = aCodecCtx;
	if(SDL_OpenAudio(&wanted_spec, &spec) < 0)
	{	
		fprintf(stderr, "SDL_OpenAudio: %s\n", SDL_GetError());
		return -1;
	}
	AVCodec *aCodec;
	aCodec = avcodec_find_decoder(aCodecCtx->codec_id);
	if(aCodec == NULL)
	{
		fprintf(stderr, "Unsupport audio codec\n");
		return -1;//codec not found
	}
	if(avcodec_open(aCodecCtx, aCodec) < 0)
	{
		fprintf(stderr, "open avcodec error\n");
		return -1;
	}
	packet_queue_init(&audioq);
	SDL_PauseAudio(0);

	AVFrame *pFrame;
	//Allocate video frame
	pFrame = avcodec_alloc_frame();
	AVFrame *pFrameRGB;
	//Allocate an AVFrame structure
	pFrameRGB = avcodec_alloc_frame();
	if(pFrameRGB == NULL)
		return -1;
	uint8_t *buffer;
	int numBytes;
	//Detemine required buffer size and allocate buffer
	numBytes = avpicture_get_size(PIX_FMT_RGB24, vCodecCtx->width, vCodecCtx->height);
	buffer = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t));
	//Assign appropriate parts of buffer to image planes in pFrameRGB
	//Note that pFrameRGB is an AVFrame, but AVFrame is a superset
	//of AVPicture
	avpicture_fill((AVPicture*)pFrameRGB, buffer, PIX_FMT_RGB24, vCodecCtx->width, vCodecCtx->height);
	
	if((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)))
	{
		fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
		exit(1);
	}
	SDL_Surface *screen;
	screen = SDL_SetVideoMode(vCodecCtx->width, vCodecCtx->height, 0, 0);
	if(!screen)
	{
		fprintf(stderr, "SDL: could not set video mode\n");
		exit(1);
	}
	SDL_Overlay *bmp;
	bmp = SDL_CreateYUVOverlay(vCodecCtx->width, vCodecCtx->height, SDL_YV12_OVERLAY, screen);

	int frameFinished;
	AVPacket packet;
	SDL_Rect rect;
	i = 0;
	while(av_read_frame(pFormatCtx, &packet) >=0)
	{
		//is this a packet from video stream?
		if(packet.stream_index == videoStream)
		{
			//Decoder video frame
			avcodec_decode_video2(vCodecCtx, pFrame, &frameFinished, &packet);
			//Did we got a video frame?
			if(frameFinished)
			{
				//Convert the image into OPENGL 
				AVPicture pict;
				static struct SwsContext *img_convert_ctx;
				img_convert_ctx = sws_getCachedContext(img_convert_ctx,
		                   vCodecCtx->width, vCodecCtx->height, vCodecCtx->pix_fmt,
			               vCodecCtx->width, vCodecCtx->height, PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL);
		        sws_scale(img_convert_ctx, pFrame->data, pFrame->linesize,
		                   0, pFrame->height, pict.data, pict.linesize);

				/*
				usleep(40 * 1000);
				SDL_LockYUVOverlay(bmp);
				AVPicture pict;
				pict.data[0] = bmp->pixels[0];
				pict.data[1] = bmp->pixels[2];
				pict.data[2] = bmp->pixels[1];
				pict.linesize[0] = bmp->pitches[0];
				pict.linesize[1] = bmp->pitches[2];
				pict.linesize[2] = bmp->pitches[1];
				//Convert the image into YUV format that SDL uses
				static struct SwsContext *img_convert_ctx;
				img_convert_ctx = sws_getCachedContext(img_convert_ctx,
		                   vCodecCtx->width, vCodecCtx->height, vCodecCtx->pix_fmt,
			               vCodecCtx->width, vCodecCtx->height, PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
		        sws_scale(img_convert_ctx, pFrame->data, pFrame->linesize,
		                   0, pFrame->height, pict.data, pict.linesize);
				SDL_UnlockYUVOverlay(bmp); 
				rect.x = 0;
				rect.y = 0;
				rect.w = vCodecCtx->width;
				rect.h = vCodecCtx->height;
				SDL_DisplayYUVOverlay(bmp, &rect);
				*/
			}
			//Free the packet that was allocated by av_read_frame
			av_free_packet(&packet);	
			/*
			SDL_Event event;
			SDL_PollEvent(&event);
			switch(event.type)
			{
				case SDL_QUIT:
					quit = 1;
					SDL_Quit();
					exit(0);
					break;
				defalut:
					break;
			}
			*/
		}
		else if(packet.stream_index == audioStream)
		{
			packet_queue_put(&audioq, &packet);
		}
		else
		{
			av_free_packet(&packet);
		}
	}
	//Free the RGB image
	av_free(buffer);
	av_free(pFrameRGB);
	//Free the YUV freame
	av_free(pFrame);
	//Close the codec
	avcodec_close(vCodecCtx);
	//Close the video file
	avformat_close_input(&pFormatCtx);
}


