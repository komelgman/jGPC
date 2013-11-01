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

import java.util.Arrays;

public class Geometry {

    public static int TAG_CONTOUR = 0;
    public static int TAG_HOLE = 1;

    /**
     * vertex data {x0, y0, x1, y1 ...}
     */
    double[] vertices = null;

    /**
     * Some specific data.
     * For GPC algorithm it is hole flag in input polygons
     */
    int tag = TAG_CONTOUR;

    public Geometry() {
        // jni
    }

    public Geometry(double[] vertices, int tag) {
        setVerticesData(vertices, tag);
    }

    public static Geometry createContour(double ... vertices) {
        return new Geometry(vertices, TAG_CONTOUR);
    }

    public static Geometry createHole(double ... vertices) {
        return new Geometry(vertices, TAG_HOLE);
    }

    public void setVerticesData(double[] vertices, int tag) {
        this.vertices = vertices;
        this.tag = tag;

        validate();
    }

    public double[] getVertices() {
        return vertices;
    }

    public long getTag() {
        return tag;
    }

    public void validate() {
        if (vertices == null) {
            return;
        }

        final int ARITY = 2;
        if (vertices.length % ARITY != 0) {
            throw new IllegalStateException("Vertices length must be equal N * Arity size, where N is vertex count");
        }
    }
}