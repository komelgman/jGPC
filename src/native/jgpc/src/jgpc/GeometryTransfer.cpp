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

#include <stdlib.h>
#include "GeometryTransfer.h"
#include "jni_tools.h"
#include "InitialData.h"
#include "GpcPolygon.h"
#include "GpcTriStrips.h"

/* global vars */
extern jclass class_Geometry;

/* private definitions */
GeometryTransfer* create_GeometryTransfer(JNIEnv *env, void* data, int state);
void* create_data(JNIEnv *env, int state, int chunksCount, int infoElementCount, jintArray chunksInfo, jobjectArray chunksVertices);
void* create_data(JNIEnv *env, int state);
void free_data(void *data, int state);

int get_chunksCount(JNIEnv *env, GeometryTransfer *transfer);

/*
 * GeometryTransfer
 */
GeometryTransfer* new_GeometryTransfer(JNIEnv *env, State state) {	
	void* data = create_data(env, state);
	if (env->ExceptionOccurred()) {
		return NULL;
	}

	return create_GeometryTransfer(env, data, state);
}

GeometryTransfer* new_GeometryTransfer(JNIEnv *env, int state, int chunksCount, int infoElementCount, jintArray chunksInfo, jobjectArray chunksVertices) {
	void* data = create_data(env, state, chunksCount, infoElementCount, chunksInfo, chunksVertices);
	if (env->ExceptionOccurred()) {
		return NULL;
	}

	return create_GeometryTransfer(env, data, state);
}

void free_GeometryTransfer(GeometryTransfer *transfer) {	
	if (transfer->state != STATE_EMPTY) {
		free_data(transfer->data, transfer->state);
		free(transfer);		
	}
}

jobjectArray GeometryTransfer_extract(JNIEnv *env, GeometryTransfer *transfer) {
	int chunksCount = get_chunksCount(env, transfer);
	if (env->ExceptionOccurred()) {
		return NULL;
	}

	jobjectArray result = env->NewObjectArray(chunksCount, class_Geometry, NULL);
	if (env->ExceptionOccurred()) {
		return NULL;
	}

	if (chunksCount == 0) {
		return result;
	}

	switch (transfer->state) {
		case STATE_GPC_POLY: 
			GpcPolygon_extractTo(env, (gpc_polygon*)transfer->data, result);
			break;

		case STATE_GPC_TRISTRIPS: 
			GpcTriStrips_extractTo(env, (gpc_tristrip*)transfer->data, result);
			break;

		case STATE_INITIAL: 
			InitialData_extractTo(env, (InitialData*)transfer->data, result);
			break;

	}

	return result;
}


/*
 * Private
 */

GeometryTransfer* create_GeometryTransfer(JNIEnv *env, void* data, int state) {
	if (state != STATE_EMPTY && !data) {
		JVM_throw_IllegalStateException(env, "Unknown error occured, data not initialized");
		return NULL;
	}

	GeometryTransfer *result = (GeometryTransfer*)malloc(sizeof(GeometryTransfer));
	if (!result) {
		free_data(data, state);

		JVM_throw_OutOfMemeory(env, "Can't allocate memory for GeometryTransfer");
		return NULL;
	}

	result->data = data;
	result->state = (State)state;	

	return result;
}

void* create_data(JNIEnv *env, int state, int chunksCount, int infoElementCount, jintArray chunksInfo, jobjectArray chunksVertices) {	
	switch (state) {
		case STATE_INITIAL:
			return new_InitialData(env, chunksCount, infoElementCount, chunksInfo, chunksVertices);
			break;

		case STATE_GPC_POLY:
			return new_GpcPolygon(env, chunksCount, infoElementCount, chunksInfo, chunksVertices);
			break;

		case STATE_EMPTY:
		case STATE_GPC_TRISTRIPS:
			JVM_throw_IllegalArgumentException(env, "Can't init data: Unsupported transfer state");
			break;
	}

	JVM_throw_IllegalArgumentException(env, "Can't init data: Unknown transfer state");
	return NULL;
}

void* create_data(JNIEnv *env, int state) {	
	switch (state) {
		case STATE_INITIAL:
			return new_InitialData(env);
			break;

		case STATE_GPC_POLY:
			return new_GpcPolygon(env);
			break;

		case STATE_GPC_TRISTRIPS:
			return new_GpcTriStrips(env);
			break;

		case STATE_EMPTY:
			return NULL;
			break;
	}

	JVM_throw_IllegalArgumentException(env, "Can't create data: Unknown transfer state");
	return NULL;
}

void free_data(void* data, int state) {
	switch (state) {
		case STATE_INITIAL:
			free_InitialData((InitialData*)data);
			break;
		case STATE_GPC_POLY:
			gpc_free_polygon((gpc_polygon*)data);
			break;
		case STATE_GPC_TRISTRIPS:
			gpc_free_tristrip((gpc_tristrip*)data);
			break;
	}
}

int get_chunksCount(JNIEnv *env, GeometryTransfer *transfer) {
	switch (transfer->state) {
		case STATE_INITIAL: return ((InitialData*)transfer->data)->chunksCount;
		case STATE_GPC_POLY: return ((gpc_polygon*)transfer->data)->num_contours;
		case STATE_GPC_TRISTRIPS: return ((gpc_tristrip*)transfer->data)->num_strips;
		case STATE_EMPTY: return 0;
	}

	JVM_throw_IllegalArgumentException(env, "Can't retrun chunks count: Unknown transfer state");
	return 0;
}