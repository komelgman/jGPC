#ifndef __GpcTriStrips_h
#define __GpcTriStrips_h

#include "jni.h"
#include "gpc.h"

gpc_tristrip* new_GpcTriStrips(JNIEnv *env);
void GpcTriStrips_extractTo(JNIEnv *env, gpc_tristrip *data, jobjectArray result);

#endif