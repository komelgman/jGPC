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

package kom.geometry.core;

final class jni {
    static native long GeometryTransfer_create(int targetState, int chunksCount, int infoElementsCount, int[] chunksInfo, double[][] chunksVertices);
    static native void GeometryTransfer_free(long objCPtr);
    static native Geometry[] GeometryTransfer_extract(long objCPtr);

    static native long Gpc_polygonClip(int gpcOp, long subjectCPtr, long clipCPtr, boolean returnAsTriStrips);
    static native long Gpc_triangulate(long objCPtr);

    static {
        System.loadLibrary("jgpc");
    }
}