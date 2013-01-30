package kom.geometry.jgpc;

import kom.geometry.core.GeometryTransfer;
import kom.geometry.core.GpcHelper;

/**
 * Created with IntelliJ IDEA.
 * User: syungman
 * Date: 24.01.13
 * Time: 13:18
 */
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