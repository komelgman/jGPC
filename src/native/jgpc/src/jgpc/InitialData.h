/*******************************************************************************
 * Copyright 2013 Sergey Yungman
 *
 * Licensed under the LGPL Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.gnu.org/copyleft/lesser.html
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

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