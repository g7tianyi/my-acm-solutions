package org.zoj;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ZOJ1006 {

	private static BufferedReader reader = new BufferedReader(
			new InputStreamReader(System.in));
	
	public static void main(String[] args) throws IOException {
		String line;
		while (null != (line = reader.readLine())) {
			String elems[] = line.split("\\s+");
			if (elems[0].equals("0")) {
				break;
			}
			int key = Integer.parseInt(elems[0]);
			String cipherText = elems[1];
			int len = cipherText.length();
			int[] plainCode = new int[len];
			for (int i = 0; i < len; ++i) {
				int cipherCode = toCipherCode(cipherText.charAt(i));
				// according to cipherCode[i] = (plainCode[k * i % n] - i) % 28,
				// plainCode  = 28 * n + cipherCode
				// make sure that plainCode less than 28
				while (cipherCode + i >= 28) {
					cipherCode -= 28;
				}
				plainCode[mod(key * i, len)] = cipherCode + i;
			}
			for (int i = 0; i < len; ++i) {
				System.out.print(toPlainChar(plainCode[i]));
			}
			System.out.println();
		}
	}

	private static int mod(int a, int b) {
		return a % b + (a % b >= 0 ? 0 : b);
	}
	private static int toCipherCode(char ch) {
		if (ch == '_') {
			return 0;
		}
		if (ch == '.') {
			return 27;
		}
		return ch - 'a' + 1;
	}
	private static char toPlainChar(int c) {
		if (c == 0) {
			return '_';
		}
		if (c == 27) {
			return '.';
		}
		return (char) (((int)('a')) + c - 1);
	}
}
