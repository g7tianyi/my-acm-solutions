#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::vector;
using std::string;

#include <unordered_set>
#include <unordered_map>
using std::unordered_set;
using std::unordered_map;

typedef unordered_set<string> dictionary;

unordered_set<string> visit;

class Solution {
public:
    vector<vector<string> > findLadders(string start, string end, dictionary& dict) {
        minPath = std::numeric_limits<int>::max();
        vector<vector<string> > result;
        visit.clear();
        visit.insert(start);
        result = findLadders(0, start, end, visit, dict);
        for (vector<vector<string> >::iterator pos = result.begin();
                pos != result.end(); ) {
            if (pos->size() > minPath) {
                pos = result.erase(pos);
            } else {
                ++pos;
            }
        }
        return result;
    }
private:
    int minPath;

    vector<vector<string> > findLadders(int depth, string& curr, string& end, dictionary& visit,
            dictionary& dict) {
        vector<vector<string> > result;
        if (depth > minPath) {
            return result;
        }

        string temp(curr);
        for (int i = 0; i < curr.size(); ++i) {
            for (int j = 0; j < 26; ++j) {
                temp[i] = 'a' + j;
                if (temp == end) {
                    minPath = depth + 2;
                    vector<string> v;
                    v.push_back(curr);
                    v.push_back(end);
                    result.push_back(v);
                    return result;
                }

                if (dict.find(temp) == dict.end()  // invalid word
                        || visit.find(temp) != visit.end()) { // already used
                    temp[i] = curr[i];
                    continue;
                }

                visit.insert(temp);
                vector<vector<string> > v = findLadders(depth + 1, temp, end, visit, dict);
                visit.erase(temp);

                if (!v.empty()) {
                    for (int i = 0; i < v.size(); ++i) {
                        if (depth + v[i].size() > minPath) {
                            continue;
                        }
                        v[i].insert(v[i].begin(), curr);
                        result.push_back(v[i]);
                    }
                }

                temp[i] = curr[i];
            }
        }

        return result;
    }
};

Solution solu;

int main() {
    vector<vector<string> > result;
    unordered_set<string> dict;
    dict.insert("hot"), dict.insert("dot"), dict.insert("dog");
    dict.insert("lot"), dict.insert("log");

    result = solu.findLadders("hit", "cog", dict);
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(),
                std::ostream_iterator<string>(std::cout, " "));
        std::cout << std::endl;
    }
    std::cout << std::endl;

    dict.clear();
    result = solu.findLadders("hit", "cog", dict);
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(),
                std::ostream_iterator<string>(std::cout, " "));
        std::cout << std::endl;
    }
    std::cout << std::endl;

    result = solu.findLadders("hit", "hit", dict);
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(),
                std::ostream_iterator<string>(std::cout, " "));
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return 0;
}

