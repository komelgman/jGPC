#ifndef __InitialData_h
#define __InitialData_h

#include "jni.h"
#include "gpc.h"

/* Initialdata struct - represent experimetal algorithm independent format */
typedef struct {
	int chunksCount;
	int infoElementCount;
	int *chunksInfo;			/* It is array of int with length = chunksCount * infoElementCount. 
								 * chunkInfo_tag0 = chunksInfo[index + 0];
								 * chunkInfo_tag1 = chunksInfo[index + 1];
								 * etc.
								 */
	double **verticesData;		/* It is 2 dim array of double with following structure: [chuksCount][chunkInfo_tag0]
								 * chunkVertices = verticesdata[chunkIndex] { x0, y0, x1, y1 ... }
								 */
} InitialData;


InitialData* new_InitialData(JNIEnv *env);
InitialData* new_InitialData(JNIEnv *env, int chunksCount, int infoElementCount, jintArray chunksInfo, jobjectArray chunksVertices);
void free_InitialData(InitialData *pointer);

void InitialData_extractTo(JNIEnv *env, InitialData *data, jobjectArray result);

#endif