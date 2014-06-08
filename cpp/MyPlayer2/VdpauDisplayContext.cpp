#include "VdpauDisplayContext.h"

int check_error(int line)
{
	GLenum	errCode;
	const	GLubyte	*errString;
	if((errCode = glGetError()) != GL_NO_ERROR)
	{
		errString = gluErrorString(errCode);
		fprintf(stderr, "OpenGL Error: %s : %d\n", errString, line);
		return 0;
	}
	return 1;
}

VdpauDisplayContext::VdpauDisplayContext(Window win, VdpauContext *vdpContext)
{
	m_vdp_presentation_queue_target = VDP_INVALID_HANDLE;
	m_vdp_presentation_queue = VDP_INVALID_HANDLE;
	m_vdp_display_surface = VDP_INVALID_HANDLE;
	m_vdp_output_surface_index = -1;
	for(int i = 0; i < OUTPUT_SURFACE_NUM; i++)
		m_vdp_outputSurface[i] = VDP_INVALID_HANDLE;
	m_pVdpContext = vdpContext;
	m_disp_win = win;
	if(m_pVdpContext == NULL)
	{
		fprintf(stderr, "no vdpau context, can not create display queue\n");
		return;
	}
	VdpStatus vdp_st;
	vdp_st = m_pVdpContext->vdp_presentation_queue_target_create_x11(m_pVdpContext->vdpDevice,
															  win,
															  &m_vdp_presentation_queue_target);
	if(vdp_st != VDP_STATUS_OK)
	{
		fprintf(stderr, "vdp_presentation_queue_target_create_x11 failed with: %d\n", vdp_st);
		return;
	}
	vdp_st = m_pVdpContext->vdp_presentation_queue_create(m_pVdpContext->vdpDevice,
														  m_vdp_presentation_queue_target,
														  &m_vdp_presentation_queue);
	if(vdp_st != VDP_STATUS_OK)
	{
		fprintf(stderr, "vdp_presentation_queeue_create failed with: %d\n", vdp_st);
		return;
	}
	VdpColor vdp_bg = {0.01, 0.02, 0.03, 0};
	vdp_st = m_pVdpContext->vdp_presentation_queue_set_background_color(m_vdp_presentation_queue, &vdp_bg);
	if(vdp_st != VDP_STATUS_OK)
	{
		fprintf(stderr, "vdp_presentation_queue_set_backgrounf_color failed with: %d\n", vdp_st);
		return;
	}
	for(int j = 0; j < OUTPUT_SURFACE_NUM; j++)
	{
		vdp_st = m_pVdpContext->vdp_output_surface_create(m_pVdpContext->vdpDevice,
														  VDP_RGBA_FORMAT_B8G8R8A8,
														  1920, 1080,
														  &m_fixed_outputSurface[0][j]);	
		if(vdp_st != VDP_STATUS_OK)
			fprintf(stderr, "vdp_output_surface_create failed with: %d\n", vdp_st);
		else
			fprintf(stderr, "vdp_output_surface_create: %d\n", m_fixed_outputSurface[0][j]);
	}
	for(int j = 0; j < OUTPUT_SURFACE_NUM; j++)
	{
		vdp_st = m_pVdpContext->vdp_output_surface_create(m_pVdpContext->vdpDevice,
														  VDP_RGBA_FORMAT_B8G8R8A8,
														  1080, 1920,
														  &m_fixed_outputSurface[1][j]);
		if(vdp_st != VDP_STATUS_OK)
			fprintf(stderr, "vdp_output_surface_create failed with: %d\n", vdp_st);
		else
			fprintf(stderr, "vdp_output_surface_create: %d\n", m_fixed_outputSurface[1][j]);
	}
	m_vdp_output_surface_used_index = -1;
	m_need_destroy_register = false;
	glGenTextures(OUTPUT_SURFACE_NUM, m_register_texture);
	for(int i = 0; i < OUTPUT_SURFACE_NUM; i++)
		m_register_surface[i] = VDP_INVALID_HANDLE;
	m_disp_width = 0;
	m_disp_height = 0;
	
	pthread_mutex_init(&m_outputSurfaceMutex, NULL);
	pthread_mutex_init(&testsurface, NULL);
}

VdpauDisplayContext::~VdpauDisplayContext()
{
	VdpStatus vdp_st;
	if(m_pVdpContext == NULL)
		return;
	if(m_vdp_presentation_queue != VDP_INVALID_HANDLE)
	{
		vdp_st = m_pVdpContext->vdp_presentation_queue_destroy(m_vdp_presentation_queue);
		if(vdp_st != VDP_STATUS_OK)
			fprintf(stderr, "vpd_presentation_queue_destroy failed with: %d\n", vdp_st);
		m_vdp_presentation_queue = VDP_INVALID_HANDLE;
	}
	if(m_vdp_presentation_queue_target != VDP_INVALID_HANDLE)
	{
		vdp_st = m_pVdpContext->vdp_presentation_queue_target_destroy(m_vdp_presentation_queue_target);
		if(vdp_st != VDP_STATUS_OK)
			fprintf(stderr, "vdp_presentation_queue_target_destroy failed with: %d\n", vdp_st);
		m_vdp_presentation_queue_target = VDP_INVALID_HANDLE;
	}
	
	destroyOutputSurface();

	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < OUTPUT_SURFACE_NUM; j++)
		{
			vdp_st = m_pVdpContext->vdp_output_surface_destroy(m_fixed_outputSurface[i][j]);
			if(vdp_st != VDP_STATUS_OK)
				fprintf(stderr, "vdp_output_surface_destroy failed with: %d\n", vdp_st);
		}
	}

	glDeleteTextures(OUTPUT_SURFACE_NUM, m_register_texture);
	pthread_mutex_destroy(&m_outputSurfaceMutex);
	pthread_mutex_destroy(&testsurface);
}

int VdpauDisplayContext::decoderVideo2OutputSurface(int width, int height,
												    VdpVideoSurface *history,
													VdpVideoSurface current,
													VdpVideoSurface future,
													VdpVideoMixer mixer)
{
	VdpStatus vdp_st;
	VdpTime t;

	m_vdp_output_surface_index = (m_vdp_output_surface_index + 1) % OUTPUT_SURFACE_NUM;
	m_vdp_display_surface = m_vdp_outputSurface[m_vdp_output_surface_index];
	vdp_st = m_pVdpContext->vdp_presentation_queue_block_until_surface_idle(m_vdp_presentation_queue,
																			m_vdp_outputSurface[m_vdp_output_surface_index],
																			&t);
	if(vdp_st != VDP_STATUS_OK)
	{
		fprintf(stderr, "vdp_presentation_queue_block_until_surface_idle failed with: %d\n", vdp_st);
		return -1;	
	}
	VdpVideoSurface histo[2] = {history[0], history[1]};
	VdpRect src_rect = {0, 0, width, height};
	VdpRect dest_video_rect = {0, 0, m_disp_width, m_disp_height};
	VdpVideoMixerPictureStructure structure = VDP_VIDEO_MIXER_PICTURE_STRUCTURE_FRAME;
	vdp_st = m_pVdpContext->vdp_video_mixer_render(mixer, VDP_INVALID_HANDLE, NULL, structure,
												   2, histo, current, 1, &future, &src_rect,
												   m_vdp_outputSurface[m_vdp_output_surface_index],
												   NULL, &dest_video_rect, 0, NULL);
	if(vdp_st != VDP_STATUS_OK)
	{
		fprintf(stderr, "vdp_video_mixer_render failed with: %d\n", vdp_st);
		return -1;
	}
	fprintf(stderr, "decoderVideo2OutputSurface finish\n");
	return 0;
}

int VdpauDisplayContext::decoderSurface2Texture(GLuint fbo, GLuint *inTex, int status)
{
	if(m_vdp_display_surface == VDP_INVALID_HANDLE)
		return -1;
	pthread_mutex_lock(&m_outputSurfaceMutex);
	int index = -1;
	index = get_surface_iter(m_vdp_display_surface);
	if(index != -1)
	{
		int buffer[4];
		int len = 0;

		m_pVdpContext->ptrglVDPAUGetSurfaceivNV(m_gl_surface[index], GL_SURFACE_STATE_NV, 4, &len, buffer);
		m_pVdpContext->ptrglVDPAUMapSurfacesNV(1, &(m_gl_surface[index]));
		*inTex = m_register_texture[index];
	}
	else
	{
		fprintf(stderr, "ptrglVdpauMapSurfaceNV failed\n");
		pthread_mutex_unlock(&m_outputSurfaceMutex);
		return -1;
	}
	pthread_mutex_unlock(&m_outputSurfaceMutex);
	return index;
}

int VdpauDisplayContext::releaseTexture(int index)
{
	if(index == -1)
		return 0;
	m_pVdpContext->ptrglVDPAUUnmapSurfacesNV(1, &(m_gl_surface[index]));
	return 1;
}

void VdpauDisplayContext::destroyOutputSurface()
{
	for(int i = 0; i < OUTPUT_SURFACE_NUM; i++)
	{
		if(m_register_surface[i] != VDP_INVALID_HANDLE)
		{
			remove_register_surface(m_register_surface[i]);
			fprintf(stderr, "remove_register_surface: %d\n", m_register_surface[i]);
		}
	}
}

void VdpauDisplayContext::releaseDisplayContext()
{
	destroyOutputSurface();
}

int VdpauDisplayContext::updateDisplayContext(int width, int height)
{
	pthread_mutex_lock(&m_outputSurfaceMutex);
	fprintf(stderr, "updateDisplayContext\n");

	int index = 1;
	m_disp_width = 1080;
	m_disp_height = 1920;
	if(width >= height)
	{
		index = 0;
		m_disp_width = 1920;
		m_disp_height = 1080;
	}
	if(m_vdp_output_surface_used_index != index && m_vdp_output_surface_used_index != -1)
	{
		m_need_destroy_register = true;	
	}
	m_vdp_output_surface_used_index = index;
	for(int i = 0; i < OUTPUT_SURFACE_NUM; i++)
	{
		m_vdp_outputSurface[i] = m_fixed_outputSurface[index][i];
		fprintf(stderr, "use output surface: %d\n", m_vdp_outputSurface[i]);
	}
	pthread_mutex_unlock(&m_outputSurfaceMutex);
	return 0;
}

int VdpauDisplayContext::get_surface_iter(VdpOutputSurface face)
{
	pthread_mutex_lock(&testsurface);
	int count = OUTPUT_SURFACE_NUM;
	if(m_need_destroy_register)
	{
		destroyOutputSurface();
		m_need_destroy_register = false;
	}
	int i = 0;
	for(i = 0; i < count; i++)
	{
		if(m_register_surface[i] == face)
		{
			fprintf(stderr, "m_register_surface[%d] = face(%d)\n", m_register_surface[i], face);
			pthread_mutex_unlock(&testsurface);
			return i;
		}
		else if(m_register_surface[i] == VDP_INVALID_HANDLE)
		{
			fprintf(stderr, "should register_surface:%d face(%d)\n", i, face);
			int ret = register_surface(i, face);
			if(ret == 0)
			{
				fprintf(stderr, "register_surface %d failed \n", i);
				break;
			}
			if(m_gl_surface[i] == NULL)
			{
				fprintf(stderr, "have no this surface......%d\n", i);
				break;
			}
			m_register_surface[i] = face;
			pthread_mutex_unlock(&testsurface);
			return i;	
		}
	}
	pthread_mutex_unlock(&testsurface);
	fprintf(stderr, "register surface failed...%d\n", face);
	return -1;
}

int VdpauDisplayContext::register_surface(int iter, VdpOutputSurface face)
{
	m_gl_surface[iter] = m_pVdpContext->ptrglVDPAURegisterOutputSurfaceNV((GLvoid*)(size_t)face,
																	     GL_TEXTURE_2D, 1, 
																		 &m_register_texture[iter]);
	int ret = check_error(__LINE__);
	fprintf(stderr, "ptrglVDPAURegisterOutputSurfaceNV %d to %d\n", face, iter);
	return ret;
}

int VdpauDisplayContext::remove_register_surface(VdpOutputSurface face)
{
	fprintf(stderr, "remove_register_surface %d\n", face);
	for(int i = 0; i < OUTPUT_SURFACE_NUM; i++)
	{
		if(m_register_surface[i] == face)
		{
			m_pVdpContext->ptrglVDPAUUnregisterSurfaceNV(m_gl_surface[i]);
			check_error(__LINE__);
			m_register_surface[i] = VDP_INVALID_HANDLE;
			return 1;
		}
	}
	return 0;
}
