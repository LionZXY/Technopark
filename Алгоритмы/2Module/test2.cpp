#include <chrono>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cassert>

void mergeSort(int *arr, int start, int end);

int main() {
    bool correct = true;
    srand(time(NULL));

    while (correct) {
        int maxSize = abs(rand()) % 10 + 1;
        int maxNumber = 10;
        std::vector<int> vectorCanonical;
        std::vector<int> testSource;

        int tmp;
        for (int i = 0; i < maxSize; i++) {
            tmp = abs(rand()) % maxNumber;
            vectorCanonical.push_back(tmp);
            testSource.push_back(tmp);
        }

        //Sort canonical
        std::sort(vectorCanonical.begin(), vectorCanonical.end());

        std::cout << "Инициализация " << maxSize << '\n';
        mergeSort(testSource.begin().base(), 0, maxSize - 1);

        for (int i = 0; i < maxSize; i++)
            if (testSource[i] != vectorCanonical[i])
                correct = false;

        if (!correct) {
            for (int i = 0; i < maxSize; i++)
                std::cout << testSource[i] << ' ';
        }
    }
    return 0;
};

void merge(int *arr, int firstStart, int firstEnd, int secondStart, int secondEnd) {
    int start = firstStart;
    firstStart -= start;
    firstEnd -= start;
    secondStart -= start;
    secondEnd -= start;
    int size = secondEnd - firstStart + 1;

    int *buffer = new int[size];
    std::copy(arr + start, arr + start + size, buffer);

    for (int i = start; i <= secondEnd; i++) {
        if (secondEnd >= secondStart)
            if (firstEnd >= firstStart) {
                arr[i] = (buffer[firstStart] > buffer[secondStart] ? buffer[secondStart++] : buffer[firstStart++]);
            } else arr[i] = buffer[secondStart++];
        else arr[i] = buffer[firstStart++];
    }

    delete[] buffer;
}


void mergeSort(int *arr, int start, int end) {
    std::cout << "Вход: " << start << ' ' << end << ' ' << '\n';
    if (end - start < 2) {
        if (arr[start] > arr[end])
            std::swap(arr[start], arr[end]);
        return;
    }

    int size = end - start + 1;

    int firstStart = start;
    int firstEnd = start + size / 2;
    int secondStart = firstEnd + 1;
    int secondEnd = end;

    assert(firstEnd >= firstStart);
    assert(secondEnd >= secondStart);
    assert(size > 0);

    std::cout << "Индексы: " << firstStart << ' ' << firstEnd << ". И конец: " << secondStart << ' ' << secondEnd
              << '\n';

    mergeSort(arr, firstStart, firstEnd);
    mergeSort(arr, secondStart, secondEnd);

    merge(arr, firstStart, firstEnd, secondStart, secondEnd);
}