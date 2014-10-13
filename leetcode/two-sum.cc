#include <algorithm>
#include <iostream>

#include <string>
using std::string;

#include <vector>
using std::vector;

struct element {
    int value, index;
    element(int _value, int _index) : value(_value), index(_index) {}
};

inline bool elemCompare(const element& elem1, const element& elem2) {
    return elem1.value < elem2.value;
}

class Solution {
public:
    typedef vector<element>::iterator elemIterator;

    vector<int> twoSum(vector<int> &numbers, int target) {
        vector<int> result;
        if (numbers.empty()) {
            return result;
        }

        int size = numbers.size();
        vector<element> elements;
        for (int i = 0; i < size; ++i) {
            elements.push_back(element(numbers[i], i + 1));
        }
        std::sort(elements.begin(), elements.end(), elemCompare);

        elemIterator pos;
        for (int i = 0, val; i < size - 1; ++i) {
            val = target - elements[i].value;
            // no use => "You may assume that each input would have exactly one solution."
            // if (val < elements[i].value) {
            //     break;
            // }
            // the binarySearch's precondition is,
            // both the begin and end iterator are inclusively contained
            pos = binarySearch(elements.begin() + i + 1, elements.end() - 1, val);
            if (pos != elements.end()) {
                if (elements[i].index < pos->index) {
                    result.push_back(elements[i].index), result.push_back(pos->index);
                } else {
                    result.push_back(pos->index), result.push_back(elements[i].index);
                }
                break;
            }
        }

        return result;
    }
private:
    elemIterator binarySearch(elemIterator first, elemIterator last, int value) {
        elemIterator middle, failure = last + 1;
        while (first <= last) {
            middle = first + ((last - first) >> 1);
            if (middle->value == value) {
                return middle;
            } else if (middle->value < value) {
                first = middle + 1;
            } else {
                last = middle - 1;
            }
        }
        return failure;
    }
};

Solution solu;

void print(vector<int>& result, int target) {
    if (result.empty()) {
        std::cout << "No solution." << std::endl;
    } else {
        std::cout << "(" << result[0] << ", " << result[1] << ") => " << target << std::endl;
    }
}

int main() {
    vector<int> result;
    vector<int> numbers;
    numbers.push_back(2), numbers.push_back(15);
    numbers.push_back(11), numbers.push_back(7);

    std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    result = solu.twoSum(numbers, 9);
    print(result, 9);

    std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    result = solu.twoSum(numbers, 26);
    print(result, 26);

    numbers.push_back(3), numbers.push_back(17);
    numbers.push_back(5), numbers.push_back(14);

    std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    result = solu.twoSum(numbers, 8);
    print(result, 8);

    std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    result = solu.twoSum(numbers, 23);
    print(result, 23);

    return 0;
}

