/**
 * 5_2. Сортировка почти упорядоченной последовательности.
 * Дана последовательность целых чисел a1...an и натуральное число k, такое что для любых i, j:
 * если j >= i + k, то a[i] <= a[j]. Требуется отсортировать последовательность. Последовательность
 * может быть очень длинной. Время работы O(n * log(k)). Память O(k). Использовать слияние.
 *
 * Пример 1:
 * 10 4
 * 0 4 3 2 1 8 7 6 5 9
 * Вывод:
 * 0 1 2 3 4 5 6 7 8 9
 */
#include <iostream>
#include <cstring>
#include <cassert>

void mergeSort(int *arr, int start, int end);

void sort(int *array, int n, int k);

int main() {
    int n = 0;
    int k = 0;
    std::cin >> n >> k;

    int *array = new int[n];
    for (int i = 0; i < n; i++)
        std::cin >> array[i];

    sort(array, n, k);

    for (int i = 0; i < n; i++)
        std::cout << array[i] << ' ';

    delete[] array;
    return 0;
}

void merge(int *arr, int firstStart, int firstEnd, int secondStart, int secondEnd) {
    int start = firstStart;
    int end = secondEnd;
    firstStart -= start;
    firstEnd -= start;
    secondStart -= start;
    secondEnd -= start;
    int size = secondEnd - firstStart + 1;

    int *buffer = new int[size];
    std::copy(arr + start, arr + start + size, buffer);

    for (int i = start; i <= end; i++) {
        if (secondEnd >= secondStart)
            if (firstEnd >= firstStart) {
                arr[i] = (buffer[firstStart] > buffer[secondStart] ? buffer[secondStart++] : buffer[firstStart++]);
            } else arr[i] = buffer[secondStart++];
        else arr[i] = buffer[firstStart++];
    }

    assert(secondStart > secondEnd);
    assert(firstStart > firstEnd);

    delete[] buffer;
}

void mergeSort(int *arr, int start, int end) {
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

    mergeSort(arr, firstStart, firstEnd);
    mergeSort(arr, secondStart, secondEnd);

    merge(arr, firstStart, firstEnd, secondStart, secondEnd);
}

void sort(int *array, int n, int k) {
    mergeSort(array, 0, k - 1);
    int i = 0;
    for (i = k * 2; i < n; i += k) {
        mergeSort(array, i - k, i);
        merge(array, i - (k * 2), i - k - 1, i - k, i);
    }
    i -= k;
    if (i < n) {
        mergeSort(array, i, n - 1);
        merge(array, i - k, i - 1, i, n - 1);
    }
}