package org.zoj;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

/**
 * ZOJ1004: Anagrams by Stack
 * http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=1004
 */
public class ZOJ1004 {

	private static BufferedReader reader = new BufferedReader(
			new InputStreamReader(System.in));

	public static void main(String[] args) throws IOException {
		String source, destination;
		while ((source = reader.readLine()) != null 
				&& source.length() != 0
				&& (destination = reader.readLine()) != null
				&& destination.length() != 0) {
			new DFS(source, destination).run();
		}
	}

	private static final class DFS {
		private String sourceString;
		private String destination;
		private StringBuffer stackString = new StringBuffer();
		private StringBuffer operations = new StringBuffer();

		private static final String PUSH = "i ";
		private static final String POP = "o ";

		public DFS(String source, String destination) {
			super();
			this.sourceString = source;
			this.destination = destination;
			this.stackString = new StringBuffer();
		}

		public void run() {
			System.out.println("[");
			if (accessible()) {
				runDFS(0, 0);
			}
			System.out.println("]");
		}

		private void runDFS(int srcIndex, int dstIndex) {
			if (dstIndex == destination.length()) {
				System.out.println(operations.toString());
				return;
			}
			if (srcIndex == sourceString.length()) {
				for (int i = stackString.length() - 1, j = dstIndex; 
						i >= 0 && j < sourceString.length();
						--i, ++j) {
					if (stackString.charAt(i) != destination.charAt(j)) {
						return;
					}
				}
				System.out.print(operations.toString());
				for (int i = 0; i < stackString.length(); ++i) {
					System.out.print(POP);
				}
				System.out.println();
				return;
			}

			operations.append(PUSH);
			stackString.append(sourceString.charAt(srcIndex));
			runDFS(srcIndex + 1, dstIndex);
			stackString.deleteCharAt(stackString.length() - 1);
			operations.delete(operations.length() - 2, operations.length());

			char dstChar = destination.charAt(dstIndex);
			if (stackString.length() > 0
					&& stackString.charAt(stackString.length() - 1) == dstChar) {
				operations.append(POP);
				stackString.deleteCharAt(stackString.length() - 1);
				runDFS(srcIndex, dstIndex + 1);
				stackString.append(dstChar);
				operations.delete(operations.length() - 2, operations.length());
			}
		}

		private boolean accessible() {
			if (sourceString.length() != destination.length()) {
				return false;
			}
			Map<Character, Integer> sourceCharCount = countChars(sourceString);
			Map<Character, Integer> targetCharCount = countChars(destination);
			for (Map.Entry<Character, Integer> entry : sourceCharCount.entrySet()) {
				Character key = entry.getKey();
				if (!targetCharCount.containsKey(key)
						|| !entry.getValue().equals(targetCharCount.get(key))) {
					return false;
				}
			}
			return true;
		}

		private Map<Character, Integer> countChars(String str) {
			Map<Character, Integer> charCount = new HashMap<Character, Integer>();
			for (int i = 0; i < str.length(); ++i) {
				char ch = str.charAt(i);
				if (!charCount.containsKey(ch)) {
					charCount.put(ch, 0);
				}
				charCount.put(ch, charCount.get(ch) + 1);
			}
			return charCount;
		}
	}
}
