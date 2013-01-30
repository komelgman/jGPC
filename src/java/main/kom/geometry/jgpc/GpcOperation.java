/*******************************************************************************
 * Copyright 2013 Sergey Yungman
 *
 * Licensed under the LGPL Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.gnu.org/copyleft/lesser.html
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

package kom.geometry.jgpc;

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
