#ifndef _VDPAU_DECODER_CONTEXT_H_
#define _VDPAU_DECODER_CONTEXT_H_

extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavcodec/vdpau.h>
}	
#include <vdpau/vdpau_x11.h>
#include "VdpauDisplayContext.h"
#include "VdpauContext.h"

#define VIDEO_SURFACES_NUM	18
#define HISTORY_VIDEO_NUM	5

extern int decoder_get_buffer(struct AVCodecContext *c, AVFrame *pic);
extern void decoder_release_buffer(struct AVCodecContext *c, AVFrame *pic);
extern void decoder_draw_horiz_band(struct AVCodecContext *context, const AVFrame *frame, 
									int offset[4], int y, int type, int h);
extern enum PixelFormat decoder_get_format(struct AVCodecContext *codecCtx, const enum PixelFormat *pix_fmt);

class VdpauDecoderContext
{
public:
	VdpauDecoderContext(VdpauContext *vdpContext = NULL);
	~VdpauDecoderContext();

	int updateDecoderContext(int pixfmt, int width, int height);
	struct vdpau_render_state *get_video_surface();
	int decoder_render(struct vdpau_render_state *rndr);
	void updateframe(AVFrame *frame);
	void setDisplayHandle(VdpauDisplayContext *context);
private:
	void destroy_decoder_resource();
	void make_decoder_invalid();
	int create_surface_resource(int width, int height);
	int create_decoder_resource(int pixfmt, int max_refs, int width, int height);
	int create_vdp_mixer(VdpChromaType vdp_chroma_type, int width, int height);
	int update_csc_matrix(VdpVideoMixer mixer);
	void push_int_surface(VdpVideoSurface surface);
	void initHistorySurface();
public:
	VdpDecoder 		m_vdp_decoder;
	VdpVideoMixer	m_vdp_videoMixer;
private:
	VdpauContext			*m_pVdpContext;
	VdpauDisplayContext		*m_pDisplayContext;
	int						m_vdp_pixfmt;
	int 					m_vdp_width;
	int 					m_vdp_height;
	int 					m_vdp_surface_render_index;
	VdpVideoSurface			m_history_surface[HISTORY_VIDEO_NUM];
	struct vdpau_render_state 	m_surface_render[VIDEO_SURFACES_NUM];
	pthread_mutex_t			m_contextMutex;
public:
	int 					ip_age[2];
	int 					b_age;
};
#endif
