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

void mergeSort(int *arr, int start, int end);

int main() {
    int n = 0;
    int k = 0;
    std::cin >> n >> k;

    int *array = new int[n];
    for (int i = 0; i < n; i++)
        std::cin >> array[i];

    if (k > n)
        k = n - 1;
    std::sort(array, )


    int kIndex = k - 1;
    for (int i = kIndex; i < n; i += 4) {
    }

    for (int i = 0; i < n; i++)
        std::cout << array[i] << ' ';

    delete[] array;
    return 0;
}

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