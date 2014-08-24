package org.zoj.volumn1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * This version use DFS as well, but the standard DFS based varies, 
 * the efficiency shows enormous difference.
 */
public class ZOJ1020 {

    private static BufferedReader READER = new BufferedReader(new InputStreamReader(System.in));

    private static final Map<Integer, List<String>> DICTIONARY = new HashMap<Integer, List<String>>();
    private static final String SPACE = " ";
    private static final char UNASSIGNED = '*';
    private static final int CHAR_COUNT = 26;
    
    public static void main(String[] args) throws IOException {
        int numWords = Integer.parseInt(READER.readLine());
        for (int i = 0; i < numWords; ++i) {
            String word = READER.readLine().trim();
            int len = word.length();
            if (!DICTIONARY.containsKey(len)) {
                DICTIONARY.put(len, new ArrayList<String>());
            }
            DICTIONARY.get(len).add(word);
        }
        
        int cases = Integer.parseInt(READER.readLine());
        String line = READER.readLine();
        boolean[] charFlags = new boolean[CHAR_COUNT];
        StringBuffer sbWords;
        int distinctChars = 0;
        for (int i = 0; i < cases; ++i) {
            for (int j = 0; j < CHAR_COUNT; ++j) {
                charFlags[j] = false;
            }
            sbWords = new StringBuffer();
            while (null != (line = READER.readLine())
                    && 0 != line.trim().length()) {
                line = line.trim();
                sbWords.append(line).append(SPACE);
                for (int j = 0; j < line.length(); ++j) {
                    char ch = line.charAt(j);
                    if (ch != ' ' && !charFlags[ch - 'A']) {
                        charFlags[ch - 'A'] = true;
                        ++distinctChars;
                    }
                }
            }
            List<String> encryptedWords = Arrays.asList(sbWords.toString().split(SPACE));
            Collections.sort(encryptedWords, STRING_LENGTH_DESC_COMP);
            new DFS(encryptedWords, distinctChars).run();
        }
    }
    
    private static final class DFS {
        private int pathCount;
        private int unmappedChars;
        private final List<String> encryptedWords;
        private StringBuffer encryptMapping = new StringBuffer();
        private StringBuffer decryptMapping = new StringBuffer();
        private StringBuffer matchedTable;
        public DFS(List<String> encryptedWords, int unmappedChars) {
            this.pathCount = 0;
            this.unmappedChars = unmappedChars;
            this.encryptedWords = encryptedWords;
            for (int i = 0; i < CHAR_COUNT; ++i) {
                encryptMapping.append(UNASSIGNED);
                decryptMapping.append(UNASSIGNED);
            }
        }
        
        public void run() {
            run(0, encryptMapping, decryptMapping);
            if (pathCount == 0) {
                System.out.println("#No solution#");
            } else if(pathCount == 1) {
                System.out.println(matchedTable.toString());
            } else {
                System.out.println("#More than one solution#");
            }
        }
        
        private void run(int wordIndex, StringBuffer encryptMapping, StringBuffer decryptMapping) {
            if (wordIndex == encryptedWords.size()) {
                ++pathCount;
                matchedTable = encryptMapping;
                return;
            }
            
            if (unmappedChars == 0) {
                // optimization, all characters have been mapped to someone
                while (wordIndex < encryptedWords.size()) {
                    String encryptedWord = encryptedWords.get(wordIndex);
                    int currLen = encryptedWord.length();
                    if (!DICTIONARY.containsKey(currLen)) {
                        return;
                    }
                    List<String> decryptedWords = DICTIONARY.get(currLen);
                    boolean acceptable = false;
                    for (String decryptedWord : decryptedWords) { // options
                        if (wordsMatch(encryptedWord, decryptedWord, encryptMapping, decryptMapping)) {
                            acceptable = true;
                            break;
                        }
                    }
                    if (!acceptable) {
                        return;
                    }
                    ++wordIndex;
                }
                ++pathCount;
                matchedTable = encryptMapping;
                return;
            }
            
            String encryptedWord = encryptedWords.get(wordIndex);
            int currLen = encryptedWord.length();
            if (!DICTIONARY.containsKey(currLen)) {
                return;
            }
            List<String> decryptedWords = DICTIONARY.get(currLen);
            for (String decryptedWord : decryptedWords) { // options
                StringBuffer newEncryptMapping = new StringBuffer(encryptMapping.toString());
                StringBuffer newDecryptMapping = new StringBuffer(decryptMapping.toString());
                int originalUnmappedChars = unmappedChars;
                if (wordsMatch(encryptedWord, decryptedWord, newEncryptMapping, newDecryptMapping)) {
                    run(wordIndex + 1, newEncryptMapping, newDecryptMapping);
                    unmappedChars = originalUnmappedChars;
                    if (pathCount == 2) {
                        return;
                    }
                }
            }
        }
        
        private boolean wordsMatch(String encryptedWord, String decryptedWord,
                StringBuffer encryptMapping, StringBuffer decryptMapping) {
            char decryptedChar, encryptedChar;
            int decryptedCharIndex, encryptedCharIndex; 
            for (int index = 0; index < encryptedWord.length(); ++index) {
                decryptedChar = decryptedWord.charAt(index);
                encryptedChar = encryptedWord.charAt(index);
                decryptedCharIndex = decryptedChar - 'A';
                encryptedCharIndex = encryptedChar - 'A';
                if (encryptMapping.charAt(decryptedCharIndex) == UNASSIGNED
                        && decryptMapping.charAt(encryptedCharIndex) == UNASSIGNED) {
                    encryptMapping.setCharAt(decryptedCharIndex, encryptedChar);
                    decryptMapping.setCharAt(encryptedCharIndex, decryptedChar);
                    --unmappedChars;
                } else if (encryptMapping.charAt(decryptedCharIndex) != encryptedChar
                        || decryptMapping.charAt(encryptedCharIndex) != decryptedChar) {
                    return false;
                }
            }
            return true;
        }
    }

    private static final Comparator<String> STRING_LENGTH_DESC_COMP = new Comparator<String>() {
        @Override
        public int compare(String o1, String o2) {
            if (o1.length() > o2.length()) {
                return -1;
            } else if (o1.length() < o2.length()) {
                return 1;
            } else {
                return 0;
            }
        }
    };
}
