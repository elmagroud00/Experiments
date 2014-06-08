#ifndef __VDPAUCONTEXT_H_
#define __VDPAUCONTEXT_H_

#include <vdpau/vdpau_x11.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>

namespace mx {

class VdpauContext {
public:
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
	VdpGetErrorString *vdp_get_error_string;
	VdpGetProcAddress *vdp_get_proc_address;
	VdpGetInformationString	*vdp_get_information_string;
	VdpDeviceDestroy *vdp_device_destroy;
	VdpGenerateCSCMatrix *vdp_generate_csc_matrix;
	VdpVideoSurfaceCreate *vdp_video_surface_create;
	VdpVideoSurfaceDestroy *vdp_video_surface_destroy;
	VdpOutputSurfaceCreate	*vdp_output_surface_create;
	VdpOutputSurfaceDestroy	*vdp_output_surface_destroy;
	VdpBitmapSurfaceCreate	*vdp_bitmap_surface_create;
	VdpBitmapSurfaceDestroy	*vdp_bitmap_surface_destroy;
	VdpDecoderCreate *vdp_decoder_create;
	VdpDecoderDestroy *vdp_decoder_destroy;
	VdpDecoderRender *vdp_decoder_render;
	VdpVideoMixerCreate	*vdp_video_mixer_create;
	VdpVideoMixerSetFeatureEnables *vdp_video_mixer_set_feature_enables;
	VdpVideoMixerGetAttributeValues	*vdp_video_mixer_set_attribute_values;
	VdpVideoMixerDestroy *vdp_video_mixer_destroy;
	VdpVideoMixerRender	 *vdp_video_mixer_render;
	VdpPreemptionCallbackRegister *vdp_preemption_callback_register;

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

} /* namespace mx */

#endif /* __VDPAUCONTEXT_H_ */

