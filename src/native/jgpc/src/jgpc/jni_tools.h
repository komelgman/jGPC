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