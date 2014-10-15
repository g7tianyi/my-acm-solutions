#include <iostream>
#include <string>
using std::string;

enum InputType {
    INVALID,    // 0
    SPACE,      // 1
    SIGN,       // 2
    DIGIT,      // 3
    DOT,        // 4
    EXPONENT,   // 5
    NUM_INPUTS  // 6
};

enum {
    STATES = 9
};

/**
 * State 0: Start state.
 *   Can receive space, +/-, number, dot
 *   1) receive space    => 0
 *   2) receive number   => 1
 *   3) receive dot      => 2
 *   4) receive +/-      => 3
 *
 * State 1: Go through space and/or digits.
 *   Can receive number, dot, exponent
 *   1) receive number   => 1
 *   2) receive dot      => 4
 *   3) receive exponent => 5
 *
 * State 2: Go through dot and/or +/-.
 *   Can receive number only
 *   1) receive number   => 4
 *
 * State 3: Go through space and/or +/-.
 *   Can receive space, number, dot
 *   1) receive space    => 0
 *   2) receive number   => 1
 *   3) receive dot      => 2
 *
 * State 4: Go through dot or +/-
 *   Can receive space, number, exponent
 *   1) receive space    => 8
 *   2) receive number   => 4
 *   3) receive exponent => 5
 *
 * State 5: Go through numbers
 *   Can receive sign, number
 *   1) receive +/-      => 6
 *   2) receive number   => 7
 *
 * State 6: Go through dot or +/- and numbers
 *   Can receive numbers only
 *   1) receive number   => 7
 *
 * State 7: Go through dot or +/- and numbers
 *   Can receive space and numbers
 *   1) receive space    => 8
 *   2) receive number   => 7
 *
 * State 8: numbers has been made and ends with space already
 *   Can receive space only
 *   1) receive space    => 8
 */
int stateTransition[STATES][NUM_INPUTS] = {
    { -1,  0,  3,  1,  2, -1 },   // next states for state 0
    { -1,  8, -1,  1,  4,  5 },   // next states for state 1
    { -1, -1, -1,  4, -1, -1 },   // next states for state 2
    { -1, -1, -1,  1,  2, -1 },   // next states for state 3
    { -1,  8, -1,  4, -1,  5 },   // next states for state 4
    { -1, -1,  6,  7, -1, -1 },   // next states for state 5
    { -1, -1, -1,  7, -1, -1 },   // next states for state 6
    { -1,  8, -1,  7, -1, -1 },   // next states for state 7
    { -1,  8, -1, -1, -1, -1 },   // next states for state 8
};

class Solution {
public:
    bool isNumber(const char* s) {
        int state = 0;
        while (*s != '\0') {
            InputType inputType = INVALID;
            if (isspace(*s)) {
                inputType = SPACE;
            } else if (*s == '+' || *s == '-') {
                inputType = SIGN;
            } else if (isdigit(*s)) {
                inputType = DIGIT;
            } else if (*s == '.') {
                inputType = DOT;
            } else if (*s == 'e' || *s == 'E') {
                inputType = EXPONENT;
            }

            state = stateTransition[state][inputType];
            if (state == -1) {
                return false;
            } else {
                ++s;
            }
        }

        return state == 1 || state == 4 || state == 7 || state == 8;
    }
};

Solution solu;

void test(const char* str) {
    bool valid = solu.isNumber(str);
    if (valid) {
        std::cout << str <<  " is a valid number" << std::endl;
    } else {
        std::cout << str << " is not a valid number" << std::endl;
    }
}

int main() {
    string strs[7] = {
        "      ",
        "-12471",
        "81243e17",
        "72845e-13",
        "72845e-13  ",
        "  72845e-13  ",
        "  72845e-13  1",
    };
    for (int i = 0; i < 7; ++i) {
        test(strs[i].c_str());
    }

    return 0;
}

