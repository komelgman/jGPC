package kom.geometry.core;

/**
 * Created with IntelliJ IDEA.
 * User: syungman
 * Date: 25.01.13
 * Time: 18:51
 */
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
