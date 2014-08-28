package org.zoj;

import java.util.Scanner;

public class ZOJ1048 {

    private static final Scanner SCANNER = new Scanner(System.in);

    private static final int MONTHS = 12;

    public static void main(String[] args) {
        double sum = 0.0;
        for (int i = 0; i < MONTHS; ++i) {
            sum += SCANNER.nextDouble();
        }
        System.out.print("$");
        System.out.printf("%.2f\n", sum / 12);
    }

}
