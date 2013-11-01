package kom.tool;

import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.text.DocumentFilter;
import javax.swing.text.PlainDocument;
import javax.swing.text.StringContent;
import java.awt.*;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

/**
 * Created with IntelliJ IDEA.
 * User: syungman
 * Date: 25.12.12
 * Time: 16:09
 */
public class BoxLayoutUtils {

    public static JPanel createHorizontalPane() {
        final JPanel result = new JPanel();
        result.setLayout(new BoxLayout(result, BoxLayout.X_AXIS));
        return result;
    }

    public static JPanel createVerticalPane() {
        final JPanel result = new JPanel();
        result.setLayout(new BoxLayout(result, BoxLayout.Y_AXIS));
        return result;
    }

    public static JPanel createVerticalPane(Component... components) {
        final JPanel result = createVerticalPane();
        //result.setBorder(BorderFactory.createLineBorder(Color.GREEN));

        for (Component component : components) {
            result.add(component);
        }

        return  result;
    }

    public static JPanel createVerticalPane(int strut, Component... components) {
        if (components.length == 0) {
            return createVerticalPane();
        }

        final Component[] strutted = new Component[components.length * 2 - 1];

        for (int i = 0; i < strutted.length; ++i) {
            if (i % 2 == 0) {
                strutted[i] = components[i/2];
            } else {
                strutted[i] = Box.createVerticalStrut(strut);
            }
        }

        return createVerticalPane(strutted);
    }

    public static JPanel createHorizontalPane(Component... components) {
        final JPanel result = createHorizontalPane();
        //result.setBorder(BorderFactory.createLineBorder(Color.BLUE));

        for (Component component : components) {
            result.add(component);
        }

        return  result;
    }

    public static JPanel createHorizontalPane(int strut, Component... components) {
        if (components.length == 0) {
            return createHorizontalPane();
        }

        final Component[] strutted = new Component[components.length * 2 - 1];

        for (int i = 0; i < strutted.length; ++i) {
            if (i % 2 == 0) {
                strutted[i] = components[i/2];
            } else {
                strutted[i] = Box.createHorizontalStrut(strut);
            }
        }

        return createHorizontalPane(strutted);
    }

    public static void makeSameWidth(Component... components) {
        int maxWidth = 0;
        for (Component component : components) {
            if (component.getPreferredSize().width > maxWidth) {
                maxWidth = component.getPreferredSize().width;
            }
        }

        for (Component component : components) {
            final Dimension size = component.getPreferredSize();
            size.setSize(maxWidth, size.height);

            component.setMinimumSize(size);
            component.setPreferredSize(size);
            component.setMaximumSize(size);
        }
    }

    public static void makeSameSize(Component... components) {
        makeSameHeight(components);
        makeSameWidth(components);
    }

    public static void makeSameSize(int alignment, JLabel... labels) {
        makeSameSize(labels);

        for (JLabel label : labels) {
            label.setHorizontalAlignment(alignment);
        }
    }

    public static void makeSameHeight(Component... components) {
        int maxHeight = 0;
        for (Component component : components) {
            if (component.getPreferredSize().height > maxHeight) {
                maxHeight = component.getPreferredSize().height;
            }
        }

        for (Component component : components) {
            final Dimension size = component.getPreferredSize();
            size.setSize(size.width, maxHeight);

            component.setMinimumSize(size);
            component.setPreferredSize(size);
            component.setMaximumSize(size);
        }
    }

    public static void bindPropertyChangeListener(final JTextField field, final String name,
                                                  final PropertyChangeListener listener) {
        bindPropertyChangeListener(field, name, listener, null);
    }

    public static void bindPropertyChangeListener(final JTextField field, final String name, final PropertyChangeListener listener,
                                                  DocumentFilter documentFilter) {

        if (field.getDocument() == null) {
            field.setDocument(new PlainDocument(new StringContent()));
        }

        final PlainDocument document = (PlainDocument)field.getDocument();

        if (documentFilter != null) {
            document.setDocumentFilter(documentFilter);
        }

        field.getDocument().addDocumentListener(new DocumentListener() {
            @Override
            public void insertUpdate(DocumentEvent e) {
                fireChangeEvent();
            }

            @Override
            public void removeUpdate(DocumentEvent e) {
                fireChangeEvent();
            }

            @Override
            public void changedUpdate(DocumentEvent e) {
                fireChangeEvent();
            }

            private void fireChangeEvent() {
                listener.propertyChange(new PropertyChangeEvent(field, name, "", field.getText()));
            }
        });
    }

    public static Component freezeSize(final Component component) {
        final Dimension size = component.getPreferredSize();

        component.setMinimumSize(size);
        component.setPreferredSize(size);
        component.setMaximumSize(size);

        return component;
    }

    public static JTextField fixTextFieldSize(JTextField field) {
        final Dimension size = field.getPreferredSize();
        size.width = field.getMaximumSize().width;
        field.setMaximumSize(size);

        return field;
    }

    public static void fixTextFieldsSize(JTextField... jTextFields) {
        for (JTextField field : jTextFields) {
            fixTextFieldSize(field);
        }
    }

    public static void setGroupAlignmentX(float alignment, Component... components) {
        for (Component component : components) {
            if (component instanceof JComponent)
                ((JComponent) component).setAlignmentX(alignment);
        }
    }

    public static void setGroupAlignmentY(float alignment, Component... components) {
        for (Component component : components) {
            if (component instanceof JComponent)
                ((JComponent) component).setAlignmentY(alignment);
        }
    }
}