#include <cstdio>
#include <iostream>
#include <assert.h>
#include "stdlib.h"

/**
 * ​Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для
 * каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по
 * значению к B[i]. Время работы поиска для каждого элемента B[i]: O(log(k)).
 * n ≤ 110000, m ≤ 1000.
 *
 * Пример:
 * 3
 * 10 20 30
 * 3
 * 9 15 35
 * Вывод:
 * 0 0 2
 *
 * Пример 2:
 * 3
 * 10 20 30
 * 4
 * 8 9 10 32
 * Вывод:
 * 0 0 0 2
 * */

int binarySearch(int n, size_t size, int *&sortedArray);

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

    int resultBinSearch = -1;
    for (int i = 0; i < sizeTwo; i++) {
        resultBinSearch = binarySearch(arrayTwo[i], (size_t) sizeOne, arrayOne);
        assert(resultBinSearch >= 0 && resultBinSearch < sizeOne);

        printf("%d ", resultBinSearch);
    }

    delete[] arrayOne, arrayTwo;
    return 0;
}

/**
 * Ищет ближайшее значение в отсортированном массиве
 *
 * @param n             Искомое число
 * @param size          Размер массива
 * @param sortedArray   Отсортированный массив по возрастанию
 * @return indexNearest Индекс ближайшего числа в массиве к числу n
 */
int binarySearch(int n, size_t size, int *&sortedArray) {
    int start = 0, end = 0, curPos = 1;

    // Бежим степенью двойки до ближайшего значения, больше искомого
    while (curPos < size && sortedArray[curPos] <= n)
        curPos *= 2;;
    if (curPos > size)
        curPos = (int) size - 1;

    if (curPos == 1)
        start = 0;
    else start = curPos / 2;
    end = curPos;

    // Стандартный бинарный поиск
    do {
        curPos = (end - start) / 2;
        if (sortedArray[start + curPos] <= n)
            start = start + curPos;
        else end = start + curPos;
    } while (end - start > 1);

    if (end == size)
        return end - 1;
    else if (abs(sortedArray[start] - n) > abs(sortedArray[end] - n))
        return end;
    else return start;
}