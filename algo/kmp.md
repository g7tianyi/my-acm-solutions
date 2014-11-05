KMP小結
---
> 致謝： http://www.cnblogs.com/yjiyjige/p/3263858.html

##訓練題推薦

> [POJ 1961](https://github.com/g7tianyi/my-acm-solutions/blob/master/poj/String/poj1961.cc)

> [POJ 2752](https://github.com/g7tianyi/my-acm-solutions/blob/master/poj/String/poj2752.cc)

> [POJ 3461](https://github.com/g7tianyi/my-acm-solutions/blob/master/poj/String/poj3461.cc)

> [POJ 2406](https://github.com/g7tianyi/my-acm-solutions/blob/master/poj/String/poj2406.cc)


##代碼模板
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

