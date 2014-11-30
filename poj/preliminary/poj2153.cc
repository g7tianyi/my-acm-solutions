/**
 * http://poj.org/problem?id=2153
 * Rank List
 * HashMap ?..
 */

#include <iostream>
#include <string>
#include <map>

std::map<std::string, int> scores;
std::map<std::string, int>::iterator pos;

int main() {
    std::string name;
    int people;
    scanf("%d\n", &people);
    for (int i = 0; i < people; ++i) {
        getline(std::cin, name);
        scores[name] = 0;
    }

    int course;
    scanf("%d", &course);
    while (course--) {
        int score, rank = 1;
        for (int i = 0; i < people; ++i) {
            scanf("%d ", &score);
            getline(std::cin, name);
            scores[name] += score;
        }

        pos = scores.find("Li Ming");
        score = pos->second;
        for (pos = scores.begin(); pos != scores.end(); ++pos) {
            if (pos->second > score) {
                ++rank;
            }
        }
        printf("%d\n", rank);
    }

    return 0;
}

