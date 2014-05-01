/* ************************************************************************
  > File Name: invocationApi.c
  > Author: lnmcc
  > Mail: lnmcc@hotmail.com 
  > Blog: lnmcc.net 
  > Created Time: Thu Apr  3 23:48:07 2014
 *********************************************************************** */
#include <jni.h>
#include <string.h>
#include <stdlib.h>

int main() {
    JNIEnv* env;
    JavaVM* vm;
    JavaVMInitArgs vm_args;
    JavaVMOption options[1];
    jint res;
    jclass cls;
    jmethodID mid;
    jstring jstr;
    jclass stringClass;
    jobjectArray args;

    //1.生成Java虚拟机选项
    options[0].optionString = "-Djava.class.path=.";
    memset(&vm_args, 0x0, sizeof(JavaVMInitArgs));
    vm_args.version = JNI_VERSION_1_6;
    vm_args.options = options;
    vm_args.nOptions = 1;
    vm_args.ignoreUnrecognized = JNI_TRUE;

    //2.生成Java虚拟机
    res = JNI_CreateJavaVM(&vm, (void**)&env, &vm_args);

    //3.查找并加载类
    cls = (*env)->FindClass(env, "invocationApiTest");

    //4.获取mian()方法的ID
    mid = (*env)->GetStaticMethodID(env, cls, "main", "([Ljava/lang/String;)V");
    if(!mid) {
        fprintf(stderr, "Cannot find method: main\n");
        exit(1);
    }

    //5.生成字符串对象,用作main()方法的参数
    jstr = (*env)->NewStringUTF(env, "Hello Invocation API");
    stringClass = (*env)->FindClass(env, "java/lang/String");
    args = (*env)->NewObjectArray(env, 1, stringClass, jstr);

    //6.调用main()方法的
    (*env)->CallStaticVoidMethod(env, cls, mid, args);

    //7.销毁Java虚拟机
    (*vm)->DestroyJavaVM(vm);

    return 0;
}
