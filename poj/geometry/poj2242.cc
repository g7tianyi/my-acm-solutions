/**
 * http://poj.org/problem?id=2242
 */

#include <iostream>
#include <limits>
#include <cmath>

const double INF = std::numeric_limits<double>::max();
const double PI  = 3.141592653589793;

struct point {
    double x, y;
};

struct line {
    double slope, intercept;
};

inline line midperpendicular(const point& p1, const point& p2) {
    double slope = 0;
    if (p1.x != p2.x) {
        if (p1.y != p2.y) {
            slope = -1.0 / ((p1.y - p2.y) / (p1.x - p2.x));
        } else {
            slope = INF;
        }
    }

    point pt;
    pt.x = (p1.x + p2.x) / 2;
    pt.y = (p1.y + p2.y) / 2;

    double intercept;
    if (slope == INF) {
        intercept = pt.x;
    } else {
        intercept = pt.y - slope * pt.x;
    }

    line line;
    line.slope = slope;
    line.intercept = intercept;

    return line;
}

inline point intersection(const line& line1, const line& line2) {
    point pt;
    if (line1.slope == INF) {
        pt.x = line1.intercept;
        pt.y = line2.slope * pt.x + line2.intercept;
    } else if(line2.slope == INF) {
        pt.x = line2.intercept;
        pt.y = line1.slope * pt.x + line1.intercept;
    } else {
        pt.x = (line1.intercept - line2.intercept) / (line2.slope - line1.slope);
        pt.y = line1.slope * pt.x + line1.intercept;
    }
    return pt;
}

inline double distance(const point& p1, const point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int main() {
    point p1, p2, p3;
    while (scanf("%lf %lf %lf %lf %lf %lf",
            &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y) != EOF) {
        line   line1  = midperpendicular(p1, p2);
        line   line2  = midperpendicular(p1, p3);
        point  center = intersection(line1, line2);
        double radius = distance(center, p1);
        printf("%.2f\n", 2 * PI * radius);
    }
    return 0;
}

