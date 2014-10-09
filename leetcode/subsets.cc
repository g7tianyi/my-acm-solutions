#include <iostream>

inline int min(int a, int b) {
    return a < b ? a : b;
}
inline int max(int a, int b) {
    return a > b ? a : b;
}

#include <algorithm>
#include <vector>
using std::vector;

struct Worker {
public:
    Worker(vector<int>& _source, vector<vector<int> >& _result) :
            source(_source), result(_result) {
    }
    void run(int curr, vector<int>& V) {
        vector<int> C(V);
        result.push_back(C);

        for (int i = curr; i < source.size(); ++i) {
            V.push_back(source[i]);
            run(i + 1, V);
            V.pop_back();
        }
    }
public:
    vector<int>& source;
    vector<vector<int> >& result;
};

class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        vector<vector<int> > V;
        if (S.empty()) {
            return V;
        }
        std::sort(S.begin(), S.end());
        vector<int> C;
        Worker worker(S, V);
        worker.run(0, C);
        return V;
    }
};
Solution sol;

int main() {
    vector<int> S;
    S.push_back(1), S.push_back(2), S.push_back(3);
    vector<vector<int> > V = sol.subsets(S);
    for (int i = 0; i < V.size(); ++i) {
        std::cout << "subset " << i + 1 << ": ";
        std::copy(V[i].begin(), V[i].end(),
                std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
    return 0;
}

