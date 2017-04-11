#include <iostream>
#include <string.h>
#include <algorithm>

/**
 * Сортировка вставками
 */
template<typename T>
void insertionSort(T *array, size_t arraySize, int (*compare)(T *firstVar, T *twoVar));

struct Point {
    int x;
    int y;

    Point() : x(0), y(0) {};
};

/**
 * Во всех вариантах данной задачи необходимо реализовать и использовать сортировку
 * вставками​. Функция сравнения или оператор сравнения или функтор должен быть явно
 * определен и передаваться в функцию сортировки.
 *
 * 1_2. Ломаная 1.
 *
 * Задано N точек на плоскости. Указать (N-1)-звенную несамопересекающуюся незамкнутую
 * ломаную, проходящую через все эти точки.
 * Указание: стройте ломаную в порядке возрастания x-координаты. Если имеются две точки с
 * одинаковой x-координатой, то расположите раньше ту точку, у которой y-координата меньше.
 *
 * Пример:
 * 4
 * 0 0
 * 1 1
 * 1 0
 * 0 1
 * Вывод:
 * 0 0
 * 0 1
 * 1 0
 * 1 1
**/

int main() {
    size_t n = 0;
    std::cin >> n;
    Point *pointArray = new Point[n];

    for (int i = 0; i < n; i++) {
        std::cin >> pointArray[i].x >> pointArray[i].y;
    }

    insertionSort<Point>(pointArray, n, [](Point *first, Point *two) {
        return (first->x == two->x ? first->y - two->y : first->x - two->x);
    });

    for (int i = 0; i < n; i++) {
        std::cout << pointArray[i].x << ' ' << pointArray[i].y << '\n';
    }

    delete[] pointArray;
    return 0;
}

/**
 * Ищет ближайшее значение в отсортированном массиве
 * Модифицированная версия. Указывает последний индекс.
 *
 * @param n             Искомое число
 * @param size          Размер массива
 * @param sortedArray   Отсортированный массив по возрастанию
 * @return indexNearest Индекс ближайшего числа в массиве к числу n
 */
template<typename T>
int binarySearch(T *&sortedArray, size_t size, T n, int (*compare)(T *firstVar, T *twoVar)) {
    int start = 0, end = (int) (size - 1), curPos = 1;
    // Стандартный бинарный поиск
    do {
        curPos = start + (end - start) / 2;
        if (compare(&n, &sortedArray[curPos]) < 0)
            end = curPos;
        else start = curPos;
    } while (end - start > 1);

    int returnPos = end == size ? end - 1 : (compare(&n, &sortedArray[end]) >= 0 ? end : start);

    return returnPos;
}

/**
 * Обертка для binarySearch
 *
 * @param n             Искомое число
 * @param start         Позиция индекса, с которого мы будем стартовать
 * @param end           Позиция индекса, которым будет ограничиваться массив
 * @param sortedArray   Отсортированный массив по возрастанию
 * @return indexNearest Индекс ближайшего числа в массиве к числу n
 */
template<typename T>
int binarySearch(T *&sortedArray, int start, int end, T n, int (*compare)(T *firstVar, T *twoVar)) {
    sortedArray += start;
    return binarySearch<T>(sortedArray, (size_t) (end - start + 1), n, compare);
}

/**
 * Сортировка вставками
 */
template<typename T>
void insertionSort(T *array, size_t arraySize, int (*compare)(T *firstVar, T *twoVar)) {
    T tmp;
    if (arraySize > 1 && compare(&array[0], &array[1]) > 0) {
        tmp = array[0];
        array[0] = array[1];
        array[1] = tmp;
    }

    for (int i = 2; i < arraySize; ++i) {
        tmp = array[i];
        int pos = binarySearch(array, 0, i - 1, array[i], compare);
        pos = compare(&array[pos], &tmp) > 0 ? pos : pos + 1;
        memmove(&array[pos + 1], &array[pos], (size_t) sizeof(T) * (i - pos));
        array[pos] = tmp;

    }
}