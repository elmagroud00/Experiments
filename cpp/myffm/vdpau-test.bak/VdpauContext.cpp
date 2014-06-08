#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#include "VdpauContext.h"

VdpauContext::VdpauContext(Display *d, int screen)
{
	vdpDisplay = d;
	vdpScreen = screen;
	vdpDevice = VDP_INVALID_HANDLE;
	ptrglVDPAUInitNV = NULL;
	ptrglVDPAUFiniNV = NULL;
	ptrglVDPAURegisterOutputSurfaceNV = NULL;
	ptrglVDPAUUnregisterSurfaceNV = NULL;
	ptrglVDPAUMapSurfacesNV = NULL;
	ptrglVDPAUUnmapSurfacesNV = NULL;
	ptrglVDPAUIsSurfaceNV = NULL;
	ptrglVDPAUGetSurfaceivNV = NULL;
	ptrglVDPAUSurfaceAccessNV = NULL;
}

VdpauContext::~VdpauContext()
{
	VdpStatus vdp_st;
	if(vdpDevice != VDP_INVALID_HANDLE)
	{
		vdp_st = vdp_device_destroy(vdpDevice);
		if(vdp_st != VDP_STATUS_OK)
			fprintf(stderr, "vdp_device_destroy failed\n");
		ptrglVDPAUFiniNV();
	}
}

bool VdpauContext::getFunc(int func, void **p)
{
	VdpStatus vdp_st = vdp_get_proc_address(vdpDevice, func, p);
	if(vdp_st != VDP_STATUS_OK)
		return false;
	return true;
}

void VdpauContext::initVdpauInterop()
{
	if(ptrglVDPAUInitNV == NULL)
		init_vdpau_interop();
	ptrglVDPAUInitNV((const GLvoid*)vdpDevice, (const GLvoid*)vdp_get_proc_address);
}
int VdpauContext::init()
{
	vdp_get_proc_address = NULL;
	VdpStatus vdp_st;
	if(vdpDevice != VDP_INVALID_HANDLE)
	{
		vdp_st = vdp_device_destroy(vdpDevice);
		if(vdp_st != VDP_STATUS_OK)
			fprintf(stderr, "%d destroy device vdpau failed: vdp_st = %d\n", __LINE__, vdp_st);
	}
	vdp_st = vdp_device_create_x11(vdpDisplay, vdpScreen, &vdpDevice, &vdp_get_proc_address);
	if(vdp_st != VDP_STATUS_OK)
	{
		fprintf(stderr, "%d create device vdpau failed: vdp_st = %d\n", __LINE__, vdp_st);
		return -1;
	}
	if (!getFunc( VDP_FUNC_ID_GET_ERROR_STRING , (void**)&vdp_get_error_string))
        printf("Can't get VDP_FUNC_ID_GET_ERROR_STRING address !!");

    if (!getFunc( VDP_FUNC_ID_GET_API_VERSION , (void**)&vdp_get_api_version))
        printf("Can't get VDP_FUNC_ID_GET_API_VERSION address !!");

    if (!getFunc( VDP_FUNC_ID_GET_INFORMATION_STRING , (void**)&vdp_get_information_string))
        printf("Can't get VDP_FUNC_ID_GET_INFORMATION_STRING address !!");

    if (!getFunc( VDP_FUNC_ID_DEVICE_DESTROY , (void**)&vdp_device_destroy))
        printf("Can't get VDP_FUNC_ID_DEVICE_DESTROY address !!");

    if (!getFunc( VDP_FUNC_ID_GENERATE_CSC_MATRIX , (void**)&vdp_generate_csc_matrix))
        printf("Can't get VDP_FUNC_ID_GENERATE_CSC_MATRIX address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_SURFACE_QUERY_CAPABILITIES , (void**)&vdp_video_surface_query_capabilities))
        printf("Can't get VDP_FUNC_ID_VIDEO_SURFACE_QUERY_CAPABILITIES address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_SURFACE_QUERY_GET_PUT_BITS_Y_CB_CR_CAPABILITIES , (void**)&vdp_video_surface_query_get_put_bits_y_cb_cr_capabilities))
        printf("Can't get VDP_FUNC_ID_VIDEO_SURFACE_QUERY_GET_PUT_BITS_Y_CB_CR_CAPABILITIES address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_SURFACE_CREATE , (void**)&vdp_video_surface_create))
        printf("Can't get VDP_FUNC_ID_VIDEO_SURFACE_CREATE address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_SURFACE_DESTROY , (void**)&vdp_video_surface_destroy))
        printf("Can't get VDP_FUNC_ID_VIDEO_SURFACE_DESTROY address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_SURFACE_GET_PARAMETERS , (void**)&vdp_video_surface_get_parameters))
        printf("Can't get VDP_FUNC_ID_VIDEO_SURFACE_GET_PARAMETERS address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_SURFACE_GET_BITS_Y_CB_CR , (void**)&vdp_video_surface_get_bits_y_cb_cr))
        printf("Can't get VDP_FUNC_ID_VIDEO_SURFACE_GET_BITS_Y_CB_CR address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_SURFACE_PUT_BITS_Y_CB_CR , (void**)&vdp_video_surface_put_bits_y_cb_cr))
        printf("Can't get VDP_FUNC_ID_VIDEO_SURFACE_PUT_BITS_Y_CB_CR address !!");

    if (!getFunc( VDP_FUNC_ID_OUTPUT_SURFACE_QUERY_CAPABILITIES , (void**)&vdp_output_surface_query_capabilities))
        printf("Can't get VDP_FUNC_ID_OUTPUT_SURFACE_QUERY_CAPABILITIES address !!");

    if (!getFunc( VDP_FUNC_ID_OUTPUT_SURFACE_QUERY_GET_PUT_BITS_NATIVE_CAPABILITIES , (void**)&vdp_output_surface_query_get_put_bits_native_capabilities))
        printf("Can't get VDP_FUNC_ID_OUTPUT_SURFACE_QUERY_GET_PUT_BITS_NATIVE_CAPABILITIES address !!");

    if (!getFunc( VDP_FUNC_ID_OUTPUT_SURFACE_QUERY_PUT_BITS_INDEXED_CAPABILITIES , (void**)&vdp_output_surface_query_put_bits_indexed_capabilities))
        printf("Can't get VDP_FUNC_ID_OUTPUT_SURFACE_QUERY_PUT_BITS_INDEXED_CAPABILITIES address !!");

    if (!getFunc( VDP_FUNC_ID_OUTPUT_SURFACE_QUERY_PUT_BITS_Y_CB_CR_CAPABILITIES , (void**)&vdp_output_surface_query_put_bits_y_cb_cr_capabilities))
        printf("Can't get VDP_FUNC_ID_OUTPUT_SURFACE_QUERY_PUT_BITS_Y_CB_CR_CAPABILITIES address !!");

    if (!getFunc( VDP_FUNC_ID_OUTPUT_SURFACE_CREATE , (void**)&vdp_output_surface_create))
        printf("Can't get VDP_FUNC_ID_OUTPUT_SURFACE_CREATE address !!");

    if (!getFunc( VDP_FUNC_ID_OUTPUT_SURFACE_DESTROY , (void**)&vdp_output_surface_destroy))
        printf("Can't get VDP_FUNC_ID_OUTPUT_SURFACE_DESTROY address !!");

    if (!getFunc( VDP_FUNC_ID_OUTPUT_SURFACE_GET_PARAMETERS , (void**)&vdp_output_surface_get_parameters))
        printf("Can't get VDP_FUNC_ID_OUTPUT_SURFACE_GET_PARAMETERS address !!");

    if (!getFunc( VDP_FUNC_ID_OUTPUT_SURFACE_GET_BITS_NATIVE , (void**)&vdp_output_surface_get_bits_native))
        printf("Can't get VDP_FUNC_ID_OUTPUT_SURFACE_GET_BITS_NATIVE address !!");

    if (!getFunc( VDP_FUNC_ID_OUTPUT_SURFACE_PUT_BITS_NATIVE , (void**)&vdp_output_surface_put_bits_native))
        printf("Can't get VDP_FUNC_ID_OUTPUT_SURFACE_PUT_BITS_NATIVE address !!");

    if (!getFunc( VDP_FUNC_ID_OUTPUT_SURFACE_PUT_BITS_INDEXED , (void**)&vdp_output_surface_put_bits_indexed))
        printf("Can't get VDP_FUNC_ID_OUTPUT_SURFACE_PUT_BITS_INDEXED address !!");

    if (!getFunc( VDP_FUNC_ID_OUTPUT_SURFACE_PUT_BITS_Y_CB_CR , (void**)&vdp_output_surface_put_bits_y_cb_cr))
        printf("Can't get VDP_FUNC_ID_OUTPUT_SURFACE_PUT_BITS_Y_CB_CR address !!");

    if (!getFunc( VDP_FUNC_ID_BITMAP_SURFACE_QUERY_CAPABILITIES , (void**)&vdp_bitmap_surface_query_capabilities))
        printf("Can't get VDP_FUNC_ID_BITMAP_SURFACE_QUERY_CAPABILITIES address !!");

    if (!getFunc( VDP_FUNC_ID_BITMAP_SURFACE_CREATE , (void**)&vdp_bitmap_surface_create))
        printf("Can't get VDP_FUNC_ID_BITMAP_SURFACE_CREATE address !!");

    if (!getFunc( VDP_FUNC_ID_BITMAP_SURFACE_DESTROY , (void**)&vdp_bitmap_surface_destroy))
        printf("Can't get VDP_FUNC_ID_BITMAP_SURFACE_DESTROY address !!");

    if (!getFunc( VDP_FUNC_ID_BITMAP_SURFACE_GET_PARAMETERS , (void**)&vdp_bitmap_surface_get_parameters))
        printf("Can't get VDP_FUNC_ID_BITMAP_SURFACE_GET_PARAMETERS address !!");

    if (!getFunc( VDP_FUNC_ID_BITMAP_SURFACE_PUT_BITS_NATIVE , (void**)&vdp_bitmap_surface_put_bits_native))
        printf("Can't get VDP_FUNC_ID_BITMAP_SURFACE_PUT_BITS_NATIVE address !!");

    if (!getFunc( VDP_FUNC_ID_OUTPUT_SURFACE_RENDER_OUTPUT_SURFACE , (void**)&vdp_output_surface_render_output_surface))
        printf("Can't get VDP_FUNC_ID_OUTPUT_SURFACE_RENDER_OUTPUT_SURFACE address !!");

    if (!getFunc( VDP_FUNC_ID_OUTPUT_SURFACE_RENDER_BITMAP_SURFACE , (void**)&vdp_output_surface_render_bitmap_surface))
        printf("Can't get VDP_FUNC_ID_OUTPUT_SURFACE_RENDER_BITMAP_SURFACE address !!");

    if (!getFunc( VDP_FUNC_ID_DECODER_QUERY_CAPABILITIES , (void**)&vdp_decoder_query_capabilities))
        printf("Can't get VDP_FUNC_ID_DECODER_QUERY_CAPABILITIES address !!");

    if (!getFunc( VDP_FUNC_ID_DECODER_CREATE , (void**)&vdp_decoder_create))
        printf("Can't get VDP_FUNC_ID_DECODER_CREATE address !!");

    if (!getFunc( VDP_FUNC_ID_DECODER_DESTROY , (void**)&vdp_decoder_destroy))
        printf("Can't get VDP_FUNC_ID_DECODER_DESTROY address !!");

    if (!getFunc( VDP_FUNC_ID_DECODER_GET_PARAMETERS , (void**)&vdp_decoder_get_parameters))
        printf("Can't get VDP_FUNC_ID_DECODER_GET_PARAMETERS address !!");

    if (!getFunc( VDP_FUNC_ID_DECODER_RENDER , (void**)&vdp_decoder_render))
        printf("Can't get VDP_FUNC_ID_DECODER_RENDER address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_QUERY_FEATURE_SUPPORT , (void**)&vdp_video_mixer_query_feature_support))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_QUERY_FEATURE_SUPPORT address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_QUERY_PARAMETER_SUPPORT , (void**)&vdp_video_mixer_query_parameter_support))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_QUERY_PARAMETER_SUPPORT address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_QUERY_ATTRIBUTE_SUPPORT , (void**)&vdp_video_mixer_query_attribute_support))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_QUERY_ATTRIBUTE_SUPPORT address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_QUERY_PARAMETER_VALUE_RANGE , (void**)&vdp_video_mixer_query_parameter_value_range))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_QUERY_PARAMETER_VALUE_RANGE address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_QUERY_ATTRIBUTE_VALUE_RANGE , (void**)&vdp_video_mixer_query_attribute_value_range))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_QUERY_ATTRIBUTE_VALUE_RANGE address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_CREATE , (void**)&vdp_video_mixer_create))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_CREATE address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_SET_FEATURE_ENABLES , (void**)&vdp_video_mixer_set_feature_enables))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_SET_FEATURE_ENABLES address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_SET_ATTRIBUTE_VALUES , (void**)&vdp_video_mixer_set_attribute_values))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_SET_ATTRIBUTE_VALUES address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_GET_FEATURE_SUPPORT , (void**)&vdp_video_mixer_get_feature_support))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_GET_FEATURE_SUPPORT address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_GET_FEATURE_ENABLES , (void**)&vdp_video_mixer_get_feature_enables))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_GET_FEATURE_ENABLES address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_GET_PARAMETER_VALUES , (void**)&vdp_video_mixer_get_parameter_values))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_GET_PARAMETER_VALUES address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_GET_ATTRIBUTE_VALUES , (void**)&vdp_video_mixer_get_attribute_values))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_GET_ATTRIBUTE_VALUES address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_DESTROY , (void**)&vdp_video_mixer_destroy))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_DESTROY address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_RENDER , (void**)&vdp_video_mixer_render))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_RENDER address !!");

    if (!getFunc( VDP_FUNC_ID_PRESENTATION_QUEUE_TARGET_CREATE_X11 , (void**)&vdp_presentation_queue_target_create_x11))
        printf("Can't get VDP_FUNC_ID_PRESENTATION_QUEUE_TARGET_CREATE_X11 address !!");

    if (!getFunc( VDP_FUNC_ID_PRESENTATION_QUEUE_TARGET_DESTROY , (void**)&vdp_presentation_queue_target_destroy))
        printf("Can't get VDP_FUNC_ID_PRESENTATION_QUEUE_TARGET_DESTROY address !!");

    if (!getFunc( VDP_FUNC_ID_PRESENTATION_QUEUE_CREATE , (void**)&vdp_presentation_queue_create))
        printf("Can't get VDP_FUNC_ID_PRESENTATION_QUEUE_CREATE address !!");

    if (!getFunc( VDP_FUNC_ID_PRESENTATION_QUEUE_DESTROY , (void**)&vdp_presentation_queue_destroy))
        printf("Can't get VDP_FUNC_ID_PRESENTATION_QUEUE_DESTROY address !!");

    if (!getFunc( VDP_FUNC_ID_PRESENTATION_QUEUE_SET_BACKGROUND_COLOR , (void**)&vdp_presentation_queue_set_background_color))
        printf("Can't get VDP_FUNC_ID_PRESENTATION_QUEUE_SET_BACKGROUND_COLOR address !!");

    if (!getFunc( VDP_FUNC_ID_PRESENTATION_QUEUE_GET_BACKGROUND_COLOR , (void**)&vdp_presentation_queue_get_background_color))
        printf("Can't get VDP_FUNC_ID_PRESENTATION_QUEUE_GET_BACKGROUND_COLOR address !!");

    if (!getFunc( VDP_FUNC_ID_PRESENTATION_QUEUE_GET_TIME , (void**)&vdp_presentation_queue_get_time))
        printf("Can't get VDP_FUNC_ID_PRESENTATION_QUEUE_GET_TIME address !!");

    if (!getFunc( VDP_FUNC_ID_PRESENTATION_QUEUE_DISPLAY , (void**)&vdp_presentation_queue_display))
        printf("Can't get VDP_FUNC_ID_PRESENTATION_QUEUE_DISPLAY address !!");

    if (!getFunc( VDP_FUNC_ID_PRESENTATION_QUEUE_BLOCK_UNTIL_SURFACE_IDLE , (void**)&vdp_presentation_queue_block_until_surface_idle))
        printf("Can't get VDP_FUNC_ID_PRESENTATION_QUEUE_BLOCK_UNTIL_SURFACE_IDLE address !!");

    if (!getFunc( VDP_FUNC_ID_PRESENTATION_QUEUE_QUERY_SURFACE_STATUS , (void**)&vdp_presentation_queue_query_surface_status))
        printf("Can't get VDP_FUNC_ID_PRESENTATION_QUEUE_QUERY_SURFACE_STATUS address !!");

    if (!getFunc( VDP_FUNC_ID_PREEMPTION_CALLBACK_REGISTER , (void**)&vdp_preemption_callback_register))
        printf("Can't get VDP_FUNC_ID_PREEMPTION_CALLBACK_REGISTER address !!");
	
	init_vdpau_interop();																																								      
	ptrglVDPAUInitNV((const GLvoid*)vdpDevice, (const GLvoid*)vdp_get_proc_address);
	return 0;
}

void VdpauContext::init_vdpau_interop()
{
    void * dlh = dlopen("/usr/lib/libGLEW.so", RTLD_LAZY);
    if (!dlh) {
        printf("ERROR at %s:%d: dlopen(NULL) failed: %s\n", __FILE__, __LINE__, dlerror());
        return;
    }

    ptrglVDPAUInitNV = (PFNGLVDPAUINITNVPROC)(uintptr_t)dlsym(dlh, "glVDPAUInitNV");
    if (!ptrglVDPAUInitNV) {
        printf("ERROR at %s:%d: dlsym() failed: %s\n", __FILE__, __LINE__, dlerror());
        return;
    }

    ptrglVDPAUFiniNV = (PFNGLVDPAUFININVPROC)(uintptr_t)dlsym(dlh, "glVDPAUFiniNV");
    if (!ptrglVDPAUFiniNV) {
        printf("ERROR at %s:%d: dlsym() failed: %s\n", __FILE__, __LINE__, dlerror());
        return;
    }

    ptrglVDPAURegisterOutputSurfaceNV = (PFNGLVDPAUREGISTEROUTPUTSURFACENVPROC)(uintptr_t)dlsym(dlh, "glVDPAURegisterOutputSurfaceNV");
    if (!ptrglVDPAURegisterOutputSurfaceNV) {
        printf("ERROR at %s:%d: dlsym() failed: %s\n", __FILE__, __LINE__, dlerror());
        return;
    }

    ptrglVDPAUUnregisterSurfaceNV = (PFNGLVDPAUUNREGISTERSURFACENVPROC)(uintptr_t)dlsym(dlh, "glVDPAUUnregisterSurfaceNV");
    if (!ptrglVDPAUUnregisterSurfaceNV) {
        printf("ERROR at %s:%d: dlsym() failed: %s\n", __FILE__, __LINE__, dlerror());
        return;
    }

    ptrglVDPAUMapSurfacesNV = (PFNGLVDPAUMAPSURFACESNVPROC)(uintptr_t)dlsym(dlh, "glVDPAUMapSurfacesNV");
    if (!ptrglVDPAUMapSurfacesNV) {
        printf("ERROR at %s:%d: dlsym() failed: %s\n", __FILE__, __LINE__, dlerror());
        return;
    }

    ptrglVDPAUIsSurfaceNV = (PFNGLVDPAUISSURFACENVPROC)(uintptr_t)dlsym(dlh, "glVDPAUIsSurfaceNV");
    if (!ptrglVDPAUIsSurfaceNV) {
        printf("ERROR at %s:%d: dlsym() failed: %s\n", __FILE__, __LINE__, dlerror());
        return;
    }
    ptrglVDPAUUnmapSurfacesNV = (PFNGLVDPAUUNMAPSURFACESNVPROC)(uintptr_t)dlsym(dlh, "glVDPAUUnmapSurfacesNV");
    if (!ptrglVDPAUUnmapSurfacesNV) {
        printf("ERROR at %s:%d: dlsym() failed: %s\n", __FILE__, __LINE__, dlerror());
        return;
    }
    ptrglVDPAUGetSurfaceivNV = (PFNGLVDPAUGETSURFACEIVNVPROC)(uintptr_t)dlsym(dlh, "glVDPAUGetSurfaceivNV");
    if (!ptrglVDPAUUnmapSurfacesNV) {
        printf("ERROR at %s:%d: dlsym() failed: %s\n", __FILE__, __LINE__, dlerror());
        return;
    }
    ptrglVDPAUSurfaceAccessNV = (PFNGLVDPAUSURFACEACCESSNVPROC)(uintptr_t)dlsym(dlh,"glVDPAUSurfaceAccessNV");
    if(!ptrglVDPAUSurfaceAccessNV )
    {
        printf("ERROR at %s:%d: dlsym() failed: %s\n", __FILE__, __LINE__, dlerror());
        return;
    }
    dlclose(dlh);

}
