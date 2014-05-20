#include "DecoderThread.h"
#include <sys/time.h>

#define SDL_AUDIO_BUFFER_SIZE		1024
#define WAIT_DECODER_THREAD_TIME	2000 //ms

VdpauContext		*g_deviceContext = NULL;

DemuxThread::DemuxThread(std::string filename)
{
	m_fileName = filename;
	m_videoindex = -1;
	m_pFormatCtx = NULL;
	m_readPkt = NULL;
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

void DemuxThread::setVideoName(std::string filename)
{
	m_fileName = filename;
	fprintf(stderr, "Demux to play movie: %s\n", m_fileName.c_str());
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
		testOpen--;
		avformat_close_input(&m_pFormatCtx);
		m_pFormatCtx = NULL;
	}
	pthread_mutex_unlock(&m_prepareMutex);
}

bool DemuxThread::prepareVideoInfo()
{
	pthread_mutex_lock(&m_prepareMutex);
	m_videoindex = -1;
	m_isVideoPrepared = false;
	fprintf(stderr, "avformat_open_input file: %d\n", testOpen);
	testOpen++;
	int avret = avformat_open_input(&m_pFormatCtx, m_fileName.c_str(), NULL, NULL);
	if(avret != 0)
	{
		fprintf(stderr, "avformat_open_input (%s) failed with %d\n", m_fileName.c_str(), avret);
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
	av_dump_format(m_pFormatCtx, 0, m_fileName.c_str(), 0);
	//AVStream *m_stream = m_pFormatCtx->streams[m_videoindex];
	//fprintf(stderr, "m_stream->codec->codec->name = %s\n", m_stream->codec->codec->name);
	if(m_videoDecoder != NULL)
		m_isVideoPrepared = m_videoDecoder->prepareMediaInfo(m_pFormatCtx, m_videoindex);
	pthread_mutex_unlock(&m_prepareMutex);
	if(m_isVideoPrepared)
		return true;
	else
		return false;
}

void DemuxThread::run()
{
	fprintf(stderr, "demux thread start\n");
	int readret;
	while(1)
	{
		if(!m_isVideoPrepared)
		{	
			usleep(10 * 1000);
			continue;
		}
		pthread_mutex_lock(&m_prepareMutex);
/*		if(m_videoDecoder->getThreadStatus() == THREAD_STOP)
		{
			pthread_mutex_unlock(&m_prepareMutex);
			fprintf(stderr, "video decoder had exit\n");
			break;
		}*/
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
			m_videoDecoder->putPacket(m_readPkt); /* is this correct ? */
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
		av_free(packet);
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

DecoderContext::DecoderContext()
{
	m_pFormatCtx = NULL;
	m_stream = NULL;
	m_codecContext = NULL;
	pthread_mutex_init(&m_codecCtxMutex, NULL);
}

DecoderContext::~DecoderContext()
{
	releaseMediaInfo();
	pthread_mutex_destroy(&m_codecCtxMutex);	
}

void DecoderContext::releaseMediaInfo()
{
	pthread_mutex_lock(&m_codecCtxMutex);
	freePacket();
	if(m_stream != NULL && m_codecContext != NULL)
	{
		fprintf(stderr, "release codec context\n");
		m_stream->discard = AVDISCARD_ALL;
		m_codecContext = NULL;
	}
	pthread_mutex_unlock(&m_codecCtxMutex);
}

bool DecoderContext::prepareMediaInfo(AVFormatContext *pFormatCtx, int index)
{
	return true;
}

VideoDecoderThread::VideoDecoderThread()
{
	m_frame = avcodec_alloc_frame();
	m_decodePkt = NULL;
}

VideoDecoderThread::~VideoDecoderThread()
{
	av_free(m_frame);
	if(m_decodePkt != NULL)
	{
		av_free_packet(m_decodePkt);
		av_free(m_decodePkt);
		m_decodePkt = NULL;
	}
}

void VideoDecoderThread::setVdpauContext(VdpauContext *dev, VdpauDecoderContext *dec, VdpauDisplayContext *dsp)
{
	m_deviceContext = dev;
	m_decoderContext = dec;
	m_displayContext = dsp;
}

void VideoDecoderThread::releaseMediaInfo()
{
	if(m_decodePkt != NULL)
	{
		av_free_packet(m_decodePkt);
		av_free(m_decodePkt);
		m_decodePkt = NULL;
	}
	DecoderContext::releaseMediaInfo();
	m_displayContext->releaseDisplayContext();
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
	if(!codec || avcodec_open(m_codecContext, codec) < 0)
	{
		fprintf(stderr, "unsupport codec(%s)\n", m_codecContext->codec_name);
	}
	fprintf(stderr, "m_codecContext->pix_fmt = %d, m_codecContext->width = %d, m_codecContext->height = %d\n", 
			m_codecContext->pix_fmt, m_codecContext->width, m_codecContext->height);
	m_codecContext->opaque = (void*)m_decoderContext;
	m_stream = m_pFormatCtx->streams[index];
	//fprintf(stderr, "m_stream->codec = %p\n", m_stream->codec);
	//fprintf(stderr, "m_stream->codec->codec->name = %s\n", m_stream->codec->codec->name);
	m_decoderContext->updateDecoderContext(PIX_FMT_VDPAU_H264, m_codecContext->width, m_codecContext->height);
	m_displayContext->updateDisplayContext(m_codecContext->width, m_codecContext->height);

	return true;
}

void VideoDecoderThread::run()
{	
	fprintf(stderr, "VideoDecoderThread start\n");
	int decLen, frameFinished;
	double pts = 0;
	struct timeval startTime, endTime;
	int frameNum = 0;
	int syncNum = 0;
	while(1)
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
		pts = 0;
		decLen = avcodec_decode_video2(m_stream->codec, m_frame, &frameFinished, m_decodePkt);
		pthread_mutex_unlock(&m_codecCtxMutex);
		if(m_decodePkt->dts == AV_NOPTS_VALUE && m_frame->opaque && *(uint64_t*)m_frame->opaque != AV_NOPTS_VALUE)
			pts = *(uint64_t*)m_frame->opaque;
		else if(m_decodePkt->dts != AV_NOPTS_VALUE)
				pts = m_decodePkt->dts;
		else
			pts = 0;
		pts *= av_q2d(m_stream->time_base);
		if(frameFinished)
		{
			fprintf(stderr, "m_decoderContext->updateframe(m_frame)\n");
			m_decoderContext->updateframe(m_frame);
		}
		frameNum++;
		if(m_decodePkt != NULL)
		{
			av_free_packet(m_decodePkt);
			av_free(m_decodePkt);
			m_decodePkt = NULL;
		}
		gettimeofday(&endTime, NULL);
		int sleepTime = 42 - (((endTime.tv_sec * 1000 * 1000 + endTime.tv_usec) / 1000 -
			   			       (startTime.tv_sec * 1000 * 1000 + startTime.tv_usec) / 1000) + 1000) % 1000;
//		usleep(sleepTime * 1000);
	}	
	fprintf(stderr, "video thread end\n");
}	

DecoderThread::DecoderThread(Display *display, GLXContext glContext, GLXDrawable glDrawable)
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
	m_demux = new DemuxThread;
	m_videoDecoder = new VideoDecoderThread;
	m_videoDecoder->setVdpauContext(g_deviceContext, m_decoderContext, m_dispContext);
	m_videoDecoder->setDecoderThread(this);
	m_videoDecoder->setDemuxThread(m_demux);
	m_demux->setVideoDecoder(m_videoDecoder);
}

DecoderThread::~DecoderThread()
{
	delete m_videoDecoder;
	delete m_demux;
	delete m_decoderContext;
	delete m_dispContext;
}

int DecoderThread::createGLSurface(GLuint *texID)
{
	return m_dispContext->decoderSurface2Texture(m_fbo, texID, 0);
}

void DecoderThread::releaseGLSurface(int index)
{
	m_dispContext->releaseTexture(index);
}

void DecoderThread::startMediaPlay(std::string fileName)
{
	m_fileName = fileName;
	m_demux->setVideoName(m_fileName);
	m_demux->prepareVideoInfo();
	m_demux->start();
	m_videoDecoder->start();
}

void DecoderThread::run()
{
	while(1)
	{
		fprintf(stderr, "Decoder thread...\n");
	//	startMediaPlay("/home/sijiewang/Videos/mollystheory-tlr1_h480p.mov");
		startMediaPlay("/home/sijiewang/Videos/A1.mp4");
		sleep(1000000);
	}
}
