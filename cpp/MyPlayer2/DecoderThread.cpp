#include "DecoderThread.h"
#include <sys/time.h>


#define SDL_AUDIO_BUFFER_SIZE		1024
#define WAIT_DECODER_THREAD_TIME	2000 //ms

VdpauContext		*g_deviceContext = NULL;

DemuxThread::DemuxThread()
{
	m_fileName = NULL;
	m_videoindex = -1;
	m_pFormatCtx = NULL;
	m_readPkt = NULL;
	m_quit = false;
   	pthread_mutex_init(&m_prepareMutex, NULL);
}

DemuxThread::~DemuxThread()
{
	if(m_pFormatCtx != NULL)
	{
		avformat_close_input(&m_pFormatCtx);	
		m_pFormatCtx = NULL;
	}
	pthread_mutex_destroy(&m_prepareMutex);
}

void DemuxThread::setVideoDecoder(VideoDecoderThread *videodecoder)
{
	m_videoDecoder = videodecoder;
}

void DemuxThread::demuxVideo(const char *fileName)
{
	m_fileName = fileName;
	prepareVideoInfo();
}

void DemuxThread::releaseVideoInfo()
{
	pthread_mutex_lock(&m_prepareMutex);
	if(m_readPkt != NULL)
	{
		fprintf(stderr, "free m_readPkt\n");
		av_free_packet(m_readPkt);
		m_readPkt = NULL;	
	}
	if(m_videoDecoder)
	{
		m_videoDecoder->releaseMediaInfo();
		m_videoindex = -1;
	}
	if(m_pFormatCtx != NULL)
	{
		fprintf(stderr, "close m_pformatCtx\n");
		avformat_close_input(&m_pFormatCtx);
		m_pFormatCtx = NULL;
	}
	pthread_mutex_unlock(&m_prepareMutex);
	m_quit = true;
}

bool DemuxThread::prepareVideoInfo()
{
	pthread_mutex_lock(&m_prepareMutex);
	m_videoindex = -1;
	m_isVideoPrepared = false;
	fprintf(stderr, "avformat_open_input file: %s\n", m_fileName);
	int avret = avformat_open_input(&m_pFormatCtx, m_fileName, NULL, NULL);
	if(avret != 0)
	{
		fprintf(stderr, "avformat_open_input (%s) failed with %d\n", m_fileName, avret);
		pthread_mutex_unlock(&m_prepareMutex);
		return false;
	}
	for(unsigned int i = 0; i < m_pFormatCtx->nb_streams; i++)
	{
		if(m_pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			m_videoindex = i;
			break;
		}
	}
	fprintf(stderr, "m_videoindex = %d\n", m_videoindex);
	av_dump_format(m_pFormatCtx, 0, m_fileName, 0);
	if(m_videoDecoder != NULL)
		m_isVideoPrepared = m_videoDecoder->prepareMediaInfo(m_pFormatCtx, m_videoindex);
	pthread_mutex_unlock(&m_prepareMutex);
	if(m_isVideoPrepared)
	{
		m_quit = false;
		return true;
	}
	else
		return false;
}

void DemuxThread::run()
{
	fprintf(stderr, "demux thread start\n");
	int readret;
	while(!m_quit)
	{
		if(!m_isVideoPrepared)
		{	
			usleep(10 * 1000);
			continue;
		}
		pthread_mutex_lock(&m_prepareMutex);

		if(m_videoDecoder->getPacketSize() > MAX_VIDEO_PACKET_NUM)
		{
			fprintf(stderr, "packet list full, sleep now\n");
			usleep(10 * 1000);
			pthread_mutex_unlock(&m_prepareMutex);
			continue;
		}
		if(m_pFormatCtx == NULL)
		{
			fprintf(stderr, "m_pFormatCtx is NULL\n");
			pthread_mutex_unlock(&m_prepareMutex);
			break;
		}
		m_readPkt = &m_readPacket;
		if((readret = av_read_frame(m_pFormatCtx, m_readPkt)) < 0)
		{	
			if(readret == AVERROR_EOF || url_feof(m_pFormatCtx->pb) == 0)
			{
				fprintf(stderr, "av_read_frame end of file\n");
				m_readPkt = NULL;
				pthread_mutex_unlock(&m_prepareMutex);
				break;
			}	
			else
			{
				m_readPkt = NULL;
				pthread_mutex_unlock(&m_prepareMutex);
				break;
			}			
		}
		/* be sure the video stream */
		if(m_readPkt->stream_index == m_videoindex && m_isVideoPrepared)
		{
			fprintf(stderr, "begin to putPacket\n");
			m_videoDecoder->putPacket(m_readPkt);
		}
		else
			av_free_packet(m_readPkt);/*just free the data struct*/

		m_readPkt = NULL;
		pthread_mutex_unlock(&m_prepareMutex);
	}
	fprintf(stderr, "demux thread exit\n");
}

DecoderData::DecoderData()
{
	pthread_mutex_init(&m_pktMutex, NULL);
}

DecoderData::~DecoderData()
{
	freePacket();
	pthread_mutex_destroy(&m_pktMutex);
}

void DecoderData::putPacket(AVPacket *pkt)
{
	AVPacket *packet = (AVPacket*)av_malloc(sizeof(AVPacket));
	if(!packet)
	{
		fprintf(stderr, "av_malloc error\n");
		return ;
	}	
	pthread_mutex_lock(&m_pktMutex);
	*packet = *pkt;
	m_packetsList.push_back(packet);
	pthread_mutex_unlock(&m_pktMutex);
}

AVPacket *DecoderData::getPacket()
{
	AVPacket *packet = NULL;
	pthread_mutex_lock(&m_pktMutex);
	if(!m_packetsList.empty())
	{
		packet = m_packetsList.front();
		m_packetsList.pop_front();
	}
	pthread_mutex_unlock(&m_pktMutex);
	return packet;
}

void DecoderData::freePacket()
{
	pthread_mutex_lock(&m_pktMutex);
	fprintf(stderr, "packet num is: %d\n", m_packetsList.size());
	while(!m_packetsList.empty())
	{
		AVPacket *packet = m_packetsList.front();
		m_packetsList.pop_front();
		av_free_packet(packet);
		av_freep(&packet);
	}
	pthread_mutex_unlock(&m_pktMutex);
}

int DecoderData::getDataSize()
{
	int datasize = 0;
    pthread_mutex_lock(&m_pktMutex);
	for(std::list<AVPacket*>::iterator it = m_packetsList.begin(); it != m_packetsList.end(); it++)
		datasize += (*it)->size;
	pthread_mutex_unlock(&m_pktMutex);
	return datasize;
}

int DecoderData::getPacketSize()
{
	int size;
	pthread_mutex_lock(&m_pktMutex);
	size = m_packetsList.size();
	pthread_mutex_unlock(&m_pktMutex);
	return size;
}

VideoDecoderThread::VideoDecoderThread()
{
	m_pFormatCtx = NULL;
	m_stream = NULL;
	m_codecContext = NULL;
	pthread_mutex_init(&m_codecCtxMutex, NULL);
	m_frame = avcodec_alloc_frame();
	m_decodePkt = NULL;
}

VideoDecoderThread::~VideoDecoderThread()
{
	av_free(m_frame);
	if(m_decodePkt != NULL)
	{
		av_free_packet(m_decodePkt);
		av_freep(&m_decodePkt);
	}
	pthread_mutex_destroy(&m_codecCtxMutex);
}

void VideoDecoderThread::setVdpauContext(VdpauContext *dev, VdpauDecoderContext *dec, VdpauDisplayContext *dsp)
{
	m_deviceContext = dev;
	m_decoderContext = dec;
	m_displayContext = dsp;
	m_quit = false;
}

void VideoDecoderThread::releaseMediaInfo()
{
	if(m_stream != NULL && m_codecContext != NULL)
	{
		fprintf(stderr, "release codec context\n");
		m_stream->discard = AVDISCARD_ALL;
		m_codecContext = NULL;
	}
	if(m_decodePkt != NULL)
	{
		av_free_packet(m_decodePkt);
		av_freep(&m_decodePkt);
	}
	pthread_mutex_lock(&m_codecCtxMutex);
	freePacket();
	pthread_mutex_unlock(&m_codecCtxMutex);
//	DecoderContext::releaseMediaInfo();
	//m_displayContext->releaseDisplayContext();
	m_quit = true;
}

bool VideoDecoderThread::prepareMediaInfo(AVFormatContext *pFormatCtx, int index)
{
	m_pFormatCtx = pFormatCtx;
	AVCodec *codec = NULL;
	if(pFormatCtx == NULL)
	{
		fprintf(stderr, "m_pFormatCtx NULL\n");
		return NULL;
	}	
	if(index < 0)
	{
		fprintf(stderr, "video index error: index = %d\n", index);
		m_codecContext = NULL;
		m_stream = NULL;
		return false;
	}
	if(pFormatCtx->nb_streams < index)
	{
		fprintf(stderr, "pformatCtx->nb_streams < index, error\n");
		return false;
	}
	m_codecContext = pFormatCtx->streams[index]->codec;
	if(m_codecContext->codec_id == CODEC_ID_H264)
	{
		fprintf(stderr, "Find CODEC_ID_H264\n");
		codec = avcodec_find_decoder_by_name("h264_vdpau");
		m_codecContext->get_format = decoder_get_format;
		m_codecContext->get_buffer = decoder_get_buffer;
		m_codecContext->release_buffer = decoder_release_buffer;
		m_codecContext->draw_horiz_band = decoder_draw_horiz_band;
		m_codecContext->reget_buffer = decoder_get_buffer;
		m_codecContext->slice_flags = SLICE_FLAG_CODED_ORDER | SLICE_FLAG_ALLOW_FIELD;
	}
	else
	{
		fprintf(stderr, "unsupport codec(%s)\n", m_codecContext->codec_name);
		m_codecContext = NULL;
		m_stream = NULL;
		return false;
	}	
	if(!codec || avcodec_open2(m_codecContext, codec, NULL) < 0)
	{
		fprintf(stderr, "unsupport codec(%s)\n", m_codecContext->codec_name);
	}
	fprintf(stderr, "m_codecContext->pix_fmt = %d, m_codecContext->width = %d, m_codecContext->height = %d\n", 
			m_codecContext->pix_fmt, m_codecContext->width, m_codecContext->height);
	m_codecContext->opaque = (void*)m_decoderContext;
	m_stream = m_pFormatCtx->streams[index];
	m_decoderContext->updateDecoderContext(PIX_FMT_VDPAU_H264, m_codecContext->width, m_codecContext->height);
	m_displayContext->updateDisplayContext(m_codecContext->width, m_codecContext->height);
	m_quit = false;
	return true;
}

void VideoDecoderThread::run()
{	
	fprintf(stderr, "VideoDecoderThread start\n");
	int decLen, frameFinished;
	struct timeval startTime, endTime;

	while(!m_quit)
	{
		gettimeofday(&startTime, NULL);
		pthread_mutex_lock(&m_codecCtxMutex);
		if(m_codecContext == NULL)
		{
			pthread_mutex_unlock(&m_codecCtxMutex);
			break;
		}
		if(getPacketSize() == 0)
		{
			pthread_mutex_unlock(&m_codecCtxMutex);
			usleep(5 * 1000);
			continue;
		}
		m_decodePkt = getPacket();
		if(m_decodePkt == NULL)	
		{
			pthread_mutex_unlock(&m_codecCtxMutex);
			fprintf(stderr, "no packet in list\n");
			continue;
		}
		decLen = avcodec_decode_video2(m_stream->codec, m_frame, &frameFinished, m_decodePkt);
		pthread_mutex_unlock(&m_codecCtxMutex);
		if(frameFinished)
		{
			fprintf(stderr, "m_decoderContext->updateframe(m_frame)\n");
			m_decoderContext->updateframe(m_frame);
		}
		if(m_decodePkt != NULL)
		{
			av_free_packet(m_decodePkt);
			av_freep(&m_decodePkt);
		}
		gettimeofday(&endTime, NULL);

		double sleepTime = 42 - (((endTime.tv_sec * 1000 * 1000 + endTime.tv_usec) / 1000 -
			   			       (startTime.tv_sec * 1000 * 1000 + startTime.tv_usec) / 1000) + 1000) % 1000;
		if(sleepTime < 0)
			sleepTime = 0;

		fprintf(stderr, "DecoderThread sleepTime %ld\n", sleepTime);
		av_usleep(sleepTime * 1000);
	}	
	fprintf(stderr, "video thread end\n");
}	

VideoPlayer::VideoPlayer(Display *display, GLXContext glContext, GLXDrawable glDrawable)
{
	m_display = display;
	m_glDrawable = glDrawable;
	m_glContext = glContext;
	if(g_deviceContext == NULL)
	{
		g_deviceContext = new VdpauContext(m_display, DefaultScreen(m_display));
		g_deviceContext->init();
	}
	m_decoderContext = new VdpauDecoderContext(g_deviceContext);
	m_dispContext = new VdpauDisplayContext(m_glDrawable, g_deviceContext);
	m_decoderContext->setDisplayHandle(m_dispContext);
	m_demux = new DemuxThread();
	m_videoDecoder = new VideoDecoderThread;
	m_videoDecoder->setVdpauContext(g_deviceContext, m_decoderContext, m_dispContext);
	m_demux->setVideoDecoder(m_videoDecoder);
}

VideoPlayer::~VideoPlayer()
{
	delete m_videoDecoder;
	delete m_demux;
	delete m_decoderContext;
	delete m_dispContext;
}

int VideoPlayer::createGLSurface(GLuint *texID)
{
	return m_dispContext->decoderSurface2Texture(m_fbo, texID, 0);
}

void VideoPlayer::releaseGLSurface(int index)
{
	m_dispContext->releaseTexture(index);
}

void VideoPlayer::setFileName(const char *filename)
{
	m_fileName = filename;
}

void VideoPlayer::quitPlayer()
{
	m_demux->releaseVideoInfo();
	m_videoDecoder->releaseMediaInfo();
}

void VideoPlayer::stopPlay()
{
	m_demux->releaseVideoInfo();
	m_videoDecoder->releaseMediaInfo();
}

void VideoPlayer::startPlay()
{
	m_demux->demuxVideo(m_fileName);
	m_demux->start();
	m_videoDecoder->start();
}