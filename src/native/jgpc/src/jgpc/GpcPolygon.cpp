#include <stdlib.h>
#include "jni_tools.h"
#include "GpcPolygon.h"

/* global vars */ 
extern jclass class_Geometry;
extern jmethodID ctor_Geometry;


/* public */
gpc_polygon* new_GpcPolygon(JNIEnv *env) {
	gpc_polygon *result = (gpc_polygon*)malloc(sizeof(gpc_polygon));
	if (!result) {
		JVM_throw_OutOfMemeory(env, "Can't allocate memory for gpc_polygon");
		return NULL;
	}

	result->num_contours = 0;
	result->contour = NULL;
	result->hole = NULL;

	return result;
}

gpc_polygon* new_GpcPolygon(JNIEnv * env, int chunksCount, int infoElementCount, jintArray chunksInfo, jobjectArray chunksVertices) {
	gpc_polygon *result = new_GpcPolygon(env);
	if (!result) {
		return NULL;
	}

	result->hole = (int*)malloc(chunksCount * sizeof(int));
	result->contour = (gpc_vertex_list*)malloc(chunksCount * sizeof(gpc_vertex_list));
	if (!result->hole || !result->contour) {
		gpc_free_polygon(result);
		JVM_throw_OutOfMemeory(env, "Can't allocate memory for gpc_polygon");
		return NULL;
	}
	

	const int *c_chunksInfo = (int*)env->GetIntArrayElements(chunksInfo, 0);
	if (env->ExceptionOccurred()) {
		gpc_free_polygon(result);
		return NULL;
	}
	
	for (int i = 0, j = 0; i < chunksCount; ++i, j = i * 2) {
		const jdoubleArray chunkVerticesData = (jdoubleArray)env->GetObjectArrayElement(chunksVertices, i);
		const double *c_chunkVerticesData = (double*)env->GetPrimitiveArrayCritical(chunkVerticesData, 0);
		if (env->ExceptionOccurred()) {
			gpc_free_polygon(result);
			return NULL;
		}

		result->hole[i] = c_chunksInfo[j + 1];
		result->contour[i].num_vertices = c_chunksInfo[j + 0] >> 1;
		result->contour[i].vertex = (gpc_vertex*)malloc(result->contour[i].num_vertices * sizeof(gpc_vertex));

		if (!result->contour[i].vertex) {
			gpc_free_polygon(result);
			JVM_throw_OutOfMemeory(env, "Can't allocate memory for gpc_polygon");
			return NULL;
		}

		for (int v = 0, k = 0; v < result->contour[i].num_vertices; ++v, k = v * 2) {
			result->contour[i].vertex[v].x = c_chunkVerticesData[k];
			result->contour[i].vertex[v].y = c_chunkVerticesData[k + 1];
		}

		env->ReleasePrimitiveArrayCritical(chunkVerticesData, (void*)c_chunkVerticesData, JNI_ABORT);
		env->DeleteLocalRef(chunkVerticesData);
	}

	env->ReleaseIntArrayElements(chunksInfo, (jint*)c_chunksInfo, JNI_ABORT);

	result->num_contours = chunksCount;

	return result;
}

void GpcPolygon_extractTo(JNIEnv *env, gpc_polygon *data, jobjectArray result) {
	if (!class_Geometry || !ctor_Geometry) {
		JVM_throw_IllegalStateException(env, "Geometry class or default ctor not initialized");
		return;
	}

	for (int i = 0; i < data->num_contours; ++i) {
		jdoubleArray tmpVertices = env->NewDoubleArray(data->contour[i].num_vertices << 1);
		if (env->ExceptionOccurred()) {
			return;
		}

		double *c_tmpVertices = (double*)env->GetPrimitiveArrayCritical(tmpVertices, 0);
		for (int v = 0, k = 0; v < data->contour[i].num_vertices; ++v) {
			c_tmpVertices[k++] = data->contour[i].vertex[v].x;
			c_tmpVertices[k++] = data->contour[i].vertex[v].y;
		}
		env->ReleasePrimitiveArrayCritical(tmpVertices, (void*)c_tmpVertices, 0);

		jobject geometry = env->NewObject(class_Geometry, ctor_Geometry, tmpVertices, data->hole[i]);
		if (env->ExceptionOccurred()) {
			return;
		}
		
		env->SetObjectArrayElement(result, i, geometry);

		env->DeleteLocalRef(geometry);
		env->DeleteLocalRef(tmpVertices);
	}
}