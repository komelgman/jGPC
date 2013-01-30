package kom.geometry.core;

/**
 * Created with IntelliJ IDEA.
 * User: syungman
 * Date: 24.01.13
 * Time: 12:15
 */
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