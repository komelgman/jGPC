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

#ifndef __GpcPolygon_h
#define __GpcPolygon_h

#include "jni.h"
#include "gpc.h"

gpc_polygon* new_GpcPolygon(JNIEnv *env);
gpc_polygon* new_GpcPolygon(JNIEnv *env, int chunksCount, int infoElementCount, jintArray chunksInfo, jobjectArray chunksVertices);
void GpcPolygon_extractTo(JNIEnv *env, gpc_polygon *data, jobjectArray result);

#endif