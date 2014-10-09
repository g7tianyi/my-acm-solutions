#include <vector>
#include <map>
using std::vector;
using std::map;

class Solution {
public:
    int longestConsecutive(vector<int>& array) {
        map<int, int> hash;
        hash.clear();
        int n = array.size();
        for (int i = 0; i < n; i++) {
            hash.insert(std::pair<int, int>(array[i], i));
        }
        int result = 0, count = 0;
        map<int, int>::iterator pos;
        for (int i = 0; i < array.size(); i++) {
            int curr = array[i];
            pos = hash.find(array[i]);
            count++;
            if (pos != hash.end()) {
                map<int, int>::iterator iter;
                while (true) {
                    iter = hash.find(++curr);
                    if (iter == hash.end()) {
                        break;
                    }
                    count++;
                    hash.erase(iter);
                }
                curr = array[i];
                while (true) {
                    iter = hash.find(--curr);
                    if (iter == hash.end()) {
                        break;
                    }
                    count++;
                    hash.erase(iter);
                }
                if (result < count) {
                    result = count;
                }
                count = 0;
            }
            count = 0;
        }
        return result;
    }
};


