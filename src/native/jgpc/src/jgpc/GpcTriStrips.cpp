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
#include "GpcTriStrips.h"

/* global vars */ 
extern jclass class_Geometry;
extern jmethodID ctor_Geometry;


/* public */
gpc_tristrip* new_GpcTriStrips(JNIEnv *env) {
	gpc_tristrip *result = (gpc_tristrip*)malloc(sizeof(gpc_tristrip));
	if (!result) {
		JVM_throw_OutOfMemeory(env, "Can't allocate memory for gpc_polygon");
		return NULL;
	}

	result->num_strips = 0;
	result->strip = NULL;
}

void GpcTriStrips_extractTo(JNIEnv *env, gpc_tristrip *data, jobjectArray result) {
	if (!class_Geometry || !ctor_Geometry) {
		JVM_throw_IllegalStateException(env, "Geometry class or default ctor not initialized");
		return;
	}

	for (int i = 0; i < data->num_strips; ++i) {
		jdoubleArray tmpVertices = env->NewDoubleArray(data->strip[i].num_vertices << 1);
		if (env->ExceptionOccurred()) {
			return;
		}

		double *c_tmpVertices = (double*)env->GetPrimitiveArrayCritical(tmpVertices, 0);
		for (int v = 0, k = 0; v < data->strip[i].num_vertices; ++v) {
			c_tmpVertices[k++] = data->strip[i].vertex[v].x;
			c_tmpVertices[k++] = data->strip[i].vertex[v].y;
		}
		env->ReleasePrimitiveArrayCritical(tmpVertices, (void*)c_tmpVertices, 0);

		jobject geometry = env->NewObject(class_Geometry, ctor_Geometry, tmpVertices, 0 /*fictive tag*/);
		if (env->ExceptionOccurred()) {
			return;
		}
		
		env->SetObjectArrayElement(result, i, geometry);

		env->DeleteLocalRef(geometry);
		env->DeleteLocalRef(tmpVertices);
	}
}