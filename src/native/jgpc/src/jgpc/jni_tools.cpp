﻿#include <stdlib.h>
#include <memory.h>
#include "jni_tools.h"


void JVM_throwByName(JNIEnv *env, const char *name, const char *message) {
	jclass cls;

	if (!env) {
		printf("IllegalStateException: Current JNI Enviroment not initialized\n");
		return;
	}

	cls = env->FindClass(name);

	if (cls != NULL) {
		env->ThrowNew(cls, message);
	}

	env->DeleteLocalRef(cls);
}

void JVM_throw_OutOfMemeory(JNIEnv *env, const char* message) {
	JVM_throwByName(env, "java/lang/OutOfMemoryError", message);
}

void JVM_throw_IllegalStateException(JNIEnv *env, const char* message) {
	JVM_throwByName(env, "java/lang/IllegalStateException", message);
}

void JVM_throw_IllegalArgumentException(JNIEnv *env, const char* message) {
	JVM_throwByName(env, "java/lang/IllegalArgumentException", message);
}

int* copy_jIntArray_To_IntArray(JNIEnv *env, jintArray jintArray, int arrayLength) {
	int size = arrayLength * sizeof(int);
	int* memory = (int*)malloc(size);
	if (!memory) {
		JVM_throw_OutOfMemeory(env, "Can't allocate memory for new int array");
		return NULL;
	}

	void *src = env->GetPrimitiveArrayCritical(jintArray, 0);
	memcpy(memory, src, size);	
	env->ReleasePrimitiveArrayCritical(jintArray, src, 0);

	if (env->ExceptionOccurred()) {
		free(memory);
		return NULL;
	}

	return memory;
}

double* copy_jDoubleArray_To_DoubleArray(JNIEnv *env, jdoubleArray jdoubleArray, int arrayLength) {
	int size = arrayLength * sizeof(double);
	double* memory = (double*)malloc(size);
	if (!memory) {
		JVM_throw_OutOfMemeory(env, "Can't allocate memory for new double array");
		return NULL;
	}

	void *src = env->GetPrimitiveArrayCritical(jdoubleArray, 0);
	memcpy(memory, src, size);	
	env->ReleasePrimitiveArrayCritical(jdoubleArray, src, 0);

	if (env->ExceptionOccurred()) {
		free(memory);
		return NULL;
	}

	return memory;
}