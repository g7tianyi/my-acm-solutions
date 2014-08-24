package org.zoj.volumn1;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public final class ZOJ1019 {

    private static final Scanner SCANNER = new Scanner(System.in);
    private static final int MAX_LENGTH = 100;

    private static int ROW, COLUMN;
    private static List<Move> MOVES = new ArrayList<Move>();
    private static int[][] GRID = new int[MAX_LENGTH][MAX_LENGTH];

    public static void main(String[] args) {
        int cases = SCANNER.nextInt();
        for (int i = 0; i < cases; ++i) {
            ROW = SCANNER.nextInt();
            COLUMN = SCANNER.nextInt();
            for (int r = 0; r < ROW; ++r) {
                for (int c = 0; c < COLUMN; ++c) {
                    GRID[r][c] = SCANNER.nextInt();
                }
            }

            MOVES.clear();
            int minMove, maxMove;
            while (true) {
                minMove = SCANNER.nextInt();
                maxMove = SCANNER.nextInt();
                if (minMove == 0 && maxMove == 0) {
                    break;
                }
                MOVES.add(new Move(minMove, maxMove, SCANNER.next().charAt(0)));
            }

            int count = 0;
            for (int r = 0; r < ROW; ++r) { // row
                for (int c = 0; c < COLUMN; ++c) { // column
                    if (GRID[r][c] != 1 && run(r, c, 0)) {
                        ++count;
                    }
                }
            }
            System.out.println(count);
        }
    }

    private static boolean run(int x, int y, int m) {
        if (m == MOVES.size()) {
            return true;
        }
        Move move = MOVES.get(m);
        for (int step = move.minMove; step <= move.maxMove; ++step) {
            if (movable(x, y, step, move.direction)) {
                if (move.direction == 'R' && run(x, y + step, m + 1)) {
                    return true;
                }
                if (move.direction == 'L' && run(x, y - step, m + 1)) {
                    return true;
                }
                if (move.direction == 'D' && run(x + step, y, m + 1)) {
                    return true;
                }
                if (move.direction == 'U' && run(x - step, y, m + 1)) {
                    return true;
                }
            }
        }
        return false;
    }

    private static boolean movable(int x, int y, int s, char d) {
        if (x < 0 || x >= ROW || y < 0 || y >= COLUMN || s == 0) {
            return true;
        }

        if (d == 'U' && x - s >= 0) {
            for (int i = 1; i <= s; ++i) {
                if (GRID[x - i][y] != 0) {
                    return false;
                }
            }
            return true;
        }

        if (d == 'D' && x + s < ROW) {
            for (int i = 1; i <= s; ++i) {
                if (GRID[x + i][y] != 0) {
                    return false;
                }
            }
            return true;
        }

        if (d == 'L' && y - s >= 0) {
            for (int i = 1; i <= s; ++i) {
                if (GRID[x][y - i] != 0) {
                    return false;
                }
            }
            return true;
        }

        if (d == 'R' && y + s < COLUMN) {
            for (int i = 1; i <= s; ++i) {
                if (GRID[x][y + i] != 0) {
                    return false;
                }
            }
            return true;
        }

        return false;
    }

    private static final class Move {
        private int minMove;
        private int maxMove;
        private char direction;

        public Move(int minMove, int maxMove, char direction) {
            this.minMove = minMove;
            this.maxMove = maxMove;
            this.direction = direction;
        }
    }
}
