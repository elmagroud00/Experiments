#include "TestRef.h"

static jclass myClass = 0;

JNIEXPORT jint JNICALL Java_TestRef_getMethod(JNIEnv* env, jclass clazz) {
        jfiedID fid;
        jint field;

        if(jclass == 0) {
            myClass = env->FindClass("Test");
        }

        fid = env->GetStaticFieldID(myClass, "m_num", "I");
        field = env->GetStaticIntField(myClass, fid);
        return field;
}
