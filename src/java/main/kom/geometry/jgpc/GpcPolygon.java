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

import kom.geometry.core.Geometry;
import kom.geometry.core.GeometryState;
import kom.geometry.core.TransferableGeometry;

import java.util.ArrayList;
import java.util.Collection;

/**
 * Simple wrapper for building gpc polygon structure
 */
public class GpcPolygon extends ArrayList<Geometry> implements TransferableGeometry {

    public GpcPolygon addContour(double[] vertices) {
        add(createContour(vertices));

        return this;
    }

    public GpcPolygon addHole(double[] vertices) {
        add(createHole(vertices));

        return this;
    }

    public static Geometry createContour(double[] vertices) {
        return new Geometry(vertices, 0);
    }

    public static Geometry createHole(double[] vertices) {
        return new Geometry(vertices, 1);
    }

    @Override
    public Collection<Geometry> getGeometries() {
        return this;
    }

    @Override
    public GeometryState getState() {
        return this.size() == 0
                ? GeometryState.Empty
                : GeometryState.GpcPoly;
    }
}