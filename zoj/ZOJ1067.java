package org.zoj;

import java.util.Scanner;

public class ZOJ1067 {

    private static final Scanner SCANNER = new Scanner(System.in);
    
    private static final int TARGET_COLOR_COUNT = 16;
    private static final Color[] TARGET_COLORS = new Color[TARGET_COLOR_COUNT];
    
    public static void main(String[] args) {
        for (int i = 0; i < TARGET_COLOR_COUNT; ++i) {
            TARGET_COLORS[i] = new Color();
        }

        int targetIndex;
        double minDistance, distance;
        while (true) {
            Color color = new Color();
            if (color.r == -1 && color.g == -1 && color.b == -1) {
                break;
            }
            targetIndex = -1;
            minDistance = Double.MAX_VALUE;
            for (int i = 0; i < TARGET_COLOR_COUNT; ++i) {
                distance = Color.distance(color, TARGET_COLORS[i]);
                if (minDistance > distance) {
                    minDistance = distance;
                    targetIndex = i;
                }
            }
            System.out.println(String.format("%s maps to %s", color.toString(),
                    TARGET_COLORS[targetIndex].toString()));
        }
        
    }

    private static class Color {
        private int r, g, b;
        
        public Color() {
            r = SCANNER.nextInt();
            g = SCANNER.nextInt();
            b = SCANNER.nextInt();
        }

        public static double distance(Color left, Color right) {
            return Math.sqrt(Math.pow(left.r - right.r, 2)
                    + Math.pow(left.g - right.g, 2)
                    + Math.pow(left.b - right.b, 2));
        }
        
        @Override
        public String toString() {
            return String.format("(%d,%d,%d)", r, g, b);
        }
    }
    
}
