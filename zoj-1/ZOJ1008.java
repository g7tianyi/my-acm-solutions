package org.zoj;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

public class ZOJ1008 {

    private static final BufferedReader READER = new BufferedReader(
            new InputStreamReader(System.in));

    private static int TEST_CASE = 0;
    public static void main(String[] args) throws IOException {
        String line;

        while (null != (line = READER.readLine())) {
            if (line.trim().equals("0")) {
                break;
            }

            int length = Integer.parseInt(line.trim());
            
            // Map.Key => square hash id, Map.value = square id
            Map<Integer, Integer> squareTypes = new HashMap<Integer, Integer>();
            Square[] squares = new Square[length * length];
            int index = 0;
            for (int i = 0; i < length * length; ++i) {
                line = READER.readLine();
                String[] elems = line.split("\\s+");
                int top    = Integer.parseInt(elems[0]);
                int right  = Integer.parseInt(elems[1]);
                int bottom = Integer.parseInt(elems[2]);
                int left   = Integer.parseInt(elems[3]);
                
                int squareHash = Square.hash(top, right, bottom, left);
                if (squareTypes.containsKey(squareHash)) {
                    int squareIndex = squareTypes.get(squareHash);
                    ++(squares[squareIndex].count);
                } else {
                    squareTypes.put(squareHash, index);
                    squares[index] = new Square(top, right, bottom, left);
                    ++index;
                }
            }
            new DFS(length, squares, index).run();
        }

    }

    private static final class DFS {
        private final int length;
        private final Square[] squares;
        private final int squareCount;
        private int[][] board = new int[5][5]; 

        public DFS(int length, Square[] squares, int squareCount) {
            this.length = length;
            this.squares = squares;
            this.squareCount = squareCount;
        }
        
        public void run() {
            if (TEST_CASE != 0) {
                System.out.println();
            }
            if (!runDFS(0, 0)) {
                System.out.println(String.format("Game %d: Impossible", ++TEST_CASE));
            } else {
                System.out.println(String.format("Game %d: Possible", ++TEST_CASE));
            }
        }

        private boolean runDFS(int x, int y) {
            int upperX = -1, upperY = y;
            int leftX = x, leftY = -1;
            if (x > 0) {
                upperX = x - 1;
            }
            if (y > 0) {
                leftY = y - 1;
            }
            
            int nextX = x, nextY = y + 1;
            if (y + 1 == length) {
                nextX = x + 1;
                nextY = 0;
            }
            
            for (int index = 0; index < squareCount; ++index) {
                Square square = squares[index];
                if (square.count == 0
                        || (upperX >= 0 && squares[board[upperX][upperY]].bottom != square.top) // check upper square
                        || (leftY >= 0 && squares[board[leftX][leftY]].right != square.left)) { // check left square
                    continue;
                }
                if (nextX == length) {
                    return true;
                }
                board[x][y] = index;
                --square.count;
                if(runDFS(nextX, nextY)) {
                    return true;
                }
                ++square.count;
            }
            return false;
        }
    }

    private static class Square {
        private int count = 1;
        private final int top, right, bottom, left;
        public Square(int top, int right, int bottom, int left) {
            this.top    = top;
            this.right  = right;
            this.bottom = bottom;
            this.left   = left;
        }
        @Override
        public String toString() { // for debug
            return String.format("%d:\t%d\t%d\t%d\t%d", count, top, right, bottom, left);
        }
        // we do not use the member function hashCode() to reduce the cost of new a Square object
        // which maybe unnecessary if the Square appeared before
        // this problem is really time-intense
        public static int hash(int top, int right, int bottom, int left) {
            return (top << 10) + (right << 7) + (bottom << 4) + left;
        }
    }
}
