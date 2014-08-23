package org.zoj.volumn1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayDeque;
import java.util.Queue;

/**
 * Very simple BFS 
 */
public class ZOJ1091 {

    private static BufferedReader READER = new BufferedReader(
            new InputStreamReader(System.in));

    public static void main(String[] args) throws IOException {
        String line;
        boolean firstCase = true;
        while ((line = READER.readLine()) != null && line.length() != 0) {
            String[] elems = line.split("\\s+");
            int moves = new BFS(elems[0], elems[1]).run();
            if (!firstCase) {
                System.out.println();
            } else {
                firstCase = false;
            }
            System.out.print(String.format(
                    "To get from %s to %s takes %d knight moves.", elems[0],
                    elems[1], moves));
        }
    }

    private static final class BFS {

        private static final int BOARD_LENGTH = 8;
        private static final int[][] BOARD = new int[BOARD_LENGTH][BOARD_LENGTH];
        private Node startNode, endNode;

        public BFS(String source, String target) {
            int sourceX = source.charAt(0) - 'a';
            int sourceY = source.charAt(1) - '1';
            int targetX = target.charAt(0) - 'a';
            int targetY = target.charAt(1) - '1';
            this.startNode = new Node(sourceX, sourceY);
            this.endNode = new Node(targetX, targetY);
            for (int i = 0; i < BOARD_LENGTH; ++i) {
                for (int j = 0; j < BOARD_LENGTH; ++j) {
                    BOARD[i][j] = Integer.MAX_VALUE;
                }
            }
            BOARD[sourceX][sourceY] = 0;
        }

        public int run() {
            Queue<Node> queue = new ArrayDeque<Node>();
            queue.add(startNode);
            while (!queue.isEmpty()) {
                Node node = queue.poll();

                if (node.x == endNode.x && node.y == endNode.y) {
                    return node.value;
                }

                // each time the knight may have 8 positions to choose
                if (node.x + 2 < BOARD_LENGTH && node.y + 1 < BOARD_LENGTH
                        && node.value + 1 < BOARD[node.x + 2][node.y + 1]) {
                    BOARD[node.x + 2][node.y + 1] = node.value + 1;
                    queue.add(new Node(node.x + 2, node.y + 1, node.value + 1));
                }

                if (node.x + 2 < BOARD_LENGTH && node.y - 1 >= 0
                        && node.value + 1 < BOARD[node.x + 2][node.y - 1]) {
                    BOARD[node.x + 2][node.y - 1] = node.value + 1;
                    queue.add(new Node(node.x + 2, node.y - 1, node.value + 1));
                }

                if (node.x + 1 < BOARD_LENGTH && node.y + 2 < BOARD_LENGTH
                        && node.value + 1 < BOARD[node.x + 1][node.y + 2]) {
                    BOARD[node.x + 1][node.y + 2] = node.value + 1;
                    queue.add(new Node(node.x + 1, node.y + 2, node.value + 1));
                }

                if (node.x + 1 < BOARD_LENGTH && node.y - 2 >= 0
                        && node.value + 1 < BOARD[node.x + 1][node.y - 2]) {
                    BOARD[node.x + 1][node.y - 2] = node.value + 1;
                    queue.add(new Node(node.x + 1, node.y - 2, node.value + 1));
                }

                if (node.x - 2 >= 0 && node.y + 1 < BOARD_LENGTH
                        && node.value + 1 < BOARD[node.x - 2][node.y + 1]) {
                    BOARD[node.x - 2][node.y + 1] = node.value + 1;
                    queue.add(new Node(node.x - 2, node.y + 1, node.value + 1));
                }

                if (node.x - 2 >= 0 && node.y - 1 >= 0
                        && node.value + 1 < BOARD[node.x - 2][node.y - 1]) {
                    BOARD[node.x - 2][node.y - 1] = node.value + 1;
                    queue.add(new Node(node.x - 2, node.y - 1, node.value + 1));
                }

                if (node.x - 1 >= 0 && node.y + 2 < BOARD_LENGTH
                        && node.value + 1 < BOARD[node.x - 1][node.y + 2]) {
                    BOARD[node.x - 1][node.y + 2] = node.value + 1;
                    queue.add(new Node(node.x - 1, node.y + 2, node.value + 1));
                }

                if (node.x - 1 >= 0 && node.y - 2 >= 0
                        && node.value + 1 < BOARD[node.x - 1][node.y - 2]) {
                    BOARD[node.x - 1][node.y - 2] = node.value + 1;
                    queue.add(new Node(node.x - 1, node.y - 2, node.value + 1));
                }
            }
            return Integer.MAX_VALUE;
        }

        public static final class Node {
            int x, y, value;

            Node(int x, int y) {
                this(x, y, 0);
            }

            Node(int x, int y, int val) {
                this.x = x;
                this.y = y;
                this.value = val;
            }
        }
    }

}
