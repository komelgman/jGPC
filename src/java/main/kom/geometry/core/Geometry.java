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

/**
 * Contains data about on some common geometric object
 */
public class Geometry {

    /**
     * vertex data {x0, y0, x1, y1 ...}
     */
    double[] vertices = null;

    /**
     * Some specific data. For GPC algorithm it is hole flag in input polygons
     */
    int tag = 0;

    public Geometry() {
        super();
    }

    public Geometry(double[] vertices) {
        super();

        setVerticesData(vertices);
    }

    public Geometry(double[] vertices, int tag) {
        super();

        setVerticesData(vertices, tag);
    }

    public void setVerticesData(double[] vertices) {
        setVerticesData(vertices, 0);
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