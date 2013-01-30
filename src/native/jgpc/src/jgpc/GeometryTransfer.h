#ifndef __GeometryTransfer_h
#define __GeometryTransfer_h

#include "jni.h"
#include "gpc.h"

#define CLASS_GEOMETRY "kom/geometry/core/Geometry"

typedef enum {
	STATE_EMPTY,				/* Empty transfer */
	STATE_INITIAL,				/* Experimental: contains link to InitialData struct - this is algorithm independent format */
	STATE_GPC_POLY,				/* Transfer conatins link to gpc_polygon struct (gpc library format)*/
	STATE_GPC_TRISTRIPS			/* transfer contains link to gpc_tristrip struct (gpc library format)*/
} State;

/* GeometryTransfer - gateway from java to native code for geometry data */
typedef struct {
	State state;				/* Current state */
	void* data;					/* Link to state reprentation */
} GeometryTransfer;



/*
 * GeometryTransfer methods
 */
GeometryTransfer* new_GeometryTransfer(JNIEnv *env, int state, int chunksCount, int infoElementCount, jintArray chunksInfo, jobjectArray chunksVertices);
GeometryTransfer* new_GeometryTransfer(JNIEnv *env, State state);
void free_GeometryTransfer(GeometryTransfer *pointer);

jobjectArray GeometryTransfer_extract(JNIEnv *env, GeometryTransfer *transfer);


#endif