package kom.geometry.core;

import java.util.Arrays;
import java.util.Collection;

/**
 * Created with IntelliJ IDEA.
 * User: syungman
 * Date: 23.01.13
 * Time: 16:09
 */
public final class GeometryTransfer {

    long objCPtr = 0;
    GeometryState state = GeometryState.Empty;

    public GeometryTransfer() {
    }

    public GeometryTransfer(TransferableGeometry geometry) {
        set(geometry);
    }

    GeometryTransfer(long objCPtr, GeometryState state) {
        this.objCPtr = objCPtr;
        this.state = state;
    }

    public void set(Geometry geometry, GeometryState state) {
        set(new Geometry[]{ geometry }, state);
    }

    public void set(Geometry[] geometries, GeometryState state) {
        setAs(Arrays.asList(geometries), state);
    }

    public synchronized void setAs(Collection<Geometry> geometries, GeometryState state) {
        if (objCPtr != 0) {
            free();
        }

        if (geometries == null || geometries.isEmpty()) {
            return;
        }

        final int chunksCount = geometries.size();
        final double[][] chunksVertices = new double[chunksCount][];
        final int infoElementsCount = 2;
        final int[] chunksInfo = new int[infoElementsCount * chunksCount];

        int i = 0;
        for (final Geometry geometry : geometries) {
            final double[] vertices = geometry.vertices;
            final int ix2 = infoElementsCount * i;

            chunksVertices[i] = vertices;
            chunksInfo[ix2] = vertices.length;
            chunksInfo[ix2 + 1] = geometry.tag;

            i++;
        }

        objCPtr = jni.GeometryTransfer_create(state.value, chunksCount, infoElementsCount, chunksInfo, chunksVertices);
        this.state = state;
    }

    public void set(TransferableGeometry data) {
        setAs(data.getGeometries(), data.getState());
    }

    public Geometry[] get() {
        if (objCPtr == 0) {
            return new Geometry[]{};
        }

        return jni.GeometryTransfer_extract(objCPtr);
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        free();
    }

    public synchronized void free() {
        if (objCPtr != 0) {
            jni.GeometryTransfer_free(objCPtr);
            objCPtr = 0;
            state = GeometryState.Empty;
        }
    }
}