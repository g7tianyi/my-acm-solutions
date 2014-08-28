package org.zoj;

import java.util.Scanner;

/**
 * Formula:
 *   1 + PI * (x * x +  y * y) / 2 / 50
 */
public class ZOJ1049 {

    private static final Scanner SCANNER = new Scanner(System.in);
    
    private static final double FORMULA_CONSTANT = Math.PI / 100; // Save some tiny calculation
    
    public static void main(String[] args) {
        int cases = SCANNER.nextInt();
        int year;
        double coordinateX, coordinateY;
        for (int i = 0; i < cases; ++i) {
            coordinateX = SCANNER.nextDouble();
            coordinateY = SCANNER.nextDouble();
            year = (int) (FORMULA_CONSTANT * (Math.pow(coordinateX, 2) + Math.pow(coordinateY, 2))) + 1;
            System.out.printf("Property %d: This property will begin eroding in year %d.\n", i + 1, year);
        }
        System.out.printf("END OF OUTPUT.\n");
    }
}
