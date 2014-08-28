package org.zoj.volumn1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ZOJ1046 {

    private static final int MAX_COL = 80;
    private static int fontCount, gridRow, gridColumn;
    private static Font[] fonts = new Font[MAX_COL];
    private static Font[] flags = new Font[MAX_COL];
    private static BufferedReader READER = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) throws IOException {
        String line;
        int cases = 1;
        while (null != (line = READER.readLine())) {
            String[] nums = line.split(" ");
            fontCount = Integer.parseInt(nums[0]);
            if (fontCount == 0) {
                break;
            }
            gridRow = Integer.parseInt(nums[1]);
            gridColumn = Integer.parseInt(nums[2]);
            
            int fontIndex;
            for (fontIndex = 0; fontIndex < fontCount; ++fontIndex) {
                fonts[fontIndex] = new Font();
                flags[fontIndex] = new Font();
            }
            for (int rowIndex = 0; rowIndex < gridRow; ++rowIndex) {
                line = READER.readLine();
                for (int columnIndex = 0; columnIndex < line.length(); ++columnIndex) {
                    if (line.charAt(columnIndex) != ' ' && line.charAt(columnIndex) != '\n') {
                      fontIndex = columnIndex / (gridColumn + 1);
                      fonts[fontIndex].append(line.charAt(columnIndex));
                      flags[fontIndex].append(line.charAt(columnIndex));
                    }
                }
            }
            
            boolean[] assigned = new boolean[fontCount];
            for (fontIndex = 0; fontIndex < fontCount; ++fontIndex) {
                assigned[fontIndex] = false;
            }

            // check if one # is sufficient for any font
            for (fontIndex = 0; fontIndex < fontCount; ++fontIndex) {
                for (int pos = 0; pos < gridRow * gridColumn; ++pos) {
                    if ('o' == fonts[fontIndex].value(pos) && isUnique(pos)) {
                        flags[fontIndex].value(pos, '#');
                        assigned[fontIndex] = true;
                        break;
                    }
                }
            }
            
            // check if two # is sufficient for some font
            boolean succeeded = true;
            for (fontIndex = 0; fontIndex < fontCount; ++fontIndex) {
                if (assigned[fontIndex]) {
                    continue;
                }
                boolean found = false;
                for (int pos1 = 0; pos1 < gridRow * gridColumn; ++pos1) {
                    for (int pos2 = pos1 + 1; pos2 < gridRow * gridColumn; ++pos2) {
                        if ('o' == fonts[fontIndex].value(pos1) 
                                && 'o' == fonts[fontIndex].value(pos2)
                                && isUnique(pos1, pos2)) {
                            flags[fontIndex].value(pos1, '#');
                            flags[fontIndex].value(pos2, '#');
                            assigned[fontIndex] = true;
                            found = true;
                            break;
                        }
                    }
                    if (found) {
                        break;
                    }
                }
                if (!found) {
                    succeeded = false;
                    break;
                }
            }
            
            // output
            System.out.println("Test " + cases);
            if (succeeded) {
                for (int rowIndex = 0; rowIndex < gridRow; ++rowIndex) {
                    for (fontIndex = 0; fontIndex < fontCount; ++fontIndex) {
                        System.out.print(flags[fontIndex].row(rowIndex));
                        if (fontIndex != fontCount - 1) {
                            System.out.print(" ");
                        }
                    }
                    System.out.println();
                }
            } else {
                System.out.println("impossible");
            }
            ++cases;
        }
    }
    
    private static boolean isUnique(int pos) {
        int count = 0;
        for (int fontIndex = 0; fontIndex < fontCount; ++fontIndex) {
            if ('o' == fonts[fontIndex].value(pos)) {
                ++count;
            }
        }
        return count == 1;
    }
    
    private static boolean isUnique(int pos1, int pos2) {
        int count = 0;
        for (int fontIndex = 0; fontIndex < fontCount; ++fontIndex) {
            if ('o' == fonts[fontIndex].value(pos1) 
                    && 'o' == fonts[fontIndex].value(pos2)) {
                ++count;
            }
        }
        return count == 1;
    }
    
    private static final class Font {
        private StringBuffer fingerprint = new StringBuffer();
        public void append(char ch) {
            fingerprint.append(ch);
        }
        public String row(int rowIndex) {
            return fingerprint.substring(rowIndex * gridColumn, (rowIndex + 1) * gridColumn);
        }
        public char value(int pos) {
            return fingerprint.charAt(pos);
        }
        public void value(int pos, char newValue) {
            fingerprint.setCharAt(pos, newValue);
        }
        @Override
        public String toString() {
            return fingerprint.toString();
        }
    }
}
