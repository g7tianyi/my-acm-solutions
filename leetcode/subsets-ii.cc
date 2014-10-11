#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

struct Element {
    int value, count;
    Element(int _v, int _c) :
            value(_v), count(_c) {
    }
};

struct Worker {
    Worker(vector<Element>& _source, vector<vector<int> >& _result) :
            source(_source), result(_result) {
    }

    void run(int curr, vector<int>& V) {
        vector<int> C(V);
        result.push_back(C);

        for (int i = curr; i < source.size(); ++i) {
            for (int j = 0; j < source[i].count; ++j) {
                V.push_back(source[i].value);
                run(i + 1, V);
            }
            for (int j = 0; j < source[i].count; ++j) {
                V.pop_back();
            }
        }
    }

    vector<Element>& source;
    vector<vector<int> >& result;
};

class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        vector<vector<int> > V;
        vector<int> C;
        if (S.empty()) {
            V.push_back(C);
            return V;
        }

        std::sort(S.begin(), S.end());
        vector<Element> elements;
        size_t size = S.size();
        int prev = S[0], count = 1;
        for (size_t i = 1; i < size; ++i) {
            if (S[i] == prev) {
                ++count;
            } else {
                elements.push_back(Element(prev, count));
                prev = S[i];
                count = 1;
            }
        }
        elements.push_back(Element(prev, count));

        Worker worker(elements, V);
        worker.run(0, C);
        return V;
    }
};
Solution sol;

int main() {

    vector<int> S;
    S.push_back(2);
    S.push_back(1);
    S.push_back(2);

    vector<vector<int> > V = sol.subsetsWithDup(S);

    size_t size = V.size();
    for (size_t i = 0; i < size; ++i) {
        std::copy(V[i].begin(), V[i].end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    return 0;
}

