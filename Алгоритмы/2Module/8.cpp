#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <chrono>

using namespace std::chrono;
#define BUFFER_SIZE 256*256*256
unsigned int decimalBuffer[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000,
                                  1000000000}; // Чтобы не высчитывать каждый раз степень десятки
#define BUFFER_START 16

class UpperList {
public:
    int arraySize;

    UpperList();

    ~UpperList();

    unsigned int operator[](size_t index) const;

    void add(unsigned int var);
    int

private:
    unsigned int *buffer;
    int bufferSize;
};

bool inline getVar(unsigned int &out, int &shared, int &iterrator) {
    out = 0;
    iterrator = 0;

    while ((shared = getchar_unlocked()) > ' ') {
        out += decimalBuffer[iterrator++] * (shared - '0');
    }
    return shared != EOF;
}

void inline printVar(int var) {
    for (int i = 9; i >= 0; i--) {
        if (var % decimalBuffer[i] != 0)
            putchar_unlocked(var % decimalBuffer[i] + '0');
    }
    putchar_unlocked(' ');
}

int main() {
    unsigned int x = 0;
    int shared = 0;
    int iterrator = 0;
    int pos = 0;
    int size[256]{0};
    UpperList **buffer = (UpperList **) calloc(BUFFER_SIZE, sizeof(UpperList *));
    std::cout << sizeof(std::vector<unsigned int>);

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (getVar(x, shared, iterrator)) {
        if (0 == buffer[x >> 8]) {
            buffer[x >> 8] = new UpperList();
        }
        buffer[x >> 8]->add(x);
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(t2 - t1).count();
    std::cout << '\n' << duration << '\n';

    pos = 0;
    t1 = high_resolution_clock::now();
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (buffer[i] == 0) {}
        else {
            UpperList *bufferVar = buffer[i];
            size[bufferVar->arraySize]++;
            //printf("%lu\n", bufferVar->size());
            switch (bufferVar->arraySize) {
                case 1: {
                    if (pos < 9)
                        pos++;
                    else {
                        pos = 0;
                        printVar((*bufferVar)[0]);
                    }
                    break;
                }
                case 2: {
                    if (pos < 8)
                        pos += 2;
                    else {
                        pos = 0;
                        printVar((*bufferVar)[0] < (*bufferVar)[1] ? (*bufferVar)[0] : (*bufferVar)[1]);
                    }
                    break;
                }
                default: {
                    std::sort(bufferVar->begin(), bufferVar->end());
                    if (pos + bufferVar->arraySize < 10) {
                        pos += bufferVar->arraySize;
                    } else {
                        pos = 10 - pos - 1;
                        printVar((*bufferVar)[pos]);
                        int j = 0;
                        for (j = pos + 10; j < bufferVar->arraySize); j += 10) {
                            printVar((*bufferVar)[j]);
                        }
                        pos = (int) (bufferVar->arraySize % 10);
                    }
                }
            }
        }
    }


    t2 = high_resolution_clock::now();
    duration = duration_cast<microseconds>(t2 - t1).count();
    std::cout << '\n' << duration << '\n';

    for (int i = 0; i < 256; i++)
        printf("%d %d\n", i, size[i]);
    return 0;
}


unsigned int &UpperList::operator[](size_t index) {
    return buffer[index];
}

unsigned int UpperList::operator[](size_t index) const {
    return buffer[index];
}

UpperList::UpperList() : bufferSize(BUFFER_START), arraySize(0), buffer(NULL) {
    buffer = (unsigned int *) malloc(sizeof(unsigned int) * bufferSize);
}

UpperList::~UpperList() {
    free(buffer);
}

void UpperList::add(unsigned int var) {
    if (bufferSize == arraySize) {
        bufferSize *= 1.5;
        buffer = (unsigned int *) realloc(buffer, (size_t) bufferSize);
    }
    buffer[arraySize++] = var;
}

inline void
sort(_RandomAccessIterator __first, _RandomAccessIterator __last) {

}
