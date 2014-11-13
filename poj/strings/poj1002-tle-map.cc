/**
 * POJ 1002, 487-3279
 * 1) hash
 * 2) trie
 * 3) map  => TLE, >_<
 */
#include <iostream>
#include <string>
#include <map>
using namespace std;

enum {
    UPPER = 100,
    LOWER = 1000
};

const int NUM_ALPH = 26;
const int TABLE[NUM_ALPH] = {
    2, 2, 2,      // A B C
    3, 3, 3,      // D E F
    4, 4, 4,      // G H I
    5, 5, 5,      // J K L
    6, 6, 6,      // M N O
    7, 7, 7, 7,   // P Q R S
    8, 8, 8,      // T U V
    9, 9, 9, 9    // W X Y Z
};

int num;
string pattern;
map<int, int> tel_num_count;
map<int, int>::iterator pos;

inline void print(int num, int boundary) {
    while (num < boundary) {
        cout << 0;
        boundary /= 10;
    }
    if (num) cout << num;
}

int main() {
    cin >> num;
    tel_num_count.clear();
    for (int i = 0; i < num; ++i) {
        cin >> pattern;
        const char* buffer = pattern.c_str();
        int j = 0;
        int hash = 0;
        while (buffer[j]) {
            if (buffer[j] != '-') {
                if (buffer[j] - 'A' >= 0 && buffer[j] - 'A' < 26) {
                    hash = hash * 10 +  (TABLE[buffer[j] - 'A']);
                } else {
                    hash = hash * 10 +  (buffer[j] - '0');
                }
            }
            ++j;
        }
        ++tel_num_count[hash];
    }

    bool has_duplicates = false;
    for (pos = tel_num_count.begin(); pos != tel_num_count.end(); ++pos) {
        if (pos->second > 1) {
            has_duplicates = true;
            int hash_num = pos->first;
            print(hash_num / 10000, UPPER);
            cout << '-';
            print(hash_num % 10000, LOWER);
            cout << ' ' << pos->second << '\n';
        }
    }
    if (!has_duplicates) {
        cout << "No duplicates.\n";
    }

    return 0;
}

