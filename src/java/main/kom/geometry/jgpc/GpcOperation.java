package kom.geometry.jgpc;

/**
 * Created with IntelliJ IDEA.
 * User: syungman
 * Date: 24.01.13
 * Time: 13:19
 */
public enum GpcOperation {
    // !warn: must be equals to gpc_op defined in gpc.h

    DIFF,                         /* Difference                        */
    INT,                          /* Intersection                      */
    XOR,                          /* Exclusive or                      */
    UNION;                        /* Union                             */

    private int value;

    GpcOperation() {
        this.value = Generator.value++;
    }

    public static GpcOperation valueOf(int value) {
        GpcOperation[] enums = GpcOperation.class.getEnumConstants();

        if (value >= 0 && value < enums.length)
            return enums[value];

        throw new IllegalArgumentException("No enum " + GpcOperation.class + " with value " + value);
    }

    public int getValue() {
        return value;
    }

    private static class Generator {
        static int value = 0;
    }
}
