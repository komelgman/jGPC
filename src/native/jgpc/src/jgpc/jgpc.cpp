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

#include "jgpc.h"
#include "jni_tools.h"
#include "GeometryTransfer.h"

/* cached global value */
jclass class_Geometry = NULL;
jmethodID ctor_Geometry = NULL;


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *pvt) {	
	JNIEnv *env;     
    jint envRes = vm->GetEnv((void**)&env, JNI_VERSION_1_2);
	if (envRes != JNI_OK) {
		return 0;
	}

	class_Geometry = env->FindClass(CLASS_GEOMETRY);
	if (env->ExceptionOccurred()) {
		return NULL;
	}

	ctor_Geometry = env->GetMethodID(class_Geometry, "<init>", "([DI)V");
	if (env->ExceptionOccurred()) {
		return NULL;
	}

	if (!class_Geometry || !ctor_Geometry) {
		JVM_throw_IllegalStateException(env, "Geometry class or ([DI)V ctor not found");
		return NULL;
	}

	return JNI_VERSION_1_2;
}

/*
 * Class:     kom_geometry_core_jni
 * Method:    GeometryTransfer_create
 * Signature: (III[I[[D)J
 */
JNIEXPORT jlong JNICALL Java_kom_geometry_core_jni_GeometryTransfer_1create
		(JNIEnv * env, jclass clazz, jint state, jint chunksCount, jint infoElementCount, jintArray chunksInfo, jobjectArray chunksVertices) {
	
	return (jlong)new_GeometryTransfer(env, state, chunksCount, infoElementCount, chunksInfo, chunksVertices);
}

/*
 * Class:     kom_geometry_core_jni
 * Method:    GeometryTransfer_free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_kom_geometry_core_jni_GeometryTransfer_1free
		(JNIEnv *env, jclass clazz, jlong pointer) {

	free_GeometryTransfer((GeometryTransfer*)pointer);
}

/*
 * Class:     kom_geometry_core_jni
 * Method:    GeometryTransfer_extract
 * Signature: (J)[Lcom/komelgman/geometry/Geometry;
 */
JNIEXPORT jobjectArray JNICALL Java_kom_geometry_core_jni_GeometryTransfer_1extract
		(JNIEnv *env, jclass clazz, jlong pointer) {

	return GeometryTransfer_extract(env, (GeometryTransfer*)pointer);
}

/*
 * Class:     kom_geometry_core_jni
 * Method:    Gpc_polygonClip
 * Signature: (IJJZ)J
 */
JNIEXPORT jlong JNICALL Java_kom_geometry_core_jni_Gpc_1polygonClip
		(JNIEnv *env, jclass clazz, jint op, jlong subjectPointer, 
		jlong clipPointer, jboolean returnAsTriStrips) {

	GeometryTransfer *subjectTransfer = (GeometryTransfer*)subjectPointer;
	GeometryTransfer *clipTransfer = (GeometryTransfer*)clipPointer;

	if (subjectTransfer->state != STATE_GPC_POLY || clipTransfer->state != STATE_GPC_POLY) {
		JVM_throw_IllegalArgumentException(env, "Can't clip: Subject and Clip must be GpcPolygon");
		return NULL;
	}

	GeometryTransfer *result = new_GeometryTransfer(env, (JNI_TRUE == returnAsTriStrips) ? STATE_GPC_TRISTRIPS  : STATE_GPC_POLY);
	if (!result) {
		return NULL;
	}

	if (JNI_TRUE == returnAsTriStrips) {
		gpc_tristrip_clip((gpc_op)op, (gpc_polygon*)subjectTransfer->data, (gpc_polygon*)clipTransfer->data, (gpc_tristrip*)result->data);
	} else {
		gpc_polygon_clip((gpc_op)op, (gpc_polygon*)subjectTransfer->data, (gpc_polygon*)clipTransfer->data, (gpc_polygon*)result->data);
	}

	return (jlong)result;
}

/*
 * Class:     kom_geometry_core_jni
 * Method:    Gpc_triangulate
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_kom_geometry_core_jni_Gpc_1triangulate
		(JNIEnv *env, jclass clazz, jlong pointer) {

	GeometryTransfer *transfer = (GeometryTransfer*)pointer;

	if (transfer->state != STATE_GPC_POLY) {
		JVM_throw_IllegalArgumentException(env, "Can't triangulate: Subject must be GpcPolygon");
		return NULL;
	}

	GeometryTransfer *result = new_GeometryTransfer(env, STATE_GPC_TRISTRIPS);
	if (!result) {
		return NULL;
	}

	gpc_polygon_to_tristrip((gpc_polygon*)transfer->data, (gpc_tristrip*)result->data);

	return (jlong)result;
}