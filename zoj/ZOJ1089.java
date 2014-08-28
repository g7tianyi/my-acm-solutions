package org.zoj.volumn1;

import java.util.Scanner;

public class ZOJ1089 {

    private static final Scanner SCANNER = new Scanner(System.in);
    private static final int MAX_SET_SIZE = 13;
    private static int size;
    private static int[] numbers = new int[MAX_SET_SIZE];

    public static void main(String[] args) {
        int cases = 0;
        while (true) {
            size = SCANNER.nextInt(); // size
            if (size == 0) {
                break;
            }
            if (cases++ > 0) {
                System.out.println();
            }
            for (int i = 0; i < size; ++i) {
                numbers[i] = SCANNER.nextInt();
            }

            for (int a = 0; a < size; ++a)
                for (int b = a + 1; b < size; ++b)
                    for (int c = b + 1; c < size; ++c)
                        for (int d = c + 1; d < size; ++d)
                            for (int e = d + 1; e < size; ++e)
                                for (int f = e + 1; f < size; ++f)
                                    System.out.printf("%d %d %d %d %d %d\n", numbers[a], numbers[b], numbers[c],
                                            numbers[d], numbers[e], numbers[f]);
        }

    }
}
