#include <stdio.h>
#include <algorithm>
#include <cstring>

int tmpChar[16] = {0};

bool inline getVar(unsigned int &out) {
    unsigned int x = 0;
    int shared = 0;

    while ((shared = getchar_unlocked()) > ' ') {
        x *= 10;
        x += shared - '0';
    }
    out = x;
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

int inline getByte(unsigned int var, int number) {
    return (int) ((var >> (number * 8)) & 255);
}

void radixSort(unsigned int *array, size_t n) {
    int *keyArray = (int *) malloc(256 * sizeof(int));
    unsigned int *tmpArray = (unsigned int *) malloc(n * sizeof(unsigned int));
    int tmp;
    int lastVar;
    for (int byteNumber = 0; byteNumber < 4; byteNumber++) {
        memset(keyArray, 0, 256 * sizeof(int));

        for (int i = 0; i < n; i++)
            keyArray[getByte(array[i], byteNumber)]++;

        lastVar = 0;
        for (int i = 0; i < 256; i++) {
            tmp = keyArray[i];
            keyArray[i] = lastVar;
            lastVar += tmp;
        }

        for (int i = 0; i < n; i++) {
            tmp = getByte(array[i], byteNumber);
            tmpArray[keyArray[tmp]] = array[i];
            keyArray[tmp]++;
        }

        memmove(array, tmpArray, n * sizeof(unsigned int));
    }
    free(tmpArray);
    free(keyArray);
}

int main() {
    int pos = 0;
    unsigned int *buffer = (unsigned int *) malloc(25000000 * sizeof(unsigned int));

    while (getVar(buffer[pos++]));
    radixSort(buffer, (size_t) pos);

    
    for (int i = 10; i < pos; i += 10)
        printVar(buffer[i]);

    free(buffer);
    return 0;
}