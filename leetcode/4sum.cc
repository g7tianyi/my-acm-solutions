//#include <algorithm>

#include <iostream>

//#include <string>
//using std::string;

#include <unordered_map>
#include <vector>
using std::unordered_map;
using std::vector;
using std::pair;

class Solution {
public:
    vector<vector<int> > fourSum(vector<int> &number, int target) {
        int size = number.size();
        vector<vector<int> > result;
        unordered_map<int, vector<pair<int, int> > > pairs;
        pairs.reserve(size * size);
        sort(number.begin(), number.end());

        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                pairs[number[i] + number[j]].push_back(std::make_pair(i, j));
            }
        }

        unordered_map<int, vector<pair<int, int> > >::iterator pos, last;
        for (int i = 0; i < size - 3; i++) {
            if (i > 0 && number[i] == number[i - 1]) {
                continue;
            }
            for (int j = i + 1; j < size - 2; j++) {
                if (j > i + 1 && number[j] == number[j - 1]) {
                    continue;
                }
                pos = pairs.find(target - number[i] - number[j]);
                if (pos != pairs.end()) {
                    vector<pair<int, int> >& halfsum = pos->second;
                    for (int k = 0; k < halfsum.size(); ++k) {
                        if (halfsum[k].first <= j) {
                            continue;
                        }
                        if (result.empty() ||
                                !((result.back())[0] == number[i]
                                        && (result.back())[1] == number[j]
                                        && (result.back())[2] == number[halfsum[k].first]
                                        && (result.back())[3] == number[halfsum[k].second])) {
                            vector<int> C;
                            C.push_back(number[i]), C.push_back(number[j]);
                            C.push_back(number[halfsum[k].first]);
                            C.push_back(number[halfsum[k].second]);
                            result.push_back(C);
                        }
                    }
                }
            }
        }
        return result;
    }
};

Solution solu;

vector<int> option;
vector<vector<int> > result;

int main() {
    option.push_back(1), option.push_back(0), option.push_back(-1);
    option.push_back(0), option.push_back(2), option.push_back(-2);

    result = solu.fourSum(option, 0);
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    option.clear();
    option.push_back(0);
    result = solu.fourSum(option, 0);
    std::cout << "--------" << std::endl;
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    option.clear();
    option.push_back(-3), option.push_back(-2), option.push_back(-1);
    option.push_back(0), option.push_back(0), option.push_back(1);
    option.push_back(3), option.push_back(2);
    result = solu.fourSum(option, 0);
    std::cout << "--------" << std::endl;
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    return 0;
}

