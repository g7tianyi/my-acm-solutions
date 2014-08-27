package org.zoj.volumn1;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

/**
 * Floyd algo
 */
public class ZOJ1053 {

    private static final Scanner SCANNER = new Scanner(System.in);
    private static final int MAX_NODE = 20;
    private static int caseCount;
    private static int nodeCount;
    private static int destination;
    private static int[][] cost = new int[MAX_NODE][MAX_NODE];
    private static int[][] path = new int[MAX_NODE][MAX_NODE];

    public static void main(String[] args) {
        caseCount = SCANNER.nextInt();
        int currCase = 0;
        while (true) {
            nodeCount = SCANNER.nextInt();
            for (int i = 0; i < nodeCount; ++i) {
                for (int j = 0; j < nodeCount; ++j) {
                    cost[i][j] = SCANNER.nextInt();
                    path[i][j] = j;
                }
            }
            
            // Floyd 
            for (int k = 0; k < nodeCount; ++k) {
                for (int i = 0; i < nodeCount; ++i) {
                    for (int j = 0; j < nodeCount; ++j) {
                        if (cost[i][k] >= 0 && cost[k][j] >= 0 
                                && (cost[i][j] < 0 || cost[i][j] > cost[i][k] + cost[k][j])) {
                            cost[i][j] = cost[i][k] + cost[k][j];
                            path[i][j] = path[i][k];
                        }
                    }
                }
            }
            
            SCANNER.nextLine();
            String line = SCANNER.nextLine();
            String[] elems = line.split("\\s+");
            destination = Integer.parseInt(elems[0]);
            
            Intersection[] intersections = new Intersection[elems.length - 1];
            int pos; 
            for (int i = 1; i < elems.length; ++i) {
                pos = Integer.parseInt(elems[i]);
                intersections[i - 1] = new Intersection(pos, cost[pos - 1][destination - 1]);
                intersections[i - 1].path.append(pos);
                while (pos != destination) {
                    pos = path[pos - 1][destination - 1] + 1;
                    intersections[i - 1].path.append('\t').append(pos);
                }
            }
            
            List<Intersection> sortedIntersections = Arrays.asList(intersections);
            Collections.sort(sortedIntersections);
            System.out.println("Org\tDest\tTime\tPath");
            for (Intersection intersection : sortedIntersections) {
                System.out.printf("%d\t%d\t%d\t%s\n", intersection.pos, destination, intersection.cost,
                        intersection.path.toString());
            }

            if (++currCase < caseCount) {
                System.out.println();
            } else {
                break;
            }
        }
    }
    
    private static final class Intersection implements Comparable<Intersection> {
        private int pos;
        private int cost;
        private StringBuffer path = new StringBuffer();
        public Intersection(int pos, int cost) {
            this.pos = pos;
            this.cost = cost;
        }
        @Override
        public int compareTo(Intersection o) {
            if (this.cost < o.cost) {
                return -1;
            } else if (this.cost > o.cost) {
                return 1;
            } else {
                return 0;
            }
        }
        @Override
        public String toString() { // for debug
            return String.format("%d\t%d\t%d", pos, cost, path);
        }
    }
}
