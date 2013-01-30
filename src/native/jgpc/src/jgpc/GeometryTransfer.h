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