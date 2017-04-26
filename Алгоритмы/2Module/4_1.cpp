/**
 * Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n. Требуется
 * найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом
 * k (0..n-1) в отсортированном массиве. Напишите нерекурсивный алгоритм.
 * Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).
 * Функцию Partition следует реализовывать методом прохода двумя итераторами в одном
 * направлении. Описание для случая прохода от начала массива к концу:
 *      ● Выбирается опорный элемент. Опорный элемент меняется с последним элементом
 *      массива.
 *      ● Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
 *      Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат
 *      нерассмотренные элементы. Последним элементом лежит опорный.
 *      ● Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
 *      ● Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
 *      ● Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше
 *      опорного, то сдвигаем j.
 *      Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
 *      ● В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
 *
 * 4_1. ​Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition
 * реализуйте методом прохода двумя итераторами от начала массива к концу.
 *
 * Пример 1:
 * 10 4
 * 1 2 3 4 5 6 7 8 9 10
 * Вывод:
 * 5
 *
 * Пример 2:
 * 10 0
 * 3 6 5 7 2 9 8 10 4 1
 * Вывод:
 * 1
 *
 * Пример 3:
 * 10 9
 * 0 0 0 0 0 0 0 0 0 1
 * Вывод:
 * 1
 */

#include <iostream>
#include <cassert>

int median(int x, int y, int z);

int findNumber(int *array, size_t size, int index);

int main() {
    size_t n = 0;
    int k = 0;
    std::cin >> n >> k;

    int *array = new int[n];
    for (int i = 0; i < n; i++)
        std::cin >> array[i];

    int index = findNumber(array, n, k);
    std::cout << index;

    delete[] array;
    return 0;
}


void partition(int *arr, int start, int end, int median, int &i) {
    i = start; // i - индекс последнего элемента, не большего медианы
    int j = start + 1;

    for (i = start; i <= end && arr[i] != median; i++);
    std::swap(arr[i], arr[end]);
    for (i = start; i <= end && arr[i] <= median; i++);
    std::swap(arr[i], arr[start]);

    for (i = start, j = start + 1; j < end;) {
        if (arr[j] > median)
            j++;
        else
            std::swap(arr[j++], arr[i++]);
    }
    std::swap(arr[i], arr[end]);
}

int getMedianArray(int *arr, int start, int end) {
    int *oldArr = arr;
    int *newArr = NULL;
    int tmpSize = 0;
    do {
        tmpSize = end - start;
        int newSize = tmpSize / 3 + (tmpSize % 3 == 0 ? 0 : 1);
        newArr = new int[newSize];

        for (int i = start + 3, j = 0; i <= end; i += 3, j++)
            newArr[j] = median(oldArr[i], oldArr[i - 1], oldArr[i - 2]);

        if (tmpSize % 3 == 2)
            newArr[newSize - 1] = std::min(oldArr[end - 1], oldArr[end - 2]);
        else if (tmpSize % 3 == 1)
            newArr[newSize - 1] = oldArr[end - 1];

        if (oldArr != arr)
            delete[] oldArr;

        oldArr = newArr;
        start = 0;
        end = newSize - 1;
        tmpSize = newSize;
    } while (tmpSize > 3);

    int result = 0;
    switch (tmpSize) {
        case 3:
            result = median(oldArr[0], oldArr[1], oldArr[2]);
            break;
        case 2:
            result = std::min(oldArr[0], oldArr[1]);
            break;
        case 1:
            result = oldArr[0];
            break;
        default:
            assert(false);
    }

    if (oldArr != arr)
        delete[] oldArr;

    return result;
}

int findNumber(int *array, size_t size, int index) {
    int median = 0;
    int i = 0;
    int start = 0;
    int end = (int) (size - 1);

    while (end - start > 1) {
        median = getMedianArray(array, start, end);
        partition(array, start, end, median, i);

        if (index == i)
            return median;

        if (index > i) {
            start = ++i;
        } else end = i;
    }
    if(array[start] > array[end])
        std::swap(array[start],array[end]);

    assert(index == start || index == end);

    return array[index];
}

int median(int x, int y, int z) {
    if (x > y) std::swap(x, y);
    if (y > z) std::swap(y, z);

    return y;
}