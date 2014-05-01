LOCAL_PATH:=$(call my-dir)  
 
include $(CLEAR_VARS)

LOCAL_MODULE:=useJNI
LOCAL_SRC_FILES:=useJNI.c

include $(BUILD_SHARED_LIBRARY)
