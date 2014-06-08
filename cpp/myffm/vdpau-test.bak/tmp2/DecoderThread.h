#ifndef _DECODER_THREAD_H_
#define _DECODER_THREAD_H_

extern "C"
{
#include <libavcodec/avcodec.h>	
#include <libavutil/common.h>
#include <libavutil/avstring.h>
#include <libavcodc/avcodec.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libswscale/swscale.h>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
}
#include <math.h>
#include <string>

#include "VdpauContext.h"
#include "VdpauDisplayContext.h"
#include "VdpauDecoderContext.h"

#define MAX_VIDEO_PACKET_NUM	256
#define MAX_AUDIO_PACKET_NUM	256

class DecoderThread;
class VideoDecoderThread;

class DemuxThread
{
public:
	DemuxThread(std::string filename = "");
	~DemuxThread();
	virtual void run();
	void setVideoDecoder(VideoDecoderThread *videodecoder);
	void setVideoName(std::string filename);
	void releaseVideoInfo();
	void prepareVideoInfo();
	void exitThread();
private:
	AVFormatContext			*m_pFormatCtx;
	std::string				m_filename;
	VideoDecoderThread		*m_videoDecoder;
	AVPacket				m_readPacket;
	AVPacket				*m_readPkt;
	int 					m_videoindex;
	int 					m_demuxEnd;
	pthread_mutex_t			m_endMux;
	pthread_mutex_t			m_prepareMutex;
	static pthread_mutex_t	m_movieMutex;		
	int 					testOpen;
};

class DecoderData
{
public:
	DecoderData();
	virtual ~DecoderData();
	void putPacket(AVPacket *pkt);
	AVPacket *getPacket();
	int getPacketSize();
	int getDataSize();
	void freePacket();
protected:
	std::list<AVPacket*>	m_packetsList;
	pthread_mutex			m_pktMutex;
};

class DecoderContext : public DecoderData
{
public:
	DecoderContext();
	virtual ~DecoderContext();
	virtual void releaseMediaInfo();
	virtual bool prepareMediaInfo(AVFormatContext *pFormatCtx, int index);
protexted:
	AVFormatContext		*m_pFormatCtx;
	AVStream			*m_stream;
	AVCodecContext		*m_codecContext;
	pthread_mutex_t		m_codecCtxMutex;
};

class VideoDecoderThread : public DecoderContext
{
public:
	VideoDecoderThread();
	virtual ~VideoDecoderThread();
	virtual void run;
	void setVdpauContext(VdpauContext *dev, VdpauDecoderContext *dec, VdpauDisplayContext *dsp);
	virtual bool prepareMediaInfo(AVFormatContext *pFormatCtx, int index);
	virtual void releaseMediaInfo();
	void setDecoderThread(DecoderThread *pth) { m_decoderThread = pth; }
	void setDemuxThread(DemuxThread *demux) { m_demuxThread = demux; }
private:
	VdpauContext		*m_deviceContext;
	VdpauDecoderContext	*m_decoderContext;
	VdpauDisplayContext *m_displayContext;
	DecoderThread		*m_decoderThread;
	DemuxThread			*m_demuxThread;
	AVFrame				*m_frame;
	AVPacket			*m_decodePkt;
}

class DecoderThread
{
public:
	DecoderThread(Display *display, GLXContext glContext, GLXDrawable glDrawable);
	virtual ~VdpauDecoderThread();

	virtual void run();
	void changeFileSrc(std::string filename);
	void startPlay(std::string filename);
	int createGLSurface(GLuint *texID);
	void releaseGLSurface(int index);
private:
	void startMediaPlay(std::string filename);
private:
	GLXContext			m_glContext;
	GLXDrawable			m_glDrawable;
	Display				*m_display;
	std::string			filename;
private:
	GLuint				m_fbo;
	VdpauDecoderContext	*m_decoderContext;
	VdpauDisplayContext	*m_dispContext;	
	VideoDecoderThread	*m_VideoDecoder;
};

#endif






