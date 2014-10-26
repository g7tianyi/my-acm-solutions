/**
 * HDU 1004, Let the Balloon Rise
 */
#include <iostream>
#include <string>
#include <map>
using std::string;
using std::map;
map<string, int> records;

int main() {
    int N;
    while (std::cin >> N && N) {
        records.clear();
        string str;
        for (int i = 0; i < N; ++i) {
            std::cin >> str;
            ++records[str];
        }
        int max = -1;
        for (map<string, int>::iterator pos = records.begin();
                pos != records.end(); ++pos) {
            if (max < pos->second) {
                max = pos->second;
                str = pos->first;
            }
        }
        std::cout << str << std::endl;
    }
    return 0;
}

