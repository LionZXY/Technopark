#include <stdio.h>
#include <algorithm>
#include <iostream>

unsigned int decimalBuffer[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000,
                                  1000000000}; // Чтобы не высчитывать каждый раз степень десятки

bool inline getVar(int &out, int &shared, int &iterrator) {
    out = 0;
    iterrator = 0;

    while ((shared = getchar_unlocked()) > ' ') {
        out += decimalBuffer[iterrator++] * (shared - '0');
    }
    return shared != EOF;
}

int main() {
    int x = 0;
    int max = -1;

    while (x != EOF) {
        std::cin >> x;
        max = std::max(x, max);
    }
    return 0;
}
