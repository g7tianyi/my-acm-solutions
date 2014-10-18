#include <iostream>
/**
 * Standard KMP algorithm
 */
class Solution {
public:
    char* strStr(char* text, char* word) {
        if (text == NULL || word == NULL) {
            return NULL;
        }

        int textlen = strlen(text);
        int wordlen = strlen(word);
        vector<int> fail = kmpFail(word, wordlen);

        int i = 0, j = 0;
        while (i < textlen && j < wordlen) {
            if (j == -1 || text[i] == word[j]) {
                ++i; ++j;
            } else {
                j = fail[j];
            }
        }
        if (j == wordlen) {
            return text + (i - j);
        } else {
            return NULL;
        }
    }
private:
    vector<int> kmpFail(char* pattern, int len) {
        vector<int> fail(len + 1, -1);
        int i = 0, j = -1;
        while (i < len) {
            if (j == -1 || pattern[i] == pattern[j]) {
                // j is already in the leftmost, OR
                // pattern[0~k-1] == pattern[i-k~i-1] =>
                // pattern[0~k] == pattern[i-k~i], next[i+1] == k + 1 == next[i] + 1
                fail[++i] = ++j;
            } else {
                j = fail[j]; // backtracking
            }
        }
        return fail;
    }
};

Solution solu;

int main() {

    char buf1[] = "Returns a pointer to the first occurrence of needle in haystack";
    char buf2[] = "rence o";

    printf("%s\n", solu.strStr(buf1, buf2));

    return 0;
}

