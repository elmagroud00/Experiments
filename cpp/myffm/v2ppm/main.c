#include <stdio.h>
#include <stdlib.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
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

int main(int argc ,char **argv)
{
	av_register_all();
	AVFormatContext *pFormatCtx = NULL;
	AVInputFormat *file_iformat = NULL;
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
	AVCodecContext *pCodecCtx;
	//Find the first video stream
	videoStream = -1;
	for(i = 0; i < pFormatCtx->nb_streams; i++)
	{
		if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoStream = i;
			break;
		}
	}
	if(videoStream == -1)
	{
		printf("no video stream\n");
		return -1;//Did not find a video stream
	}
	printf("find video strean: %d\n", videoStream);
	//Get a pointer to the codec context for the video stream
	pCodecCtx = pFormatCtx->streams[videoStream]->codec;
	AVCodec *pCodec;
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if(pCodec == NULL)
	{
		fprintf(stderr, "Unsupported codec\n");
		return -1;//codec not find
	}
	//OPen codec
	if(avcodec_open(pCodecCtx, pCodec) < 0)
		return -1;//Could not open codec
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
	numBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
	buffer = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t));
	//Assign appropriate parts of buffer to image planes in pFrameRGB
	//Note that pFrameRGB is an AVFrame, but AVFrame is a superset
	//of AVPicture
	avpicture_fill((AVPicture*)pFrameRGB, buffer, PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
	int frameFinished;
	AVPacket packet;
	i = 0;
	while(av_read_frame(pFormatCtx, &packet) >=0)
	{
		//is this a packet from video stream?
		if(packet.stream_index == videoStream)
		{
			//Decoder video frame
			avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
			//Did we got a video frame?
			if(frameFinished)
			{
				//Convert the image from its native format to RGB
				static struct SwsContext *img_convert_ctx;
				img_convert_ctx = sws_getCachedContext(img_convert_ctx,
		                   pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
			               pCodecCtx->width, pCodecCtx->height, PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);
		        sws_scale(img_convert_ctx, pFrame->data, pFrame->linesize,
		                   0, pFrame->height, pFrameRGB->data, pFrameRGB->linesize);
				//Save the frame to disk;
				if(++i <= 10)
				{
					printf("begin to write to file\n");
					SaveFrame(pFrameRGB, pCodecCtx->width, pCodecCtx->height, i);
				}
			}
			//Free the packet that was allocated by av_read_frame
			av_free_packet(&packet);	
		}
	}
	//Free the RGB image
	av_free(buffer);
	av_free(pFrameRGB);
	//Free the YUV freame
	av_free(pFrame);
	//Close the codec
	avcodec_close(pCodecCtx);
	//Close the video file
	avformat_close_input(&pFormatCtx);
}



