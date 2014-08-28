package org.zoj.volumn1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;

public class ZOJ1005 {

    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) throws IOException {
        String line;
        int ca, cb, N;
        while (null != (line = reader.readLine())) {
            String[] strs = line.split("\\s+");
            ca = Integer.parseInt(strs[0]);
            cb = Integer.parseInt(strs[1]);
            N = Integer.parseInt(strs[2]);
            new BFS(ca, cb, N).run();
        }
    }

    private static enum Operation {
        FILL_1  ("fill A"), 
        FILL_2  ("fill B"), 
        EMPTY_1 ("empty A"), 
        EMPTY_2 ("empty B"), 
        POUR1_2 ("pour A B"), 
        POUR2_1 ("pour B A");
        
        private String operation;

        private Operation(String operation) {
            this.operation = operation;
        }

        public String val() {
            return this.operation;
        }
    }

    private static final class BFS {

        private Queue<State> queue = new ArrayDeque<State>();
        private boolean[][] flag = new boolean[1001][1001];
        private int fullCapacity1, fullCapacity2, target;

        public BFS(int capacity1, int capacity2, int target) {
            this.fullCapacity1 = capacity1;
            this.fullCapacity2 = capacity2;
            this.target = target;
            queue.add(new State(capacity1, capacity2));
            for (int i = 0; i < 1001; ++i) {
                for (int j = 0; j < 1001; ++j) {
                    flag[i][j] = true;
                }
            }
            flag[capacity1][capacity2] = false;
        }

        public void run() {
            while (!queue.isEmpty()) {
                State state = queue.poll();
                if (fullCapacity1 - state.currentCapacity1 == target
                        || fullCapacity2 - state.currentCapacity2 == target) {
                    for (Operation operation : state.operations) {
                        System.out.println(operation.val());
                    }
                    System.out.println("success");
                    break;
                }

                if (state.currentCapacity1 > 0) { // jug 1 has additional capacity
                    checkState(state.fill1());
                }
                if (state.currentCapacity2 > 0) { // jug 2 has additional capacity
                    checkState(state.fill2());
                }
                if (state.currentCapacity1 != fullCapacity1) { // jug 1 not empty
                    checkState(state.empty1());
                }
                if (state.currentCapacity2 != fullCapacity2) { // jug 2 not empty
                    checkState(state.empty2());
                }
                if (state.currentCapacity1 != fullCapacity1 // jug1 not empty
                        && state.currentCapacity2 > 0) { // jug2 not full
                    checkState(state.pour12());
                }
                if (state.currentCapacity2 != fullCapacity2 // jug2 not empty
                        && state.currentCapacity1 > 0) { // jug1 not full
                    checkState(state.pour21());
                }
            }
        }

        private void checkState(State state) {
            if (null != state) {
                queue.add(state);
            }
        }

        private final class State {
            private int currentCapacity1, currentCapacity2;
            private List<Operation> operations;

            public State(int capacity1, int capacity2) {
                this(capacity1, capacity2, new ArrayList<Operation>());
            }

            public State(int capacity1, int capacity2, List<Operation> operations) {
                this.currentCapacity1 = capacity1;
                this.currentCapacity2 = capacity2;
                this.operations = operations;
            }

            public State fill1() {
                return newState(0, this.currentCapacity2, Operation.FILL_1);
            }

            public State fill2() {
                return newState(this.currentCapacity1, 0, Operation.FILL_2);
            }

            public State empty1() {
                return newState(fullCapacity1, this.currentCapacity2, Operation.EMPTY_1);
            }

            public State empty2() {
                return newState(this.currentCapacity1, fullCapacity2, Operation.EMPTY_2);
            }

            public State pour12() {
                return pour(fullCapacity1, this.currentCapacity1, this.currentCapacity2, Operation.POUR1_2);
            }

            public State pour21() {
                return pour(fullCapacity2, this.currentCapacity2, this.currentCapacity1, Operation.POUR2_1);
            }

            private List<Operation> appendOperation(Operation operation) {
                List<Operation> newOperations = new ArrayList<Operation>(this.operations);
                newOperations.add(operation);
                return newOperations;
            }

            private State pour(int sourceFullCapacity, int sourceCurrentCapacity, int targetCurrentCapacity,
                    Operation operation) {
                int newSourceCapacity, newTargetCapacity;
                if (sourceFullCapacity - sourceCurrentCapacity > targetCurrentCapacity) {
                    newSourceCapacity = sourceCurrentCapacity + targetCurrentCapacity;
                    newTargetCapacity = 0;
                } else {
                    newSourceCapacity = sourceFullCapacity;
                    newTargetCapacity = targetCurrentCapacity - (sourceFullCapacity - sourceCurrentCapacity);
                }
                if (operation == Operation.POUR1_2) {
                    return newState(newSourceCapacity, newTargetCapacity, operation);
                } else {
                    return newState(newTargetCapacity, newSourceCapacity, operation);
                }
            }

            private State newState(int capacity1, int capacity2, Operation operation) {
                if (flag[capacity1][capacity2]) {
                    flag[capacity1][capacity2] = false;
                    return new State(capacity1, capacity2, appendOperation(operation));
                }
                return null;
            }
        }
    }

}
