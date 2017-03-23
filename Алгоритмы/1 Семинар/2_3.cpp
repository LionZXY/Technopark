#include <cstdio>
#include <iostream>
#include <assert.h>

/**
 *   ​Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k. Найти количество
 *   таких пар индексов (i, j), что A[i] + B[j] = k. Время работы O(n + m).
 *   n, m ≤ 100000.
 *   Указание. Обходите массив B от конца к началу.
 *
 *   Пример:
 *   4
 *   -5 0 3 18
 *   5
 *   -10 -2 4 7 12
 *   7
 *   Вывод:
 *   3
 **/

int getSumCount(int needSum, size_t sizeOne, size_t sizeTwo, int *&arrayOne, int *&arrayTwo);


int main() {
    //Первый массив
    int sizeOne = -1;
    std::cin >> sizeOne;
    assert(sizeOne != -1);

    int *arrayOne = new int[sizeOne];
    for (int i = 0; i < sizeOne; i++)
        std::cin >> arrayOne[i];

    //Второй массив
    int sizeTwo = -1;
    std::cin >> sizeTwo;
    assert(sizeTwo != -1);

    int *arrayTwo = new int[sizeTwo];
    for (int i = 0; i < sizeTwo; i++)
        std::cin >> arrayTwo[i];


    int k = -1;
    std::cin >> k;
    assert(k != -1);

    int sumCount = getSumCount(k, (size_t) sizeOne, (size_t) sizeTwo, arrayOne, arrayTwo);

    printf("%d", sumCount);
    delete[] arrayOne, arrayTwo;
    return 0;
}

int getSumCount(int needSum, size_t sizeOne, size_t sizeTwo, int *&arrayOne, int *&arrayTwo) {
    int sum = 0, sumCount = 0;
    int iterratorOne = (int) (sizeOne - 1);
    int iterratorTwo = 0;

    do {
        sum = arrayOne[iterratorOne] + arrayTwo[iterratorTwo];
        if (sum > needSum)
            iterratorOne--;
        else if (sum < needSum)
            iterratorTwo++;
        else if (sum == needSum) {
            sumCount++;
            iterratorOne--;
        }
    } while (iterratorOne >= 0 && iterratorTwo < sizeTwo);

    return sumCount;

}