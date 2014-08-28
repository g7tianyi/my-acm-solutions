package org.zoj.volumn1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

/**
 * Trie is fast !
 */
public class ZOJ1050 {

    private static final BufferedReader READER = new BufferedReader(new InputStreamReader(System.in));
    
    private static final String SEPERATION_LINE = "----------";
    private static final int CHAR_COUNT = 36;
    
    public static void main(String[] args) throws IOException {
        int cases = Integer.parseInt(READER.readLine().trim());
        int currCase = 0;
        while (currCase < cases) {
            if (currCase > 0) {
                System.out.println();
            }
            READER.readLine(); // empty line after cases
            
            String line;
            
            Trie queryTrie = new Trie();
            while (true) {
                line = READER.readLine();
                if (line.trim().equals(SEPERATION_LINE)) {
                    break;
                }
                String queryWords[] = normalize(line).split("\\s+");
                for (String queryWord: queryWords) {
                    if (queryWord.length() > 0) {
                        queryTrie.add(queryWord);
                    }
                }
            }
            
            boolean prevLineDash = false;
            Trie docTrie = new Trie();
            List<String> words = new ArrayList<String>();
            while (null != (line = READER.readLine())) {
                if (line.trim().equals(SEPERATION_LINE)) {
                    if (prevLineDash) {
                        break;
                    }
                    
                    // calculate previous case
                    double score = 0.0;
                    int queryCount, docCount;
                    for (String word : words) {
                        queryCount = queryTrie.count(word);
                        if (queryCount == 0) {
                            continue;
                        }
                        docCount = docTrie.count(word);
                        score += Math.sqrt(queryCount * docCount);
                    }
                    System.out.printf("%.2f\n", score);

                    prevLineDash = true;
                    docTrie = new Trie();
                    words.clear();
                    continue;
                }
                
                prevLineDash = false;
                line = normalize(line);
                String[] docWords = line.split("\\s+");
                for (String docWord: docWords) {
                    if (docWord.length() > 0 && docTrie.add(docWord)) {
                        words.add(docWord);
                    }
                }
            }
            
            ++currCase;
        }
    }
    
    public static String normalize(String input) {
        char[] charArray = input.trim().toLowerCase().toCharArray();
        StringBuilder sb = new StringBuilder();
        for (char ch : charArray) {
            if (ch == ' ' || indexOf(ch) >= 0) {
                sb.append(ch);
            }
        }
        return sb.toString();
    }
    
    public static int indexOf(char ch) {
        int code = ch - 'a';
        if (code >= 0 && code < 26) {
            return code;
        }
        code = ch - '0';
        if (code >= 0 && code < 10) {
            return code;
        }
        return -1;
    }

    public static final class Trie {
        private int count;
        private Trie[] links;
        public Trie() {
            this.count = 0;
            this.links = new Trie[CHAR_COUNT];
        }

        // return true if it is a brand new word
        public boolean add(String word) {
            int length = word.length(), index;
            char[] chars = word.toCharArray();
            Trie curr = this;
            for (int i = 0; i < length; i++) {
                index = indexOf(chars[i]);
                if (curr.links[index] == null) {
                    curr.links[index] = new Trie();
                }
                curr = curr.links[index];
            }
            ++curr.count;
            return curr.count == 1;
        }

        public int count(String word) {
            char[] letters = word.toCharArray();
            int length = letters.length;
            Trie curr = this;
            int index;
            for (index = 0; index < length; index++) {
                if (curr == null) {
                    return 0;
                }
                curr = curr.links[indexOf(letters[index])];
            }
            if (index == length && curr == null) {
                return 0;
            }
            return curr.count;
        }
    }

}
