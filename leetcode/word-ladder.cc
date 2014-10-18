#include <iostream>
#include <string>
using std::string;

#include <deque>
#include <unordered_set>
using std::unordered_set;

/**
 * BFS version, and I think we can solve it by graph algorithm => bipartite-matching
 */
class Solution {
public:
    int ladderLength(string start, string end, unordered_set<string> &dict) {
        if (start == end) {
            return 0;
        }

        string tag = start + "@";
        int result = 1;

        unordered_set<string> visit;
        std::deque<string> queue;

        visit.insert(start);
        queue.push_back(start), queue.push_back(tag);

        while (!queue.empty()) {
            string curr = queue.front();
            queue.pop_front();
            if (curr == tag) {
                if (!queue.empty()) {
                    queue.push_back(tag);
                }
                ++result;
            } else {
                string temp(curr);
                for (int i = 0; i < curr.size(); ++i) {
                    for (int j = 0; j < 26; ++j) {
                        temp[i] = 'a' + j;
                        if (temp == end) {
                            return result + 1;
                        }
                        if (dict.find(temp) != dict.end()
                                && visit.find(temp) == visit.end()) {
                            visit.insert(temp);
                            queue.push_back(temp);
                        }
                        temp[i] = curr[i];
                    }
                }
            }
        }
        return 0; // Return 0 if there is no such transformation sequence
    }
};

Solution solu;

int main() {
    unordered_set<string> dict;
    dict.insert("hot"), dict.insert("dot"), dict.insert("dog");
    dict.insert("lot"), dict.insert("log");
    std::cout << solu.ladderLength("hit", "cog", dict) << std::endl;
    std::cout << solu.ladderLength("hit", "coh", dict) << std::endl;
    return 0;
}

