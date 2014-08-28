package org.zoj;

import java.util.Scanner;

/**
 * Case 1: either m or n is a even number ==> No need to take a diagonal path ==> m * n
 * Case 2: both m and n are odd number ==> At least one diagonal path will be taken ==> m * n + sqrt(2) - 1
 */
public class ZOJ1037 {
    
    private static final Scanner SCANNER = new Scanner(System.in);
    
    public static void main(String[] args) {
        int cases = SCANNER.nextInt();
        for (int i = 0; i < cases; ++i) {
            System.out.println(String.format("Scenario #%d:", i + 1));
            int m = SCANNER.nextInt();
            int n = SCANNER.nextInt();
            if ((m & 1) == 0 || (n & 1) == 0) {
                System.out.printf("%.2f\n\n", (double) m * n);
            } else {
                System.out.printf("%.2f\n\n", (m * n + Math.sqrt(2.0) - 1));
            }
        }
    }
}
