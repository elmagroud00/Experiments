#ifndef _DECODER_THREAD_H_
#define _DECODER_THREAD_H_

extern "C"
{
#include <libavutil/common.h>
#include <libavutil/avstring.h>
#include <libavcodec/avcodec.h>
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
#include "Thread.h"
#include <list>

#define MAX_VIDEO_PACKET_NUM	256
#define MAX_AUDIO_PACKET_NUM	256

class VideoPlayer;
class VideoDecoderThread;
class Thread;

class DemuxThread : public Thread
{
public:
	DemuxThread();
	virtual ~DemuxThread();
	virtual void run();
	void setVideoDecoder(VideoDecoderThread *videodecoder);
	void releaseVideoInfo();
	bool prepareVideoInfo();
	void demuxVideo(const char *fileName);
private:
	AVFormatContext			*m_pFormatCtx;
	const char				*m_fileName;
	VideoDecoderThread		*m_videoDecoder;
	AVPacket				m_readPacket;
	AVPacket				*m_readPkt;
	int 					m_videoindex;
	int 					m_demuxEnd;
	pthread_mutex_t			m_endMux;
	pthread_mutex_t			m_prepareMutex;
	bool					m_isVideoPrepared;
	bool					m_quit;
};

class DecoderData
{
public:
	DecoderData();
	virtual ~DecoderData();
	void putPacket(AVPacket *pkt);
	AVPacket *getPacket();
	int getPacketSize();
	int getDataSize(); /*AVPacket->size */
	void freePacket();
protected:
	std::list<AVPacket*>	m_packetsList;
	pthread_mutex_t			m_pktMutex;
};

class VideoDecoderThread : public DecoderData, public Thread
{
public:
	VideoDecoderThread();
	virtual ~VideoDecoderThread();
	virtual void run();
	void setVdpauContext(VdpauContext *dev, VdpauDecoderContext *dec, VdpauDisplayContext *dsp);
	virtual bool prepareMediaInfo(AVFormatContext *pFormatCtx, int index);
	virtual void releaseMediaInfo();
private:
	AVFormatContext		*m_pFormatCtx;
	AVStream			*m_stream;
	AVCodecContext		*m_codecContext;
	pthread_mutex_t		m_codecCtxMutex;

	VdpauContext		*m_deviceContext;
	VdpauDecoderContext	*m_decoderContext;
	VdpauDisplayContext *m_displayContext;
	VideoPlayer		*m_decoderThread;
	DemuxThread			*m_demuxThread;
	AVFrame				*m_frame;
	AVPacket			*m_decodePkt;
	bool 				m_quit;
};

class VideoPlayer
{
public:
	VideoPlayer(Display *display, GLXContext glContext, GLXDrawable glDrawable);
	virtual ~VideoPlayer();
	void setFileName(const char *filename);
	void startPlay();
	void stopPlay();
	void quitPlayer();
	int createGLSurface(GLuint *texID);
	void releaseGLSurface(int index);

private:
	GLXContext			m_glContext;
	GLXDrawable			m_glDrawable;
	Display				*m_display;
	const char*			m_fileName;
	GLuint				m_fbo;
	DemuxThread			*m_demux;
	VdpauDecoderContext	*m_decoderContext;
	VdpauDisplayContext	*m_dispContext;	
	VideoDecoderThread	*m_videoDecoder;
};

#endif
