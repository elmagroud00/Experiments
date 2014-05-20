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

enum ThreadStatus
{
	THREAD_PREPARED,
	THREAD_PRE_PROCESS,
	THREAD_RUN,
	THREAD_STOP,
	THREAD_END
};

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
	void stopPlay();
	void exitThread();
	void isPlayMediaEnd();/* 1: end, 0: playing */
	void setMediaEndSig(int value);
	void setQuitSig(int value);
private:
	AVFormatContext			*m_pFormatCtx;
	std::string				m_filename;
	VideoDecoderThread		*m_videoDecoder;
	AVPacket				m_readPacket;
	AVPacket				*m_readPkt;
	int 					m_videoindex;
	int 					m_quit;
	pthread_mutex_t			m_quitMux;
	int 					m_demuxEnd;
	pthread_mutex_t			m_endMux;
	pthread_mutex_t			m_prepareMutex;
	bool					m_isVideoPrepared;
	static pthread_mutex_t	m_movieMutex;		
	int 					testOpen;
}

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
}

class DecoderThread
{
public:
	DecoderThread(Display *display, GLXContext glContext, GLXDrawable glDrawable);
	virtual ~VdpauDecoderThread();

	virtual void run();
	void changeFileSrc(char *filename);
	void stopPlay();
	void startPlay(char *filename);
	int createGLSurface(GLuint *texID);
	void releaseGLSurface(int index);
	void exitThread() { m_quit = true; }
private:
	void stopMediaPlay();
	void startMediaPlay(char *filename);
private:
	GLXContext			m_glContext;
	GLXDrawable			m_glDrawable;
	Display				*m_display;
	char				*filename;
private:
	bool				m_quit;
	GLuint				m_fbo;
	VdpauDecoderContext	*m_decoderContext;
	VdpauDisplayContext	*m_dispContext;	
}

#endif
