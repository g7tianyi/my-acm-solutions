KMP的實現模板
---
> 致謝： http://www.cnblogs.com/yjiyjige/p/3263858.html
```C++
int next[MAX_N];
//   0   k j-k j       0   k j-k j
//   |   | |   |       |   | |   |
//   A B C A B C D     A B C A B C D
//     |     |           |   | |   |
//    k-1   j-1        k-1 k+1 j-1 j+1
//
void get_next(char str[], int len) {
    next[0] = -1;
    int i = 0, j = -1;
    while (i < len - 1) {
        if (j == -1 // i is already in the lefemost, we can only shift i to the right
                || str[i] == str[j]) { // str[0~k-1] == str[i-k~i-1] => str[0~k] == str[i-k~i], next[i+1] == k + 1 == next[i] + 1
            next[++i] = ++j;
        } else {
            j = next[j]; // backtracking
        }
    }
}

int kmp_search(char text[], char pattern[]) {
    int i = 0, j = 0;
    while (i < strlen(text) && j < strlen(pattern)) {
        if (j == -1 || text[i] == pattern[j]) {
            ++i; ++j;
        } else {
            j = next[j];
        }
    }
    if (j == strlen(pattern)) {
        return i - j;
    } else {
        return -1;
    }
}
```

