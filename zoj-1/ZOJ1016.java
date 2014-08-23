package org.zoj;

import java.util.Scanner;

public class ZOJ1016 {

    private static final Scanner SCANNER = new Scanner(System.in);
    private static final char PARENTHESIS_LEFT = '(';
    private static final char PARENTHESIS_RIGHT = ')';
    private static final int MAX_LENGTH = 40;

    // match[i] indicate the matching right parenthesis of i
    private static int[] match = new int[MAX_LENGTH + 1];
    private static int[] stack = new int[MAX_LENGTH + 1];
    private static int[] pArray = new int[MAX_LENGTH + 1];
    private static int[][] cache = new int[MAX_LENGTH + 1][MAX_LENGTH + 1];

    private static int cases;
    private static int length;

    public static void main(String[] args) {
        cases = SCANNER.nextInt();
        for (int i = 0; i < cases; ++i) {
            length = SCANNER.nextInt();
            for (int j = 0; j < length; ++j) {
                pArray[j] = SCANNER.nextInt();
            }
            runByConstructingParenthesesString();
            if (i != cases - 1) {
                System.out.println();
            }
        }
    }

    private static void runByConstructingParenthesesString() {
        // constructing parentheses sequence
        StringBuffer sb = new StringBuffer();
        int dealtLeftCount = 0;
        for (int i = 0; i < length; ++i) {
            while (dealtLeftCount < pArray[i]) {
                ++dealtLeftCount;
                sb.append(PARENTHESIS_LEFT);
            }
            sb.append(PARENTHESIS_RIGHT);
        }

        int top = -1; // top of the stack
        for (int i = 0; i < sb.length(); ++i) {
            if (sb.charAt(i) == PARENTHESIS_RIGHT) {
                match[i] = stack[top];
                match[stack[top]] = i;
                --top; // pop one element
            } else {
                ++top; // push one element
                stack[top] = i;
            }
        }
        
        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < length; ++j) {
                cache[i][j] = 0;
            }
        }
        
        for (int i = 0; i < sb.length(); ++i) {
            if (sb.charAt(i) == PARENTHESIS_RIGHT) {
                System.out.print(countRange(match[i], i));
                if (i != sb.length() - 1) {
                    System.out.print(" ");
                }
            }
        }
    }

    private static int countRange(int start, int end) {
        if (cache[start][end] != 0) {
            return cache[start][end];
        } else if (start >= end) {
            return 0;
        } else if (start + 1 == end) {
            // case: ()
            cache[start][end] = 1;
            return 1;
        } else if (match[start] == end) {
            // case: (()()) 
            int res = 1 + countRange(start + 1, match[start + 1]) + countRange(match[start + 1] + 1, end - 1);
            cache[start][end] = res;
            return res;
        } else {
            // case: ()()
            int res = countRange(start, match[start]) + countRange(match[start] + 1, end);
            cache[start][end] = res;
            return res;
        }
    }
}
