#ifndef _VDPAU_DISPLAY_CONTEXT_H
#define _VDPAU_DISPLAY_CONTEXT_H

#include <stdio.h>
#include <pthread.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <vdpau/vdpau_x11.h>

#include "VdpauContext.h"

#define OUTPUT_SURFACE_NUM	2

class VdpauDisplayContext
{
public:
	VdpauDisplayContext(Window win, VdpauContext *vdpContext = NULL);
	~VdpauDisplayContext();
	int updateDisplayContext(int width, int height);
	void releaseDisplayContext();
	int decoderVideo2OutputSurface(int width, int height,
								   VdpVideoSurface *history,
								   VdpVideoSurface current,
								   VdpVideoSurface future,
								   VdpVideoMixer mixer);
	int decoderSurface2Texture(GLuint fbo, GLuint *inTex, int status);
	int releaseTexture(int index);
	void destroyOutputSurface();
private:
	int get_surface_iter(VdpOutputSurface face);
	int register_surface(int iter, VdpOutputSurface face);
	int remove_register_surface(VdpOutputSurface face);
	GLuint CopyTexture1(GLuint fbo, GLuint nTexID_in, GLuint nTexID_out, GLsizei width, GLsizei height, int status);
	bool checkFramebufferStatus();
public:
	VdpauContext 	*m_pVdpContext;
	Window			m_disp_win;

	int 			m_disp_width;
	int				m_disp_height;
		
	VdpPresentationQueueTarget		m_vdp_presentation_queue_target;
	VdpPresentationQueue			m_vdp_presentation_queue;
	VdpOutputSurface				m_fixed_outputSurface[2][OUTPUT_SURFACE_NUM];
	int 							m_vdp_output_surface_used_index;
	VdpOutputSurface				m_vdp_outputSurface[OUTPUT_SURFACE_NUM];
	VdpOutputSurface				m_vdp_display_surface;
	int 							m_vdp_output_surface_index;
	GLvdpauSurfaceNV				m_gl_surface[OUTPUT_SURFACE_NUM];
	GLuint							m_register_texture[OUTPUT_SURFACE_NUM];
	VdpOutputSurface				m_register_surface[OUTPUT_SURFACE_NUM];
	bool							m_need_destroy_register;
	pthread_mutex_t					m_outputSurfaceMutex;
	pthread_mutex_t					testsurface;
};
#endif
