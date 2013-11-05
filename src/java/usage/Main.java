import kom.geometry.core.Geometry;
import kom.geometry.core.GeometryTransfer;
import kom.geometry.jgpc.Gpc;
import kom.geometry.jgpc.GpcOperation;
import kom.geometry.jgpc.GpcPolygon;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import static kom.geometry.core.Geometry.createContour;
import static kom.geometry.core.Geometry.createHole;
import static kom.tool.BoxLayoutUtils.*;

/**
 * User: syungman
 * Date: 30.10.13
 */
public class Main {

    private static final GpcPolygon poly1 = new GpcPolygon(
            createContour(50, 50, 50, 300, 300, 300, 300, 150, 400, 150, 400, 50),
            createContour(350, 200, 350, 400, 450, 400, 450, 200),
            createHole(250, 100, 250, 200, 100, 200, 100, 100)
    );

    private static final GpcPolygon poly2 = new GpcPolygon(
            createContour(150, 150, 150, 300, 400, 300, 400, 150)
    );

    private static GpcPolygon opResult;
    private static int showItem = 0;


    public static void main(String[] args) {
        final JFrame frame = new JFrame();

        opResult = new GpcPolygon(Gpc.clip(GpcOperation.DIFF, poly1, poly2).get());

        ActionListener opListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                GpcOperation operation = GpcOperation.valueOf(e.getActionCommand());
                GeometryTransfer clip = Gpc.clip(operation, poly1, poly2);
                Geometry[] geometry = clip.get();
                opResult = new GpcPolygon(geometry);
                frame.repaint();
            }
        };

        ActionListener showListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (e.getActionCommand().equals("Result"))
                    showItem = 0;
                else if (e.getActionCommand().equals("Operand A"))
                    showItem = 1;
                else
                    showItem = 2;

                frame.repaint();
            }
        };

        frame.add(
            createVerticalPane(
                createHorizontalPane(10, createRadioButtons(opListener, "DIFF", "INT", "XOR", "UNION")),
                createHorizontalPane(10, createRadioButtons(showListener, "Result", "Operand A", "Operand B")),
                new JComponent() {
                    {
                        setPreferredSize(new Dimension(500, 500));
                    }
                    protected void paintComponent(Graphics g) {
                        if (showItem == 0 && opResult != null)
                            draw((Graphics2D) g, opResult);
                        else if (showItem == 1)
                            draw((Graphics2D) g, poly1);
                        else if (showItem == 2)
                            draw((Graphics2D) g, poly2);
                    }
                }
            )
        );

        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }

    private static JRadioButton[] createRadioButtons(ActionListener listener, String ... names) {
        JRadioButton[] result = new JRadioButton[names.length];

        ButtonGroup group = new ButtonGroup();
        for (int i = 0; i < names.length; ++i) {
            result[i] = new JRadioButton(names[i]);
            result[i].addActionListener(listener);
            result[i].setActionCommand(names[i]);
            group.add(result[i]);
        }

        result[0].setSelected(true);

        return result;
    }

    private static void draw(Graphics2D g2d, GpcPolygon polygon) {
        for (Geometry geometry : polygon.getGeometries()) {
            draw(g2d, geometry);
        }
    }

    static void draw(Graphics2D g2d, Geometry geometry) {
        if (geometry.getVertices().length < 2)
            return;

        Polygon shape = new Polygon();
        double[] vertices = geometry.getVertices();

        for (int i = 0; i < vertices.length; i += 2) {
            shape.addPoint((int) vertices[i], (int) vertices[i + 1]);
        }

        g2d.setPaint(geometry.getTag() == Geometry.TAG_CONTOUR ? Color.BLUE : Color.RED);
        g2d.draw(shape);
    }
}
