#include "DecoderThread.h"

#define SDL_AUDIO_BUFFER_SIZE		1024
#define WAIT_DECODER_THREAD_TIME	2000 //ms

VdpauContext		*g_deviceContext = NULL;
pthread_mutex_init(&DemuxThread::m_movieMutex, NULL);

DemuxThread::DemuxThread(std::string filename)
{
	m_filename = filename;
	setQuitSig(0);
	m_videoindex = -1;
	m_pFormatCtx = NULL;
	m_isVideoPrepared = false;
	m_readPkt = NULL;
   	pthread_mutex_init(&m_prepareMutex, NULL);
	pthread_mutex_init(&m_quitMux, NULL);
}

DemuxThread::~DemuxThread()
{
	if(m_pFormatCtx != NULL)
	{
		avformat_close_input(&m_pFormatCtx);	
		m_pFormatCtx = NULL;
	}
	pthread_mutex_destroy(&m_prepareMutex);
	pthread_mutex_destroy(&m_quitMux);
}

int DemuxThread::isPlayMediaEnd()
{
	if(!this->isRunning())
	{
		if(m_videoDecoder != NULL && !m_videoDecoder->isRunning())
		{
			fprintf(stderr, "demux is end and video decoder thread have stopped\n");
			return 1;
		}
	}
	return 0;
}

void DemuxThread::setVideoDecoder(VideoDecoderThread *videodecoder)
{
	m_videoDecoder = videodecoder;
}

void DemuxThread::setVideoName(std::string filename)
{
	fprintf("Demux to play movie: %s\n", filename);
	m_filename = filename;
}

void DemuxThread::releaseVideoInfo()
{
	pthread_mutex_lock(&m_movieMutex);
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
		m_videoDecoder = -1;
	}
	if(m_pFormatCtx != NULL)
	{
		fprintf(stderr, "close m_pformatCtx\n");
		testOpen--;
		avformat_close_input(&m_pFormatCtx);
		m_pFormatCtx = NULL;
	}
	pthread_mutex_unlock(&m_prepareMutex);
	pthread_mutex_unlock(&m_movieMutex);
}

bool DemuxThread::prepareVideoInfo()
{
	pthread_mutex_lock(&m_movieMutex);
	pthread_mutex_lock(&m_prepareMutex);
	m_videoindex = -1;
	m_isVideoPrepared = false;
	fprintf(stderr, "avformat_open_input file: %d\n", testOpen);
	testOpen++;
	int avret = avformat_open_input(&m_pFormatCtx, m_fileName, NULL, NULL);
	if(avret != 0)
	{
		fprintf(stderr, "avformat_open_input (%s) failed with %d\n", m_fileName, avret);
		pthread_mutex_unlock(&m_prepareMutex);
		pthread_mutex_unlock(&m_movieMutex);
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
	fprintf(stderr, "find video stream: %d\n", m_videoindex);
	av_dump_format(m_pFormatCtx, 0, m_fileName, 0);
	if(m_videoDecoder != NULL)
		m_isVideoPrepared = m_videoDecoder->prepareMediaInfo(m_pFormatCtx, m_videoindex);
	pthread_mutex_unlock(&m_prepareMutex);
	pthread_mutex_unlock(&m_movieMutex);
	if(m_isVideoPrepared)
		return true;
	else
		return false;
}

void DemuxThread::stopPlay()
{
	fprintf("stop demux thread\n");
	if(m_videoDecoder != NULL)
	{
		m_videoDecoder->exitThread();
		bool ret = m_videoDecoder->wait();
		if(!ret)
		{
			fprintf(stderr, "force to stop video thread\n");
		    m_videoDecoder->setThreadStatus(THREAD_STOP);
			m_videoDecoder->quit();		
		}
	}
	exitThread();	
	bool ret = wait();
	if(!ret)
	{
		fprintf("force to stop video thread\n");
		quit();
	}
	releaseVideoInfo();
}	

void DemuxThread::run()
{
	fprintf("demux thread start\n");
	int readret;
	setQuitSig(0);
	while(m_quit == 0)
	{
		if(!m_isVideoPrepared)
		{	
			usleep(10 * 1000);
			continue;
		}
		pthread_mutex_lock(&m_prepareMutex);
		if(m_videoDecoder->getThreadStatus() == THREAD_STOP)
		{
			pthread_mutex_unlock(&m_prepareMutex);
			fprintf(stderr, "video decoder had exit\n");
			break;
		}
		if(m_videoDecoder->getPacketSize > MAX_VIDEO_PACKET_NUM)
		{
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
		m_readPtk = &m_readPacket;
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
		if(m_readPkt->stream_index == m_videoindex && m_isVideoPrepared)
			m_videoDecoder->putPacket(m_readPkt);
		else
			av_free_packet(m_readPkt);
		m_readPkt = NULL;
		pthread_mutex_unlock(&m_prepareMutex);
	}
	fprintf(stderr, "demux thread exit\n");
}

void DemuxThread::setMediaEndSig(int value)
{
	pthread_mutex_lock(&m_quitMux);
	m_quit = value;
	pthread_mutex_unlock(&m_quitMux);
}

DecoderData::DecoderData()
{
	pthread_mutex_init(&m_pktMutex);
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
	fprintf("packet num is: %d\n", m_packetsList.size());
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
		datasize += it->size;
	pthread_mutex_unlock(&m_pktMutex);
	return datasize;
}



DecoderThread::DecoderThread(Display *display, GLXContext glContext, GLXDrawable glDrawable)
{
	m_quit = false;
	m_display = display;
	m_glDrawable = glDrawable;
	m_glContext = glContext;
	if(g_deviceContext == NULL)
	{
		g_deviceContext = new VdpauContext(m_display, DefalutScreen(m_display));
		g_deviceContext->init();
	}
	m_decoderContext = new VdpauDecoderContext(g_deviceContext);
	m_dispContext = new VdpauDecoderContext(m_glDrawable, g_deviceContext);
}


