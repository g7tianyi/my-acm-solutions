/*
 ID: fairyroad1106
 PROG: friday
 LANG: C++
 */
#include <fstream>
using namespace std;

#define PROGID "friday"
#define INPUT  PROGID".in"
#define OUTPUT PROGID".out"

ifstream fin(INPUT);
ofstream fout(OUTPUT);

enum {
    WEEK = 7, MONTH = 12, FEBRUARY = 1, START_YEAR = 1900
};

int months[MONTH] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int result[WEEK];

// simulation problem. I'm not very into this kind of problems...
int main() {
    int N;
    fin >> N;
    N += START_YEAR;
    int year, month, days = 13;
    for (year = START_YEAR; year < N; ++year) {
        if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
            months[FEBRUARY] = 29;
        } else {
            months[FEBRUARY] = 28;
        }
        for (month = 0; month < MONTH; ++month) {
            ++result[days % WEEK];
            days += months[month];
        }
    }

    // stupid I/O requirement
    fout << result[6] << ' ' << result[0] << ' ';
    for (int i = 1; i < 5; ++i) {
        fout << result[i] << ' ';
    }
    fout << result[5] << endl;

    return 0;
}

