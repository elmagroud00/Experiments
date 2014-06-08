#ifndef __VDPAUCONTEXT_H_
#define __VDPAUCONTEXT_H_

#include <vdpau/vdpau_x11.h>
#include <GL/glew.h>
#include <X11/Xlib.h>

class VdpauContext
{
public: 
	//VdpauContext(Display *d, int screen);
	VdpauContext();
	~VdpauContext();
	int init();
	void initVdpauInterop();
	VdpDevice vdpDevice;
private:
	void init_vdpau_interop();
	bool getFunc(int func, void **p);
	Display *vdpDisplay;
	int vdpScreen;	
public:
	VdpGetErrorString	*vdp_get_error_string;
	VdpGetProcAddress	*vdp_get_proc_address;
	VdpGetApiVersion	*vdp_get_api_version;
	VdpGetInformationString	*vdp_get_information_string;
	VdpDeviceDestroy	*vdp_device_destroy;
	VdpGenerateCSCMatrix	*vdp_generate_csc_matrix;
	VdpVideoSurfaceQueryCapabilities	*vdp_video_surface_query_capabilities;
	VdpVideoSurfaceQueryGetPutBitsYCbCrCapabilities	*vdp_video_surface_query_get_put_bits_y_cb_cr_capabilities;
	VdpVideoSurfaceCreate	*vdp_video_surface_create;
	VdpVideoSurfaceDestroy	*vdp_video_surface_destroy;
	VdpVideoSurfaceGetParameters	*vdp_video_surface_get_parameters;
	VdpVideoSurfaceGetBitsYCbCr		*vdp_video_surface_get_bits_y_cb_cr;
	VdpVideoSurfacePutBitsYCbCr		*vdp_video_surface_put_bits_y_cb_cr;
	VdpOutputSurfaceQueryCapabilities	*vdp_output_surface_query_capabilities;
	VdpOutputSurfaceQueryGetPutBitsNativeCapabilities	*vdp_output_surface_query_get_put_bits_native_capabilities;
	VdpOutputSurfaceQueryPutBitsIndexedCapabilities *vdp_output_surface_query_put_bits_indexed_capabilities;
	VdpOutputSurfaceQueryPutBitsYCbCrCapabilities	*vdp_output_surface_query_put_bits_y_cb_cr_capabilities;
	VdpOutputSurfaceCreate	*vdp_output_surface_create;
	VdpOutputSurfaceDestroy	*vdp_output_surface_destroy;
	VdpOutputSurfaceGetParameters	*vdp_output_surface_get_parameters;
	VdpOutputSurfaceGetBitsNative	*vdp_output_surface_get_bits_native;
	VdpOutputSurfacePutBitsNative	*vdp_output_surface_put_bits_native;
	VdpOutputSurfacePutBitsIndexed	*vdp_output_surface_put_bits_indexed;
	VdpOutputSurfacePutBitsYCbCr	*vdp_output_surface_put_bits_y_cb_cr;
	VdpBitmapSurfaceQueryCapabilities	*vdp_bitmap_surface_query_capabilities;
	VdpBitmapSurfaceCreate	*vdp_bitmap_surface_create;
//	VdpPresentationQueueGetTime				*vdp_presentation_queue_get_time;
	VdpBitmapSurfaceDestroy	*vdp_bitmap_surface_destroy;
	VdpBitmapSurfaceGetParameters	*vdp_bitmap_surface_get_parameters;
	VdpBitmapSurfacePutBitsNative	*vdp_bitmap_surface_put_bits_native;
	VdpOutputSurfaceRenderOutputSurface	*vdp_bitmap_surface_render_output_surface;
	VdpOutputSurfaceRenderBitmapSurface	*vdp_bitmap_surface_render_bitmap_surface;
	VdpDecoderQueryCapabilities	*vdp_decoder_query_capabilities;
	VdpDecoderCreate	*vdp_decoder_create;
	VdpDecoderDestroy	*vdp_decoder_destroy;
	VdpDecoderGetParameters	*vdp_decoder_get_parameters;
	VdpVideoMixerQueryAttributeSupport			*vdp_video_mixer_query_attribute_support;
	VdpDecoderRender	*vdp_decoder_render;
	VdpVideoMixerQueryFeatureSupport	*vdp_video_mixer_query_feature_support;
	VdpVideoMixerGetAttributeValues				*vdp_video_mixer_set_attribute_values;
	VdpVideoMixerQueryParameterSupport	*vdp_video_mixer_query_parameter_support;
	VdpOutputSurfaceRenderBitmapSurface			*vdp_output_surface_render_bitmap_surface;
	VdpVideoMixerQueryAttributeValueRange	*vdp_video_mixer_query_attribute_value_range;
	VdpVideoMixerQueryParameterValueRange	*vdp_video_mixer_query_parameter_value_range;
    VdpOutputSurfaceRenderOutputSurface			*vdp_output_surface_render_output_surface;
	VdpVideoMixerCreate	*vdp_video_mixer_create;
	VdpVideoMixerSetFeatureEnables	*vdp_video_mixer_set_feature_enables;
	VdpVideoMixerGetAttributeValues	*vdp_video_mixer_get_attribute_values;
	VdpVideoMixerGetParameterValues				*vdp_video_mixer_get_parameter_values;
	VdpVideoMixerGetFeatureSupport	*vdp_video_mixer_get_feature_support;
	VdpVideoMixerGetFeatureEnables	*vdp_video_mixer_get_feature_enables;
	VdpVideoMixerGetParameterValues	*vdp_video_mixer_get_parameterValues;
	VdpVideoMixerDestroy	*vdp_video_mixer_destroy;
	VdpVideoMixerRender		*vdp_video_mixer_render;
	//VdpPresentationQueueTargetCreateX11		*vdp_presentation_queue_target_create_x11;
	//VdpPresentationQueueTargetDestroy		*vdp_presentation_queue_target_destroy;
	//VdpPresentationQueueCreate	*vdp_presentation_queue_create;
	//VdpPresentationQueueDestroy	*vdp_presentation_queue_destroy;
	//VdpPresentationQueueSetBackgroundColor	*vdp_presentation_queue_set_background_color;
	//VdpPresentationQueueGetBackgroundColor	*vdp_presentation_queue_get_background_color;
	//VdpPresentationQueueGetTime	*vdp_presetnation_queue_get_time;
	//VdpPresentationQueueDisplay	*vdp_presentation_queue_display;
	//VdpPresentationQueueBlockUntilSurfaceIdle	*vdp_presentation_queue_block_until_surface_idle;
	//VdpPresentationQueueQuerySurfaceStatus	*vdp_presentation_queue_query_surface_status;
	VdpPreemptionCallbackRegister	*vdp_preemption_callback_register;

	PFNGLVDPAUINITNVPROC	ptrglVDPAUInitNV;
	PFNGLVDPAUFININVPROC	ptrglVDPAUFiniNV;
	PFNGLVDPAUREGISTEROUTPUTSURFACENVPROC	ptrglVDPAURegisterOutputSurfaceNV;
	PFNGLVDPAUUNREGISTERSURFACENVPROC	ptrglVDPAUUnregisterSurfaceNV;
	PFNGLVDPAUMAPSURFACESNVPROC	ptrglVDPAUMapSurfacesNV;
	PFNGLVDPAUUNMAPSURFACESNVPROC	ptrglVDPAUUnmapSurfacesNV;
	PFNGLVDPAUISSURFACENVPROC	ptrglVDPAUIsSurfaceNV;
	PFNGLVDPAUGETSURFACEIVNVPROC	ptrglVDPAUGetSurfaceivNV;
	PFNGLVDPAUSURFACEACCESSNVPROC	ptrglVDPAUSurfaceAccessNV;
};
#endif

