#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include "VdpauContext.h"

using namespace mx;

VdpauContext::VdpauContext() {
	//fprintf(stderr, "VdpauContext\n");
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
   // init();
}

VdpauContext::~VdpauContext() {
	VdpStatus vdp_st;
	if(vdpDevice != VDP_INVALID_HANDLE) {
		vdp_st = vdp_device_destroy(vdpDevice);
		if(vdp_st != VDP_STATUS_OK)
			fprintf(stderr, "vdp_device_destroy failed\n");
		ptrglVDPAUFiniNV();
	}
}

bool VdpauContext::getFunc(int func, void **p) {
	VdpStatus vdp_st = vdp_get_proc_address(vdpDevice, func, p);
	if(vdp_st != VDP_STATUS_OK)
		return false;
	return true;
}

void VdpauContext::initVdpauInterop() {
	if(ptrglVDPAUInitNV == NULL)
		init_vdpau_interop();
	ptrglVDPAUInitNV((const GLvoid*)vdpDevice, (const GLvoid*)vdp_get_proc_address);
}
int VdpauContext::init() {
	if (vdpDevice != VDP_INVALID_HANDLE)
		return 2;
	vdp_get_proc_address = NULL;
	VdpStatus vdp_st;
/*	if(vdpDevice != VDP_INVALID_HANDLE) {
		vdp_st = vdp_device_destroy(vdpDevice);
		if(vdp_st != VDP_STATUS_OK)
			fprintf(stderr, "%d destroy device vdpau failed: vdp_st = %d\n", __LINE__, vdp_st);
	}*/
    Display *dpy = XOpenDisplay(NULL);
    if(dpy == NULL) {
        fprintf(stderr, "vdp_device_create_x11 open display error\n");
        return -1;
    }
	vdp_st = vdp_device_create_x11(dpy, DefaultScreen(dpy), &vdpDevice, &vdp_get_proc_address);
	if(vdp_st != VDP_STATUS_OK) {
		fprintf(stderr, "%d create device vdpau failed: vdp_st = %d\n", __LINE__, vdp_st);
		return -1;
	}
	if (!getFunc( VDP_FUNC_ID_GET_ERROR_STRING , (void**)&vdp_get_error_string))
        printf("Can't get VDP_FUNC_ID_GET_ERROR_STRING address !!");

    if (!getFunc( VDP_FUNC_ID_GET_INFORMATION_STRING , (void**)&vdp_get_information_string))
        printf("Can't get VDP_FUNC_ID_GET_INFORMATION_STRING address !!");

    if (!getFunc( VDP_FUNC_ID_DEVICE_DESTROY , (void**)&vdp_device_destroy))
        printf("Can't get VDP_FUNC_ID_DEVICE_DESTROY address !!");

    if (!getFunc( VDP_FUNC_ID_GENERATE_CSC_MATRIX , (void**)&vdp_generate_csc_matrix))
        printf("Can't get VDP_FUNC_ID_GENERATE_CSC_MATRIX address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_SURFACE_CREATE , (void**)&vdp_video_surface_create))
        printf("Can't get VDP_FUNC_ID_VIDEO_SURFACE_CREATE address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_SURFACE_DESTROY , (void**)&vdp_video_surface_destroy))
        printf("Can't get VDP_FUNC_ID_VIDEO_SURFACE_DESTROY address !!");

    if (!getFunc( VDP_FUNC_ID_OUTPUT_SURFACE_CREATE , (void**)&vdp_output_surface_create))
        printf("Can't get VDP_FUNC_ID_OUTPUT_SURFACE_CREATE address !!");

    if (!getFunc( VDP_FUNC_ID_OUTPUT_SURFACE_DESTROY , (void**)&vdp_output_surface_destroy))
        printf("Can't get VDP_FUNC_ID_OUTPUT_SURFACE_DESTROY address !!");

    if (!getFunc( VDP_FUNC_ID_BITMAP_SURFACE_CREATE , (void**)&vdp_bitmap_surface_create))
        printf("Can't get VDP_FUNC_ID_BITMAP_SURFACE_CREATE address !!");

    if (!getFunc( VDP_FUNC_ID_BITMAP_SURFACE_DESTROY , (void**)&vdp_bitmap_surface_destroy))
        printf("Can't get VDP_FUNC_ID_BITMAP_SURFACE_DESTROY address !!");

    if (!getFunc( VDP_FUNC_ID_DECODER_CREATE , (void**)&vdp_decoder_create))
        printf("Can't get VDP_FUNC_ID_DECODER_CREATE address !!");

    if (!getFunc( VDP_FUNC_ID_DECODER_DESTROY , (void**)&vdp_decoder_destroy))
        printf("Can't get VDP_FUNC_ID_DECODER_DESTROY address !!");

    if (!getFunc( VDP_FUNC_ID_DECODER_RENDER , (void**)&vdp_decoder_render))
        printf("Can't get VDP_FUNC_ID_DECODER_RENDER address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_CREATE , (void**)&vdp_video_mixer_create))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_CREATE address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_SET_FEATURE_ENABLES , (void**)&vdp_video_mixer_set_feature_enables))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_SET_FEATURE_ENABLES address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_SET_ATTRIBUTE_VALUES , (void**)&vdp_video_mixer_set_attribute_values))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_SET_ATTRIBUTE_VALUES address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_DESTROY , (void**)&vdp_video_mixer_destroy))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_DESTROY address !!");

    if (!getFunc( VDP_FUNC_ID_VIDEO_MIXER_RENDER , (void**)&vdp_video_mixer_render))
        printf("Can't get VDP_FUNC_ID_VIDEO_MIXER_RENDER address !!");

    if (!getFunc( VDP_FUNC_ID_PREEMPTION_CALLBACK_REGISTER , (void**)&vdp_preemption_callback_register))
        printf("Can't get VDP_FUNC_ID_PREEMPTION_CALLBACK_REGISTER address !!");

	init_vdpau_interop();
	ptrglVDPAUInitNV((const GLvoid*)vdpDevice, (const GLvoid*)vdp_get_proc_address);
	return 0;
}

void VdpauContext::init_vdpau_interop() {
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
