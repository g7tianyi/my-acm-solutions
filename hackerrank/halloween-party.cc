#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int T = 0;
    unsigned long K = 0;
    std::cin >> T;
    while (T--) {
        std::cin >> K;
        if (K & 0x1u) {
            std::cout << (K >> 1) * ((K >> 1) + 1) << std::endl;
        } else {
            std::cout << (K >> 1) * (K >> 1) << std::endl;
        }
    }
    
    return 0;
}

