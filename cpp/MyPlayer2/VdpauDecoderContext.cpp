#include "VdpauDecoderContext.h"

VdpauDecoderContext::VdpauDecoderContext(VdpauContext *vdpContext)
{
	m_pVdpContext = vdpContext;
	m_pDisplayContext = NULL;
	if(vdpContext == NULL)
		return;
	m_vdp_pixfmt = -1;
	m_vdp_width = 0;
	m_vdp_height = 0;
	make_decoder_invalid();	
	pthread_mutex_init(&m_contextMutex, NULL);
}

VdpauDecoderContext::~VdpauDecoderContext()
{
	destroy_decoder_resource();
	make_decoder_invalid();
	pthread_mutex_destroy(&m_contextMutex);
}

void VdpauDecoderContext::make_decoder_invalid()
{
	m_vdp_decoder = VDP_INVALID_HANDLE;
	m_vdp_videoMixer = VDP_INVALID_HANDLE;
	for(int i = 0; i < VIDEO_SURFACES_NUM; i++)
	{
		memset(&m_surface_render[i], 0x00, sizeof(m_surface_render[i]));
		m_surface_render[i].surface = VDP_INVALID_HANDLE;
	}
	m_vdp_surface_render_index = 0;
	initHistorySurface();
}

void VdpauDecoderContext::destroy_decoder_resource()
{
	VdpStatus vdp_st;
	if(m_pVdpContext == NULL)
		fprintf(stderr, "no vdpau context find\n");
	if(m_vdp_decoder != VDP_INVALID_HANDLE)
		vdp_st = m_pVdpContext->vdp_decoder_destroy(m_vdp_decoder);
	if(m_vdp_videoMixer != VDP_INVALID_HANDLE)
		vdp_st = m_pVdpContext->vdp_video_mixer_destroy(m_vdp_videoMixer);
	for(int i = 0; i < VIDEO_SURFACES_NUM; i++)
	{
		if(m_surface_render[i].surface != VDP_INVALID_HANDLE)
		{
			vdp_st = m_pVdpContext->vdp_video_surface_destroy(m_surface_render[i].surface);
			fprintf(stderr, "vdp_surface_destroy: %d end with %d\n", m_surface_render[i].surface, vdp_st);
		}
	}
}

void VdpauDecoderContext::updateframe(AVFrame *frame)
{
	pthread_mutex_lock(&m_contextMutex);
	struct vdpau_render_state *render = (struct vdpau_render_state*)frame->data[0];
	VdpVideoSurface video_surface = render->surface;
	
	push_int_surface(video_surface);
	if(m_history_surface[1] != VDP_INVALID_HANDLE && m_pDisplayContext != NULL)
	{
		fprintf(stderr, "decoderVideo2OutputSurface begin\n");
		m_pDisplayContext->decoderVideo2OutputSurface(m_vdp_width, m_vdp_height,
													  &m_history_surface[2], m_history_surface[1], m_history_surface[0],
													  m_vdp_videoMixer);	
	}
	pthread_mutex_unlock(&m_contextMutex);
}

void VdpauDecoderContext::setDisplayHandle(VdpauDisplayContext *context)
{
	m_pDisplayContext = context;
}

void VdpauDecoderContext::push_int_surface(VdpVideoSurface surface)
{
	for(int i = HISTORY_VIDEO_NUM - 1; i > 0; i--)
		m_history_surface[i] = m_history_surface[i - 1];
	m_history_surface[0] = surface;
}

void VdpauDecoderContext::initHistorySurface()
{
	for(int i = 0; i < HISTORY_VIDEO_NUM; i++)
		m_history_surface[i] = VDP_INVALID_HANDLE;
}

int VdpauDecoderContext::update_csc_matrix(VdpVideoMixer mixer)
{
	VdpStatus vdp_st;
	VdpCSCMatrix	matrix;
	int csp = 1;
	static const VdpVideoMixerAttribute attr[] = {VDP_VIDEO_MIXER_ATTRIBUTE_CSC_MATRIX};
	const void *attr_values[] = {&matrix}; static const VdpColorStandard vdp_colors[] = {0, VDP_COLOR_STANDARD_ITUR_BT_601, VDP_COLOR_STANDARD_ITUR_BT_709,
												  VDP_COLOR_STANDARD_SMPTE_240M};
	static VdpProcamp procamp;
	procamp.struct_version = VDP_PROCAMP_VERSION;
	procamp.brightness = 0.0;
	procamp.contrast = 1.0;
	procamp.saturation = 1.0;
	procamp.hue = 0.0;

	vdp_st = m_pVdpContext->vdp_generate_csc_matrix(&procamp, vdp_colors[csp], &matrix);
	if(vdp_st != VDP_STATUS_OK)
	{
		fprintf(stderr, "vdp_generate_csc_matrix failed with %d\n", vdp_st);
		return -1;
	}
	vdp_st = m_pVdpContext->vdp_video_mixer_set_attribute_values(mixer, 1, attr, (void * const*)attr_values);
	if(vdp_st != VDP_STATUS_OK)
	{
		fprintf(stderr, "vdp_vdieo_mixer_attribute_values failed with %d\n", vdp_st);
		return -1;
	}
	return 0;
}

int VdpauDecoderContext::create_vdp_mixer(VdpChromaType vdp_chroma_type, int width, int height)
{
	VdpStatus vdp_st;
	if(m_pVdpContext == NULL)
		fprintf(stderr, "not found vdpau context\n");
	VdpVideoMixerParameter params[] = {VDP_VIDEO_MIXER_PARAMETER_VIDEO_SURFACE_WIDTH,
									   VDP_VIDEO_MIXER_PARAMETER_VIDEO_SURFACE_HEIGHT,
									   VDP_VIDEO_MIXER_PARAMETER_CHROMA_TYPE};
   VdpVideoMixerFeature features[] = {VDP_VIDEO_MIXER_FEATURE_DEINTERLACE_TEMPORAL};
   VdpBool features_enables[] = {VDP_TRUE, VDP_TRUE};
   void const *param_values[] = {&width, &height, &vdp_chroma_type};
   vdp_st = m_pVdpContext->vdp_video_mixer_create(m_pVdpContext->vdpDevice,
		   										  1, features,
												  3, params, param_values,
												  &m_vdp_videoMixer);
   if(vdp_st != VDP_STATUS_OK)
	{
		fprintf(stderr, "vdp_video_mixer_create failed with %d\n", vdp_st);
		return -1;
	}	
	fprintf(stderr, "vdp_video_mixer_create success: handle = %d\n", m_vdp_videoMixer);
	m_pVdpContext->vdp_video_mixer_set_feature_enables(m_vdp_videoMixer, 2, features, features_enables);
	update_csc_matrix(m_vdp_videoMixer);
	return 0;
}

int VdpauDecoderContext::create_surface_resource(int width, int height)
{
	VdpStatus vdp_st;
	for(int i = 0; i < VIDEO_SURFACES_NUM; i++)
	{
		vdp_st = m_pVdpContext->vdp_video_surface_create(m_pVdpContext->vdpDevice, VDP_CHROMA_TYPE_420,
														 width, height, &m_surface_render[i].surface);
		if(vdp_st != VDP_STATUS_OK)
		{
			fprintf(stderr, "vdp_video_surface_create failed with %d\n", vdp_st);
			m_pVdpContext->vdp_video_surface_destroy(m_surface_render[i].surface);
			m_surface_render[i].surface = VDP_INVALID_HANDLE;
		    return -1;	
		}
		fprintf(stderr, "create video surface :%d %d %d\n", width ,height, m_surface_render[i].surface);
	}
	return 0;
}

int VdpauDecoderContext::create_decoder_resource(int pixfmt, int max_refs, int width, int height)
{
	if(m_pVdpContext == NULL)
		fprintf(stderr, "no vdpau context, create_decoder_resource failed\n");
	VdpDecoderProfile profile;
	if(pixfmt == PIX_FMT_VDPAU_H264)
		profile = VDP_DECODER_PROFILE_H264_HIGH;
	else
		fprintf(stderr, "unable to deal with pixfmt: %d\n", pixfmt);
	create_vdp_mixer(VDP_CHROMA_TYPE_420, width, height);
	VdpStatus vdp_st;
	vdp_st = m_pVdpContext->vdp_decoder_create(m_pVdpContext->vdpDevice, profile, width, height, max_refs, &m_vdp_decoder);
	if(vdp_st != VDP_STATUS_OK)
	{
		fprintf(stderr, "vdp_decode_create failed with %d\n", vdp_st);
		return -1;
	}
	fprintf(stderr, "vdp_decoder_create: %d\n", m_vdp_decoder);
	create_surface_resource(width, height);
	return 0;
}

int VdpauDecoderContext::updateDecoderContext(int pixfmt, int width, int height)
{
	if(m_pVdpContext == NULL)
	{
		fprintf(stderr, "no vdpau context\n");
		return -1;
	}	
	pthread_mutex_lock(&m_contextMutex);
	if(pixfmt != m_vdp_pixfmt || width != m_vdp_width || height != m_vdp_height)
	{
		destroy_decoder_resource();
		make_decoder_invalid();
		create_decoder_resource(pixfmt, 16, width, height);
	}
	initHistorySurface();
	pthread_mutex_unlock(&m_contextMutex);
	m_vdp_pixfmt = pixfmt;
	m_vdp_width = width;
	m_vdp_height = height;
	b_age = ip_age[0] = ip_age[1] = 256 * 256 * 256 * 64;
	return 0;
}

int VdpauDecoderContext::decoder_render(struct vdpau_render_state *rndr)
{
	VdpStatus vdp_st;
	if(m_pVdpContext == NULL)
	{
		fprintf(stderr, "no vdpau context\n");
		return -1;
	}
	vdp_st = m_pVdpContext->vdp_decoder_render(m_vdp_decoder, rndr->surface,
											   (VdpPictureInfo const *)&(rndr->info),
											   rndr->bitstream_buffers_used,
											   rndr->bitstream_buffers);
	if(vdp_st != VDP_STATUS_OK)
	{
		fprintf(stderr, "vdp_decoder_render failed with %d\n", vdp_st);
		return -1;
	}
	return 0;
}

struct vdpau_render_state *VdpauDecoderContext::get_video_surface()
{
	VdpStatus vdp_st;
	struct vdpau_render_state *rndr = NULL;
	if((m_surface_render[m_vdp_surface_render_index].surface == VDP_INVALID_HANDLE) && (m_pVdpContext != NULL))
	{
		vdp_st = m_pVdpContext->vdp_video_surface_create(m_pVdpContext->vdpDevice, VDP_CHROMA_TYPE_420,
														 m_vdp_width, m_vdp_height,
														 &m_surface_render[m_vdp_surface_render_index].surface);
		if(vdp_st != VDP_STATUS_OK)
		{
			fprintf(stderr, "vdp_video_surface_create failed with: %d\n", vdp_st);
			m_surface_render[m_vdp_surface_render_index].surface = VDP_INVALID_HANDLE;
			return NULL;
		}
	}
	if(m_surface_render[m_vdp_surface_render_index].surface == VDP_INVALID_HANDLE)
	{
		fprintf(stderr, "unable to create video surface, no vdpau device context\n");
		return NULL;
	}
	rndr = &m_surface_render[m_vdp_surface_render_index];
	m_vdp_surface_render_index = (m_vdp_surface_render_index + 1) % VIDEO_SURFACES_NUM;
	return rndr;
}

int decoder_get_buffer(struct AVCodecContext *c, AVFrame *pic)
{
	VdpauDecoderContext *decoderContext = (VdpauDecoderContext*)c->opaque;
	struct vdpau_render_state *rndr = decoderContext->get_video_surface();
	int tryCount = 0;
	while((rndr == NULL) && tryCount < (VIDEO_SURFACES_NUM / 2))
	{
		rndr = decoderContext->get_video_surface();
		tryCount++;
	}
	pic->data[0] = (uint8_t*)rndr;
	if(pic->reference)
	{
		decoderContext->ip_age[0] = decoderContext->ip_age[1] + 1;
		decoderContext->ip_age[1] = 1;
		decoderContext->b_age++;
	}
	else
	{
		decoderContext->ip_age[0]++;
		decoderContext->ip_age[1]++;
		decoderContext->b_age = 1;
	}
	pic->type = FF_BUFFER_TYPE_USER;
	return 0;
}

void decoder_release_buffer(struct AVCodecContext *c, AVFrame *pic)
{
	struct vdpau_render_state *rndr = (struct vdpau_render_state*)pic->data[0];
	rndr->state &= ~FF_VDPAU_STATE_USED_FOR_REFERENCE;
	pic->data[0] = NULL;	
}

void decoder_draw_horiz_band(struct AVCodecContext *c, const AVFrame *frame, int offset[4], int y, int type, int h)
{
	struct vdpau_render_state *rndr = (struct vdpau_render_state*)frame->data[0];
	VdpauDecoderContext *decoderContext = (VdpauDecoderContext*)c->opaque;
	decoderContext->decoder_render(rndr);
}

enum PixelFormat decoder_get_format(AVCodecContext *codecCtx, const enum PixelFormat *pix_fmt)
{
	fprintf(stderr, "pix fmt list is:\n");
	for(int i = 0; pix_fmt[i] != PIX_FMT_NONE; i++)
		fprintf(stderr, "%d\t", pix_fmt[i]);
	return pix_fmt[0];
}








