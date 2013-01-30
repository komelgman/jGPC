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

#ifndef __jvm_h
#define __jvm_h

#ifdef __cplusplus
extern "C" {
#endif

// --------------------------------------------------------------------------------------------------------------
	#include "jni.h"

	void JVM_throw_OutOfMemeory(JNIEnv *env, const char* message);
	void JVM_throw_IllegalArgumentException(JNIEnv *env, const char* message);
	void JVM_throw_IllegalStateException(JNIEnv *env, const char* message);	

	int* copy_jIntArray_To_IntArray(JNIEnv *env, jintArray jintArray, int arrayLength);
	double* copy_jDoubleArray_To_DoubleArray(JNIEnv *env, jdoubleArray jdoubleArray, int arrayLength);

// --------------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif