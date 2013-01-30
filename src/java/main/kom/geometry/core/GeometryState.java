package kom.geometry.core;

/**
* Created with IntelliJ IDEA.
* User: syungman
* Date: 25.01.13
* Time: 17:21
*/
public enum GeometryState {
    // !warn: must be equal enum in GeometryTransfer.h
    Empty, Initial, GpcPoly, GpcTriStrips;

    int value;

    GeometryState() {
        value = Generator.value++;
    }

    public static GeometryState valueOf(int value) {
        GeometryState[] enums = GeometryState.class.getEnumConstants();

        if (value >= 0 && value < enums.length)
            return enums[value];

        throw new IllegalArgumentException("No enum " + GeometryState.class + " with value " + value);
    }

    public int getValue() {
        return value;
    }

    private static class Generator {
        static int value = 0;
    }
}
