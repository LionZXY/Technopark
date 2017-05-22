#include <iostream>
#include <assert.h>
#include <cstring>

#define BUFFER_SIZE 16

/**
 *
 * В город ​ N приехал цирк с командой атлетов. Они хотят удивить горожан города ​ N — выстроить из своих тел
 * башню максимальной высоты. Башня — это цепочка атлетов, первый стоит на земле, второй стоит у него на
 * плечах, третий стоит на плечах у второго и т.д.
 * Каждый атлет характеризуется силой ​ s i (kg) и массой ​ m i (kg). Сила — это максимальная масса, которую
 * атлет способен держать у себя на плечах.
 * К сожалению ни один из атлетов не умеет программировать, так как всю жизнь они занимались физической
 * подготовкой, и у них не было времени на изучение языков программирования. Помогите им, напишите
 * программу, которая определит максимальную высоту башни, которую они могут составить.
 * Известно, что если атлет тяжелее, то он и сильнее:
 * если ​ m i > ​ m j , то ​ s i > ​ s j .
 * Атлеты равной массы могут иметь различную силу.
 * Формат входных данных:
 * Вход содержит только пары целых чисел ​ — массу и силу атлетов. Число атлетов 1 ≤ ​ n ≤ 100000. Масса и
 * сила являются положительными целыми числами меньше, чем 2000000.
 * Формат выходных данных:
 * Выход должен содержать натуральное число — максимальную высоту башни
 *
 * Пример:
 * 3 4
 * 2 2
 * 7 6
 * 4 5
 * Вывод:
 * 3
**/

template<typename T>
void qsort(T *array, int start, int end, int (*compare)(T *firstVar, T *twoVar));

struct Athlet {
    int weight;
    int force;

    Athlet() : weight(0), force(0) {};
};

class Stack {
public:
    Stack();

    ~Stack();

    int getCount() const { return count; }

    bool IsEmpty() const { return getCount() == 0; }

    void Push(Athlet value);

    Athlet Pop();

    Athlet *getAsArray();

private:
    int curIndex = 0;
    int count = 0;
    int bufferSize = 0;

    Athlet *buffer;
};

int getMaxHeightTower(Stack &stack) {
    int height = 0;
    int forceNeed = 0;
    Athlet tmpAthlet;

    qsort<Athlet>(stack.getAsArray(), 0, stack.getCount() - 1, [](Athlet *athletOne, Athlet *athletTwo) {
        return athletOne->weight == athletTwo->weight ? athletTwo->force - athletOne->force :
               athletTwo->weight - athletOne->weight;
    });

    while (!stack.IsEmpty()) {
        tmpAthlet = stack.Pop();
        if (tmpAthlet.force >= forceNeed) {
            height++;
            forceNeed += tmpAthlet.weight;
        }
    }

    return height;
}

int main() {
    Stack stack;
    Athlet tmpAthlet;

    while (std::cin.good() && !std::cin.eof()) {
        std::cin >> tmpAthlet.weight;
        std::cin >> tmpAthlet.force;
        stack.Push(tmpAthlet);
    }

    std::cout << getMaxHeightTower(stack);

    return 0;
}

Athlet Stack::Pop() {
    assert(!IsEmpty());

    count--;
    return buffer[--curIndex];
}

Athlet *Stack::getAsArray() {
    return buffer;
}

void Stack::Push(Athlet value) {
    if (count == bufferSize) {
        bufferSize += BUFFER_SIZE;
        size_t oldSize = sizeof(Athlet) * bufferSize;
        Athlet *oldbuffer = buffer;
        buffer = new Athlet[bufferSize];
        memcpy(buffer, oldbuffer, oldSize);
        delete[] oldbuffer;
    }

    count++;
    buffer[curIndex++] = value;
}

Stack::Stack() : bufferSize(BUFFER_SIZE), curIndex(0), count(0) {
    buffer = new Athlet[bufferSize];
}

Stack::~Stack() {
    delete[] buffer;
};

template<typename T>
void qsort(T *array, int start, int end, int (*compare)(T *firstVar, T *twoVar)) {
    int i = start;
    int j = end;
    T middle = array[(start + end) / 2];
    T tmp;

    do {
        while (compare(&array[i], &middle) < 0) i++;
        while (compare(&array[j], &middle) > 0) j--;

        if (i <= j) {
            if (compare(&array[i], &array[j]) > 0) {
                tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < end)
        qsort(array, i, end, compare);
    if (start < j)
        qsort(array, start, j, compare);
}