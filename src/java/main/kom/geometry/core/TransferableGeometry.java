package kom.geometry.core;

import java.util.Collection;

/**
 * Created with IntelliJ IDEA.
 * User: syungman
 * Date: 28.01.13
 * Time: 16:45
 */
public interface TransferableGeometry {
    public Collection<Geometry> getGeometries();
    public GeometryState getState();
}
