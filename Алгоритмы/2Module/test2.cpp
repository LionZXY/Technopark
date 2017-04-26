#include <chrono>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <iostream>

int main() {
    bool correct = true;
    srand(time(NULL));

    while (correct) {
        int maxSize = abs(rand()) % 300;
        int maxNumber = 300;
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

        //Init Heap sort
        CBinaryHeap<int, bool(const int &, const int &)> heap(testSource, isLess);

        //Heap dynamic sort
        CBinaryHeap<int, bool(const int &, const int &)> heap2(isLess);
        for (int i = 0; i < maxSize; i++)
            heap2.Add(testSource[i]);


        for (int i = maxSize - 1; i >= 0; i--)
            if (heap.ExtractMax() != vectorCanonical[i] || heap2.ExtractMax() != vectorCanonical[i])
                correct = false;


        if (!correct) {
            for (int i = 0; i < maxSize; i++)
                std::cout << testSource[i] << ' ';
        }
    }
    return 0;
};