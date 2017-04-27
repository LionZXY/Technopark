#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <cstring>

using namespace std::chrono;
#define BUFFER_SIZE 256*256*256
unsigned int decimalBuffer[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000,
                                  1000000000}; // Чтобы не высчитывать каждый раз степень десятки

int tmpChar[16] = {0};

bool inline getVar(unsigned int &out, int &shared, int &iterrator) {
    int pos = 0;
    out = 0;
    iterrator = 0;

    while ((shared = getchar_unlocked()) > ' ') {
        tmpChar[pos++] = shared;
    }
    while (pos != 0)
        out += decimalBuffer[iterrator++] * (tmpChar[--pos] - '0');
    //std::cout << out << ' ';
    return shared != EOF;
}


void inline printVar(int var) {
    int pos = 0;
    while (var != 0) {
        tmpChar[pos++] = var % 10 + '0';
        var /= 10;
    }
    while (pos != 0)
        putchar_unlocked(tmpChar[--pos]);
    putchar_unlocked(' ');
}


int getByte(long long var, int number) {
    return (int) ((var >> (number * 8)) & 255);
}

void radixSort(unsigned int *array, size_t n) {
    int *keyArray = (int *) malloc(256 * sizeof(int));
    unsigned int *tmpArray = (unsigned int *) malloc(n * sizeof(unsigned int));
    for (int byteNumber = 0; byteNumber < 4; byteNumber++) {
        memset(keyArray, 0, 256 * sizeof(int));

        for (int i = 0; i < n; i++)
            keyArray[getByte(array[i], byteNumber)]++;

        int lastVar = 0;
        for (int i = 0; i < 256; i++) {
            int tmp = keyArray[i];
            keyArray[i] = lastVar;
            lastVar += tmp;
        }

        for (int i = 0; i < n; i++) {
            int byte = getByte(array[i], byteNumber);
            tmpArray[keyArray[byte]] = array[i];
            keyArray[byte]++;
        }

        memmove(array, tmpArray, n * sizeof(unsigned int));
    }
    free(tmpArray);
    free(keyArray);
}

int main() {
    int shared = 0;
    int iterrator = 0;
    int pos = 0;
    unsigned int *buffer = (unsigned int *) malloc(25000000 * sizeof(unsigned int));

    while (getVar(buffer[pos++], shared, iterrator));
    radixSort(buffer, (size_t) pos);

    for (int i = 10; i < pos; i += 10)
        printVar(buffer[i]);

    free(buffer);
    return 0;
}