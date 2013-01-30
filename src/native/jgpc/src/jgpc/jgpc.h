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

/* Header for class kom_geometry_core_jni */

#ifndef _Included_kom_geometry_core_jni
#define _Included_kom_geometry_core_jni
#ifdef __cplusplus
extern "C" {
#endif

#include "jni.h"
#include "gpc.h"

/*
 * Class:     kom_geometry_core_jni
 * Method:    GeometryTransfer_create
 * Signature: (III[I[[D)J
 */
JNIEXPORT jlong JNICALL Java_kom_geometry_core_jni_GeometryTransfer_1create
  (JNIEnv *, jclass, jint, jint, jint, jintArray, jobjectArray);

/*
 * Class:     kom_geometry_core_jni
 * Method:    GeometryTransfer_free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_kom_geometry_core_jni_GeometryTransfer_1free
  (JNIEnv *, jclass, jlong);

/*
 * Class:     kom_geometry_core_jni
 * Method:    GeometryTransfer_extract
 * Signature: (J)[Lcom/komelgman/geometry/Geometry;
 */
JNIEXPORT jobjectArray JNICALL Java_kom_geometry_core_jni_GeometryTransfer_1extract
  (JNIEnv *, jclass, jlong);

/*
 * Class:     kom_geometry_core_jni
 * Method:    Gpc_polygonClip
 * Signature: (IJJZ)J
 */
JNIEXPORT jlong JNICALL Java_kom_geometry_core_jni_Gpc_1polygonClip
  (JNIEnv *, jclass, jint, jlong, jlong, jboolean);

/*
 * Class:     kom_geometry_core_jni
 * Method:    Gpc_triangulate
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_kom_geometry_core_jni_Gpc_1triangulate
  (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif
