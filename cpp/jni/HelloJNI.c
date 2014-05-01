/* ************************************************************************
  > File Name: hellojni.c
  > Author: lnmcc
  > Mail: lnmcc@hotmail.com 
  > Blog: lnmcc.net 
  > Created Time: Mon Apr  7 13:35:31 2014
 *********************************************************************** */
#include <jni.h> 
#include <stdio.h>
#include <string.h>

void printHelloNative(JNIEnv* env, jobject obj);
void printStringNative(JNIEnv* env, jobject obj, jstring string);

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = NULL;
    JNINativeMethod nm[2];
    jclass cls;
    jint result = -1;

    if((*vm)->GetEnv(vm, (void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        printf("ERROR");
        return JNI_ERR;
    }

    cls = (*env)->FindClass(env, "HelloJNI");

    nm[0].name = "printHello";
    nm[0].signature = "()V";
    nm[0].fnPtr = (void*)printHelloNative;

    nm[1].name = "printString";
    nm[1].signature = "(Ljava/lang/String;)V";
    nm[1].fnPtr = (void*)printStringNative;

    result = (*env)->RegisterNatives(env, cls, nm, 2);
    return JNI_VERSION_1_6;
}

void printHelloNative(JNIEnv* env, jobject obj) {
    printf("HelloWorld\n");
    return;
}

void printStringNative(JNIEnv* env, jobject obg, jstring string) {
    const char* str = (*env)->GetStringUTFChars(env, string, 0);
    printf("%s\n", str);
    return;
}
