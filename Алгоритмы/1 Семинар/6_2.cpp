#include <memory.h>
#include <cstdlib>
#include <cassert>
#include <iostream>

/**
 * Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков
 * пирамиду.
 * Формат входных данных:
 * На вход подается количество кубиков N.
 * Формат выходных данных:
 * Вывести число различных пирамид из N кубиков.
 *
 * 6_2. Широкая пирамида.​ Каждый вышележащий слой пирамиды должен быть строго меньше
 * нижележащего. N ​ ≤ 300.
 *
 *
 * Пример 1:
 * 3
 * Вывод:
 * 2
 *
 * Пример 2:
 * 5
 * Вывод:
 * 3
 *
 * Пример 3:
 * 7
 * Вывод:
 * 5
**/

class TriangleTableRow {
public:
    TriangleTableRow(size_t size);

    /**
     * Not use for create
     *
     * @hideinitializer
     * **/
    TriangleTableRow();

    ~TriangleTableRow();

    TriangleTableRow(const TriangleTableRow &) = delete;

    unsigned long operator[](size_t index) const;

    unsigned long &operator[](size_t index);

    size_t getSize() const;

private:
    size_t size;
    unsigned long *data;
};

/**
 * По факту этот класс - это просто двумерный квадратный массив, у которого срезали правый верхний угол.
 * Так как слагаемое может быть только меньше чем сама сумма.
 * Еще из особенностей - индексация идет с единицы, а не с нуля. Пушо так удобнее
 *
 * **/
class TriangleTable {
public:
    TriangleTable(size_t size);

    TriangleTable(const TriangleTable &) = delete;

    ~TriangleTable();

    const TriangleTableRow &operator[](size_t index) const;

    TriangleTableRow &operator[](size_t index);

    size_t getSize() const;

private:
    size_t size;
    TriangleTableRow *data;
};

size_t min(size_t i, size_t i1);

unsigned long maxPiramidCount(size_t n) {
    assert(n >= 1);
    TriangleTable table(n);
    /**
     * Весь смысл данного способа в том, что мы сохраняем старшее слагаемое (нижний ряд пирамиды) в таблицу. Точнее инкрементим в ячейку с table[N][ЧИСЛО]
     * Потом когда мы вычисляем более старшее N, мы смотрим на предыдущие пирамидки и инкрементим уже не на единичку, а на то число, что в ячейке.
     *
     * Таким образом мы и не храним слишком большие данные
     * И кешируем значения
     */

    table[1][1] = 1;
    if (n >= 2) {
        table[2][2] = 1;
    }
    for (size_t currentNumber = 3; currentNumber <= n; currentNumber++) {
        table[currentNumber][currentNumber] = 1;
        for (size_t maxSumComponent = currentNumber - 1; maxSumComponent != 0; maxSumComponent--) {
            for (size_t i = min(maxSumComponent - 1, currentNumber - maxSumComponent); i != 0; i--) {
                table[currentNumber][maxSumComponent] += table[currentNumber - maxSumComponent][i];
            }
        }
    }
    unsigned long result = 0;
    for (size_t i = 1; i <= n; i++) {
        result += table[n][i];
    }

    // Так как таблица инициализированна в стеке, делетить её не надо.
    return result;
}

int main() {
    size_t n;
    std::cin >> n;

    std::cout << maxPiramidCount(n);

    return 0;
}


//Описание методов классов


size_t min(size_t i, size_t i1) {
    return i < i1 ? i : i1;
}

TriangleTable::TriangleTable(size_t size) : size(size),
                                            data(NULL) {
    data = new TriangleTableRow[size];
    for (size_t i = 1; i <= size; i++)
        new(data + i - 1) TriangleTableRow(i);
}

const TriangleTableRow &TriangleTable::operator[](size_t index) const {
    assert(index > 0 && index <= size);
    return data[index - 1];
}

TriangleTableRow &TriangleTable::operator[](size_t index) {
    assert(index > 0 && index <= size);
    return data[index - 1];
}

size_t TriangleTable::getSize() const {
    return size;
}

TriangleTable::~TriangleTable() {
    delete[] data;
    assert(true);
}

TriangleTableRow::TriangleTableRow(size_t size) : size(size), data(NULL) {
    this->size = size;
    data = new unsigned long[size]{0};
}

unsigned long TriangleTableRow::operator[](size_t index) const {
    assert(index > 0 && index <= size);
    return data[index - 1];
}

unsigned long &TriangleTableRow::operator[](size_t index) {
    assert(index > 0 && index <= size);
    return data[index - 1];
}

size_t TriangleTableRow::getSize() const {
    return size;
}

TriangleTableRow::~TriangleTableRow() {
    delete[] data;
}

TriangleTableRow::TriangleTableRow() {
    //Nothing
}


