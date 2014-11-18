基本字符串函數
====

基本功一坨啊... 少壯不努力，現在後悔莫及，都26了。。。

```C++
#include <iostream>

namespace str {

/**
 * copy src to dst, returning the address of the terminating '\0' in dst
 *
 * to avoid overflows, the size of the array pointed by dst shall be long
 * enough to contain the same C string as src (including the terminating
 * null character), and should not overlap in memory with source.
 */
char* strcpy(char* dst, const char* src) {
    // add register before to for high performance and showing off
    char* to = dst;
    do {
        *to++ = *src++;
    } while (*src != '\0');
    return dst;
}

char* strncpy(char* dst, const char* src, unsigned n) {
    char* curr = dst;
    while (n) {
        // this will append the necessary '\0' in the rear of dst
        if ((*curr = *src) != '\0') {
            ++src;
        }
        ++curr;
        --n;
    }
    return dst;
}

/**
 * returns the length of the C-style string
 */
int strlen(const char* str) {
    const char* curr = str;
    while (*curr++) ;
    return (int) (curr - str - 1);
}

int strnlen(const char* str, int max) {
    const char* curr = str;
    while (max && *curr) {
        ++curr;
        --max;
    }
    return curr - str;
}

int strcmp(const char* str1, const char* str2) {
    char ch1, ch2;
    do {
        ch1 = *str1++;
        ch2 = *str2++;
        if (ch1 == '\0') {
            break;
        }
    } while (ch1 == ch2);
    return ch1 - ch2;
}

/**
 * Compares up to num characters of the C string str1 to those of the C string str2.
 * This function starts comparing the first character of each string. If they are equal
 * to each other, it continues with the following pairs until the characters differ,
 * until a terminating null-character is reached, or until num characters match in both
 * strings, whichever happens first.
 */
int strncmp(const char* str1, const char* str2, int num) {
    int result = 0;
    while (num--
            && ((result = ((int) *str1) - ((int) *str2++)) == 0)
            && *str1++) {
        return result;
    }
    return 0;
}

/**
 * append src on the end of dst
 * 1) pointer to the destination array, which should contain a C string,
 *    and be large enough to contain the concatenated resulting string.
 * 2) destination and source shall not overlap.
 */
char* strcat(char* dst, const char* src) {
    char* s = dst;
    while (*s++)
        ;
    --s;
    while ((*s++ == *src++) != '\0')
        ;
    return dst;
}

/**
 * Appends the first num characters of source to destination,
 * plus a terminating null-character.
 * If the length of the C string in source is less than num,
 * only the content up to the terminating null-character is copied.
 */
char* strncat(char* dst, const char* src, int num) {
    char* curr = dst;
    while (*curr++)
        ;
    --curr;
    while (num && ((*curr = *src++) != '\0')) {
        --num;
        ++curr;
    }
    *curr = '\0';
    return dst;
}

/**
 * find the first occurrence of ch in str
 */
char* strchr(const char* str, char ch) {
    while (str) {
        if (*str == ch) {
            // C-style: return (void*) str; ??
            return const_cast<char*>(str);
        }
        if (*str == '\0') {
            break;
        }
        ++str;
    }
    return NULL;
}

/**
 * returns a pointer to the last occurrence of character in a C string
 */
char* strrchr(const char* str, int ch) {
    const char* ps = NULL;
    do {
        if (*str == (char) ch) {
            ps = str;
        }
    } while(*str++);
    return const_cast<char*>(ps);
}

/**
 * return the length of the maximum initial segment of src
 * which contains no characters from rej
 */
int strcspn(const char* src, const char* stopset) {
    int count = 0;
    while (*src != '\0') {
        if (strchr(stopset, *src++) == NULL) {
            ++count;
        } else {
            break;
        }
    }
    return count;
}

char* strdup(const char* src) {
    int len = strlen(src) + 1;
    void* newstr = malloc(len);
    if (newstr == NULL) {
        return NULL;
    }
    return (char*) memcpy(newstr, src, len);
}

char* strndup(const char* src, int num) {
    num = strnlen(src, num); // avoid problems if s1 not nul-terminated
    char* ps = (char*) malloc(num + 1);
    if (ps != NULL) {
        memcpy(ps, src, num);
        ps[num] = 0;
    }
    return ps;
}

/**
 * returns a pointer to the first occurrence in src of any of the characters that
 * are part of accept, or a null pointer if there are no matches.
 */
char* strpbrk(const char* src, const char* accept) {
    const char* ps; // pointer to src
    const char* pa; // pointer to accept
    for (ps = src; *ps; ++ps) {
        for (pa = accept; *pa; ++pa) {
            if (*ps == *pa) {
                return const_cast<char*>(ps);
            }
        }
    }
    return NULL;
}

char* strsep(char** src, const char* delim) {
    char* ps = *src;
    char* pd = NULL; // pointer to delimiter
    if (ps && *ps && (pd = strpbrk(ps, delim)) && *pd) {
        *pd++ = 0;
    }
    *src = pd;
    return ps;
}

/**
 * returns the length of the initial portion of src which consists only
 * of characters that are part of accept.
 */
int strspn(char* src, const char* accept) {
    char* ps = src;
    char* pa = const_cast<char*>(accept);
    while (*pa) { // i.e. *pa != '\0'
        if (*pa++ == *ps) {
            ++ps;
            pa = const_cast<char*>(accept);
        }
    }
    return ps - src;
}

static char* strtok_r(char* src, const char* delim, char** save_ptr) {
    char* token;
    char* p;
    if (((token = src) != NULL) || ((token = *save_ptr) != NULL)) {
        if (*(token += strspn(token, delim))) {
            if ((p = strpbrk(token, delim)) != NULL) {
                *p++ = 0;
            }
        } else {
            p = token = NULL;
        }
        *save_ptr = p;
    }
    return token;
}

char* strtok(char* src, const char* delim) {
    static char* save_ptr;
    return strtok_r(src, delim, &save_ptr);
}

/*
 * return the first occurrence of needle in haystack.
 * return haystack if needle is empty, otherwise null if needle is not found in haystack.
 */
char* strstr(const char* haystack, const char* needle) {
    if (haystack == NULL || needle == NULL) {
        return NULL;
    }
    const char* ph = haystack;
    const char* pn = needle;
    do {
        if (*pn == '\0') {
            break;
        }
        if (*pn == *ph) {
            ++ph, ++pn;
        } else {
            pn = needle;
            if (*ph == '\0') {
                return NULL;
            }
            ph = ++haystack;
        }
    } while (true);
    return const_cast<char*>(haystack);
}




} // end of namespace str


int main() {

    /**
     * this is just a sample test
     * this is far from discretion..
     */

    {
        puts(">>> test str::strcmp and strncmp");
        char str[][5] = { "R2D2", "C3PO", "R2A6" };
        for (int i = 0; i < 3; i++) {
            if (str::strncmp(str[i], "R2xx", 2) == 0) {
                printf("fuzzily found %s\n", str[i]);
            }
            if (str::strcmp(str[i], "R2D2") == 0) {
                printf("preciously located %s\n", str[i]);
            }
        }
        puts("");
    }

    {
        puts(">>> test str::strncat");
        char str1[20], str2[20];
        str::strcpy(str1, "to be ");
        str::strcpy(str2, "or not to be");
        str::strncat(str1, str2, 6);
        puts(str1);
        puts("");
    }

    {
        puts(">>> test str::strpbrk");
        char str[] = "this is a sample string";
        char key[] = "aeiou";
        char * pch;
        printf("vowels in '%s': ", str);
        pch = str::strpbrk(str, key);
        while (pch != NULL) {
            printf("%c ", *pch);
            pch = strpbrk(pch + 1, key);
        }
        puts("\n");
    }

    {
        puts(">>> test str::strchr");
        char str[] = "this is a sample string";
        char * pch;
        printf("looking for the 's' character in \"%s\"...\n", str);
        pch = str::strchr(str, 's');
        while (pch != NULL) {
            printf("found 's' at %ld\n", pch - str + 1);
            pch = strchr(pch + 1, 's');
        }
        puts("");
    }

    {
        puts(">>> test str::strrchr");
        char str[] = "This is a sample string";
        char *pch;
        pch = str::strrchr(str, 's');
        printf("last occurence of 's' found at %ld \n", pch - str + 1);
        puts("");
    }

    {
        puts(">>> test str::strsep");
        char str[] = "this is a sample string";
        char *token, *strpos = str;
        while ((token = str::strsep(&strpos, " ")) != NULL) {
            printf("'%s'\n", token);
        }
        puts("");
    }

    {
        puts(">>> test str::strspn");
        char strtext[] = "129th";
        char cset[] = "1234567890";
        printf("the initial number has %d digits.\n", str::strspn(strtext, cset));
        puts("");
    }


    {
        puts(">>> test str::strcspn");
        const char str[] = "fcba73";
        const char rej[] = "1234567890";
        printf("the first number in str is at position %d.\n", str::strcspn(str, rej));
        puts("");
    }

    {
        puts(">>> test str::strstr");
        const char haystack[] = "12345fcba7367890";
        const char needle[] = "fcba7";
        printf("strstr(%s, %s) is %s.\n", haystack, needle,
                str::strstr(haystack, needle));
        puts("");
    }

    {
        puts(">>> test str::strtok");
        char str[] = "- this, a sample string.";
        char * pch;
        printf("splitting string \"%s\" into tokens:\n", str);
        pch = str::strtok(str, " ,.-");
        while (pch != NULL) {
            printf("%s\n", pch);
            pch = str::strtok(NULL, " ,.-");
        }
        puts("");
    }

    return 0;
}

-------------------------------------------------------------
>>> test str::strcmp and strncmp
fuzzily found R2D2
preciously located R2D2
fuzzily found C3PO
fuzzily found R2A6

>>> test str::strncat
to be or not

>>> test str::strpbrk
vowels in 'this is a sample string': i i a a e i 

>>> test str::strchr
looking for the 's' character in "this is a sample string"...
found at 4
found at 7
found at 11
found at 18

>>> test str::strrchr
last occurence of 's' found at 18 

>>> test str::strsep
'this'
'is'
'a'
'sample'
'string'

>>> test str::strspn
the initial number has 3 digits.

>>> test str::strcspn
the first number in str is at position 4.

>>> test str::strstr
strstr(12345fcba7367890, fcba7) is fcba7367890.

>>> test str::strtok
splitting string "- this, a sample string." into tokens:
this
a
sample
string
```
