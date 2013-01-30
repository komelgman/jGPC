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

package kom.geometry.jgpc;

import kom.geometry.core.GeometryTransfer;
import kom.geometry.core.GpcHelper;

public class Gpc {

    public static GeometryTransfer clip(GpcOperation operation, GeometryTransfer subject, GeometryTransfer clip) {
        return GpcHelper.polygonClip(operation.getValue(), subject, clip, false);
    }

    public static GeometryTransfer clip(GpcOperation operation, GeometryTransfer subject, GeometryTransfer clip,
            boolean returnAsTriStrips) {
        return GpcHelper.polygonClip(operation.getValue(), subject, clip, returnAsTriStrips);
    }

    public static GeometryTransfer clip(GpcOperation operation, GpcPolygon subject, GpcPolygon clip) {
        return GpcHelper.polygonClip(operation.getValue(), new GeometryTransfer(subject),
                new GeometryTransfer(clip), false);
    }

    public static GeometryTransfer clip(GpcOperation operation, GpcPolygon subject, GpcPolygon clip,
            boolean returnAsTriStrips) {
        return GpcHelper.polygonClip(operation.getValue(), new GeometryTransfer(subject),
                new GeometryTransfer(clip), returnAsTriStrips);
    }
}