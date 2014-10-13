#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::string;
using std::vector;

struct DFSRunner {
    DFSRunner(vector<int>& _num, vector<vector<int> >& _result) :
            num(_num), result(_result) {
        visit = vector<bool>(_num.size(), false);
    }

    void run(int depth, vector<int>& vec) {
        if (depth == num.size()) {
            result.push_back(vec);
            return;
        }
        for (int i = 0; i < num.size(); ++i) {
            if (!visit[i]) {
                visit[i] = true;
                vec.push_back(num[i]);
                run(depth + 1, vec);
                vec.pop_back();
                visit[i] = false;
            }
        }
    }

    vector<int>& num;
    vector<bool> visit;
    vector<vector<int> >& result;
};

class Solution {
public:
    vector<vector<int> > permute(vector<int> &num) {
        vector<vector<int> > result;
        DFSRunner runner(num, result);
        vector<int> V;
        runner.run(0, V);
        return result;
    }
};

Solution solu;

int main() {
    vector<int> V;
    vector<vector<int> > result;

    V.push_back(1), V.push_back(2), V.push_back(3);
    result = solu.permute(V);
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    return 0;
}

