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

public class GpcHelper {
    public static GeometryTransfer triangulate(GeometryTransfer subject) {
        validGpcPoly(subject);

        long pointer = jni.Gpc_triangulate(subject.objCPtr);
        GeometryState state = GeometryState.GpcTriStrips;

        return new GeometryTransfer(pointer, state);
    }


    public static GeometryTransfer polygonClip(int operation, GeometryTransfer subject,
            GeometryTransfer clip, boolean returnAsTriStrips) {
        validGpcPoly(subject);
        validGpcPoly(clip);

        long pointer = jni.Gpc_polygonClip(operation, subject.objCPtr, clip.objCPtr, returnAsTriStrips);
        GeometryState state = (returnAsTriStrips)
                ? GeometryState.GpcTriStrips
                : GeometryState.GpcPoly;

        return new GeometryTransfer(pointer, state);
    }

    private static void validGpcPoly(GeometryTransfer transfer) {
        if (transfer.state != GeometryState.GpcPoly) {
            throw new IllegalStateException("GeometryTransfer must be in GpcPoly state");
        }
    }
}
