#ifndef __GpcPolygon_h
#define __GpcPolygon_h

#include "jni.h"
#include "gpc.h"

gpc_polygon* new_GpcPolygon(JNIEnv *env);
gpc_polygon* new_GpcPolygon(JNIEnv *env, int chunksCount, int infoElementCount, jintArray chunksInfo, jobjectArray chunksVertices);
void GpcPolygon_extractTo(JNIEnv *env, gpc_polygon *data, jobjectArray result);

#endif