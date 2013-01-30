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
#include "jni_tools.h"
#include "InitialData.h"

/* global vars */ 
extern jclass class_Geometry;
extern jmethodID ctor_Geometry;

/* private */
double** convert_verticesData(JNIEnv *env, jobjectArray verticesData, int arrayLength, int *info);



/* public */
InitialData* new_InitialData(JNIEnv *env) {
	InitialData *result = (InitialData*)malloc(sizeof(InitialData));
	if (!result) {
		JVM_throw_OutOfMemeory(env, "Can't allocate memory for initialData");
		return NULL;
	}

	result->chunksCount = 0;
	result->chunksInfo = NULL;
	result->verticesData = NULL;
	result->infoElementCount = 0;

	return result;
}

InitialData* new_InitialData(JNIEnv * env, int chunksCount, int infoElementCount, jintArray chunksInfo, jobjectArray chunksVertices) {
	InitialData *result = new_InitialData(env);
	if (!result) {
		return NULL;
	}

	// copy chunks info
	result->chunksInfo = copy_jIntArray_To_IntArray(env, chunksInfo, chunksCount * infoElementCount);
	if (!result->chunksInfo) {
		free_InitialData(result);
		return NULL;
	}

	// copy vertices data
	result->verticesData = convert_verticesData(env, chunksVertices, chunksCount, result->chunksInfo);
	if (!result->verticesData) {
		free_InitialData(result);
		return NULL;
	}

	result->chunksCount = chunksCount;
	result->infoElementCount = infoElementCount;

	return result;
}

double** convert_verticesData(JNIEnv *env, jobjectArray verticesData, int arrayLength, int *info) {
	double **result = (double**)malloc(arrayLength * sizeof(double*));
	if (!result) {
		JVM_throw_OutOfMemeory(env, "Can't allocate memory for vertices data");
		return NULL;
	}
	
	// copy vertices data 
	// !!! allocated memory is not cleared if error occurred
	for (int i = 0, j = 0; i < arrayLength; ++i, j = i * 2) {		
		const jdoubleArray chunkVerticesData = (jdoubleArray)env->GetObjectArrayElement(verticesData, i);
		if (env->ExceptionOccurred()) {
			return NULL;
		}

		result[i] = copy_jDoubleArray_To_DoubleArray(env, chunkVerticesData, info[j]);
		if (!result[i]) {
			return NULL;
		}
	}

	return result;
}

void free_InitialData(InitialData *initialData) {
	if (initialData) {
		free(initialData->chunksInfo);
		free(initialData->verticesData);
		free(initialData);
	}
}

void InitialData_extractTo(JNIEnv *env, InitialData *data, jobjectArray result) {
	if (!class_Geometry || !ctor_Geometry) {
		JVM_throw_IllegalStateException(env, "Geometry class or default ctor not initialized");
		return;
	}

	for (int i = 0, j = 0; i < data->chunksCount; ++i, j = i * 2) {
		jdoubleArray tmpVertices = env->NewDoubleArray(data->chunksInfo[j]);
		if (env->ExceptionOccurred()) {
			return;
		}

		env->SetDoubleArrayRegion(tmpVertices, 0, data->chunksInfo[j], data->verticesData[i]);

		jobject geometry = env->NewObject(class_Geometry, ctor_Geometry, tmpVertices, data->chunksInfo[j + 1]);
		if (env->ExceptionOccurred()) {
			return;
		}
		
		env->SetObjectArrayElement(result, i, geometry);

		env->DeleteLocalRef(geometry);
		env->DeleteLocalRef(tmpVertices);
	}
}
