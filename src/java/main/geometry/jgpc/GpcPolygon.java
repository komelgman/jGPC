package kom.geometry.jgpc;

import kom.geometry.core.Geometry;
import kom.geometry.core.GeometryState;
import kom.geometry.core.TransferableGeometry;

import java.util.ArrayList;
import java.util.Collection;

/**
 * Created with IntelliJ IDEA.
 * User: syungman
 * Date: 28.01.13
 * Time: 16:12
 *
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