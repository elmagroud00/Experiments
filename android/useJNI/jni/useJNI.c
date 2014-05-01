#include "net_lnmcc_usejni_MainActivity.h"

JNIEXPORT jstring JNICALL Java_net_lnmcc_usejni_MainActivity_getStringFromNative
  (JNIEnv *env, jobject obj) {

	return (*env)->NewStringUTF(env, (char*)"hello, String from JNI");
}
