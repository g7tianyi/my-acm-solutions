#include <unordered_set>
#include <unordered_map>
using std::unordered_set;
using std::unordered_map;

#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::vector;
using std::string;

typedef unordered_set<string> HashSet;
typedef unordered_map<string, int> HashMap;

HashSet visit;
HashMap wordId;
vector<vector<int> > minCost;
const int INF_MAX = std::numeric_limits<int>::max();

#define __LOCAL_DEBUG__

#undef __LOCAL_DEBUG__

#ifdef __LOCAL_DEBUG__
#include <sys/time.h>
long now() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}
#endif

class Solution {
public:
    vector<vector<string> > findLadders(string start, string end,
            HashSet& dict) {
        vector<vector<string> > result;
        if (start == end) {
            vector<string> v;
            v.push_back(start), v.push_back(end);
            result.push_back(v);
            return result;
        }

        // assign id
        wordId.clear(), minCost.clear();
        int index = 0, wordCount = dict.size();
        for (HashSet::iterator pos = dict.begin(); pos != dict.end(); ++pos) {
            wordId[*pos] = index;
            vector<int> v(wordCount, INF_MAX);
            v[index++] = 0;
            minCost.push_back(v);
        }

        // build graph
        string temp;
        int word1, word2;
        HashSet::iterator pos;
        for (pos = dict.begin(); pos != dict.end(); ++pos) {
            temp = *pos;
            word1 = wordId[*pos];
            for (int i = 0; i < pos->size(); ++i) {
                for (int j = 0; j < 26; ++j) {
                    temp[i] = 'a' + j;
                    if (temp != *pos && dict.find(temp) != dict.end()) {
                        word2 = wordId[temp];
                        // undirected weighted graph
                        minCost[word1][word2] = minCost[word2][word1] = 1; 
                    }
                    temp[i] = pos->at(i);
                }
            }
        }

        // find all possible start/end node
        vector<string> adjStart;
        getAdjacencies(start, adjStart, dict);
        vector<string> adjEnd;
        getAdjacencies(end, adjEnd, dict);
        
#ifdef __LOCAL_DEBUG__
        long st = now();
#endif
        for (int i = 0; i < adjStart.size(); ++i) {
            dijkstra(wordId[adjStart[i]], wordCount);
        }
        for (int i = 0; i < adjEnd.size(); ++i) {
            dijkstra(wordId[adjEnd[i]], wordCount);
        }
#ifdef __LOCAL_DEBUG__
        std::cout << "Run Dijkstra cost " << now() - st << " ms\n";
#endif

        // find minPath
        int minPath = INF_MAX;
        for (int i = 0; i < adjStart.size(); ++i) {
            word1 = wordId[adjStart[i]];
            for (int j = 0; j < adjEnd.size(); ++j) {
                word2 = wordId[adjEnd[j]];
                minPath = std::min(minPath, minCost[word1][word2]);
            }
        }

#ifdef __LOCAL_DEBUG__
        st = now();
#endif
        for (int i = 0; i < adjStart.size(); ++i) {
            word1 = wordId[adjStart[i]];
            for (int j = 0; j < adjEnd.size(); ++j) {
                word2 = wordId[adjEnd[j]];
                if (minCost[word1][word2] == minPath) {
                    visit.clear();
                    visit.insert(adjStart[i]);
                    vector<vector<string> > paths = getPaths(adjStart[i],
                            adjEnd[j], minPath);
                    for (int k = 0; k < paths.size(); ++k) {
                        paths[k].insert(paths[k].begin(), start);
                        paths[k].push_back(end);
                        result.push_back(paths[k]);
                    }
                }
            }
        }
#ifdef __LOCAL_DEBUG__
        std::cout << "Run DFS cost " << now() - st << " ms\n";
#endif
        return result;
    }
private:
    void getAdjacencies(string& word, vector<string>& adj, HashSet& dict) {
        string temp = word;
        for (int i = 0; i < word.size(); ++i) {
            for (int j = 0; j < 26; ++j) {
                temp[i] = 'a' + j;
                if (temp != word && dict.find(temp) != dict.end()) {
                    adj.push_back(temp);
                }
                temp[i] = word[i];
            }
        }
    }
    void dijkstra(int start, int size) {
        vector<int> path;
        vector<bool> visit(size, false);
        visit[start] = true;
        int u; // the intermediate node
        for (int i = 1; i < size; ++i) {
            int minPath = INT_MAX, len;
            for (int j = 0; j < size; ++j) {
                if (!visit[j] && minPath > minCost[start][j]) {
                    u = j, minPath = minCost[start][j];
                }
            }
            visit[u] = true;
            for (int k = 0; k < size; ++k) {
                len = minCost[start][u] + minCost[u][k];
                if (!visit[k] && minCost[u][k] != INT_MAX
                        && minCost[start][k] > len) {
                    minCost[start][k] = minCost[k][start] = len;
                }
            }
        }
    }
    vector<vector<string> > getPaths(string& curr, string& dest, int minPath) {
        vector<vector<string> > paths;
        if (curr == dest) {
            vector<string> v;
            v.push_back(curr);
            paths.push_back(v);
            return paths;
        }

        int currId = wordId[curr], destId = wordId[dest], nextId;
        for (int i = 0; i < curr.size(); ++i) {
            for (int j = 0; j < 26; ++j) {
                string temp(curr);
                temp[i] = 'a' + j;
                if (wordId.find(temp) == wordId.end() // not exists
                    || visit.find(temp) != visit.end()) { // already used
                    continue;
                }

                nextId = wordId[temp];
                if (minCost[currId][nextId] + minCost[nextId][destId]
                        != minPath) {
                    continue;
                }

                visit.insert(temp);
                vector<vector<string> > subpaths = getPaths(temp, dest,
                        minPath - minCost[currId][nextId]);
                visit.erase(temp);
                for (int i = 0; i < subpaths.size(); ++i) {
                    subpaths[i].insert(subpaths[i].begin(), curr);
                    paths.push_back(subpaths[i]);
                }
            }
        }
        return paths;
    }
};

