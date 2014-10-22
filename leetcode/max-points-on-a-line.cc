#include <iostream>

#include <cstring>
#include <vector>
using std::vector;

#include <unordered_map>
#include <unordered_set>
#include <algorithm>

struct Point {
    int x;
    int y;
    Point() :
            x(0), y(0) {
    }
    Point(int a, int b) :
            x(a), y(b) {
    }
};

class Solution {
public:
    int maxPoints(vector<Point> &points) {
        std::unordered_map<double, int> lineHash;
        int result = 0, size = points.size();
        for (int i = 0; i < size; ++i) {
            lineHash.clear();
            int duplicateCount = 1;
            for (int j = 0; j < size; ++j) {
                if (j == i) {
                    continue;
                }
                if (points[i].x == points[j].x && points[i].y == points[j].y) {
                    ++duplicateCount;
                    continue;
                }

                double slope;
                if (points[i].x == points[j].x) {
                    slope = std::numeric_limits<double>::max();
                } else {
                    slope = static_cast<double>((points[j].y - points[i].y))
                            / (points[j].x - points[i].x);
                }
                // std::cout << slope << std::endl;
                ++lineHash[slope];
            }
            for (std::unordered_map<double, int>::iterator pos = lineHash.begin();
                    pos != lineHash.end(); ++pos) {
                if (result < pos->second + duplicateCount) {
                    result = pos->second + duplicateCount;
                }
            }
        }
        return result;
    }
};

Solution solu;

int main() {
    vector<Point> points;
    points.push_back(Point(84, 250));
    points.push_back(Point(0, 0));
    points.push_back(Point(1, 0));
    points.push_back(Point(0, -70));
    points.push_back(Point(0, -70));
    points.push_back(Point(1, -1));
    points.push_back(Point(21, 10));
    points.push_back(Point(42, 90));
    points.push_back(Point(-42, -230));

    std::cout << solu.maxPoints(points) << std::endl;

    return 0;
}

