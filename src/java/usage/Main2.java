import kom.geometry.core.Geometry;
import kom.geometry.core.GeometryTransfer;
import kom.geometry.jgpc.Gpc;
import kom.geometry.jgpc.GpcOperation;
import kom.geometry.jgpc.GpcPolygon;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

import static kom.geometry.core.Geometry.createContour;
import static kom.geometry.core.Geometry.createHole;
import static kom.tool.BoxLayoutUtils.createVerticalPane;

/**
 * User: syungman
 * Date: 30.10.13
 */
public class Main2 {

    public static void main(String[] args) {

        GpcPolygon poly1 = new GpcPolygon(
                createContour(50, 50, 50, 300, 300, 300, 300, 150, 400, 150, 400, 50),
                createContour(350, 200, 350, 400, 450, 400, 450, 200),
                createHole(250, 100, 250, 200, 100, 200, 100, 100)
        );

        GpcPolygon poly2 = new GpcPolygon(
            createContour(150, 150, 150, 300, 400, 300, 400, 150)
        );

        GeometryTransfer clip = Gpc.clip(GpcOperation.DIFF, poly1, poly2);
        Geometry[] geometry = clip.get();
        GpcPolygon opResult = new GpcPolygon(geometry);
    }
}
