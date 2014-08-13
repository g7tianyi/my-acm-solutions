import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * In fact, we don't have to use 1-d array...
 */
public class ZOJ1002 {

	private static BufferedReader reader = new BufferedReader(
			new InputStreamReader(System.in));

	public static void main(String[] args) throws IOException {
		while (true) {
			int n = Integer.parseInt(reader.readLine());
			if (n == 0) {
				break;
			}
			DFS dfs = new DFS(n);
			dfs.read();
			System.out.println(dfs.run());
		}
	}

	private static class DFS {

		private int sideLen;
		private int[] status = new int[4 * 4 + 1];
		private boolean[] blocks = new boolean[4 * 4 + 1];

		public DFS(int n) {
			this.sideLen = Math.abs(n);
		}

		public void read() throws IOException {
			String str = "";
			for (int i = 0; i < sideLen; ++i) {
				str = reader.readLine();
				for (int j = 0; j < sideLen; ++j) {
					blocks[i * sideLen + j] = (str.charAt(j) == 'X');
					status[i * sideLen + j] = 0;
				}
			}
		}

		public int run() {
			return run(0, 0, 0);
		}

		private int run(int row, int column, int count) {
			if (row == sideLen || column == sideLen) {
				return count;
			}
			
			int nextRow = row;
			int nextColumn;
			if (column < sideLen - 1) {
				nextColumn = column + 1;
			} else {
				nextRow = row + 1;
				nextColumn = 0;
			}
			
			int result = count;
			int newMax;
			int index = toUnaryIndex(row, column);
			if (!blocks[index] && status[index] == 0) { // current position is available
				disable(row, column); // occupy it
				newMax = run(nextRow, nextColumn, count + 1);
				if (result < newMax) {
					result = newMax;
				}
				enable(row, column); // release it for backtrack
			}
			
			newMax = run(nextRow, nextColumn, count);
			if (result < newMax) {
				result = newMax;
			}
			
			return result;
		}

		private void enable(int x, int y) {
			updateStatus(x, y, -1);
		}

		private void disable(int x, int y) {
			updateStatus(x, y, 1);
		}

		private int toUnaryIndex(int x, int y) {
			return x * sideLen + y;
		}

		private void updateStatus(int x, int y, int flag) {
			status[toUnaryIndex(x, y)] += flag;
			
			int i, index;
			// flood left
			for (i = y - 1; i >= 0; --i) {
				index = toUnaryIndex(x, i);
				if (blocks[index]) {
					break;
				}
				status[index] += flag;
			}
			// flood right
			for (i = y + 1; i < sideLen; ++i) {
				index = toUnaryIndex(x, i);
				if (blocks[index]) {
					break;
				}
				status[index] += flag;
			}
			// flood up
			for (i = x - 1; i >= 0; --i) {
				index = toUnaryIndex(i, y);
				if (blocks[index]) {
					break;
				}
				status[index] += flag;
			}
			// flood down
			for (i = x + 1; i < sideLen; ++i) {
				index = toUnaryIndex(i, y);
				if (blocks[index]) {
					break;
				}
				status[index] += flag;
			}
		}
	}

}
