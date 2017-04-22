#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

/**
 * Решение всех задач данного раздела предполагает использование кучи.
 *
 * 2_1. Жадина.
 * Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной массы. Вовочка
 * может поднять не более K грамм. Каждый фрукт весит не более K грамм. За раз он выбирает
 * несколько самых тяжелых фруктов, которые может поднять одновременно, откусывает от каждого
 * половину и кладет огрызки обратно в корзину. Если фрукт весит нечетное число грамм, он
 * откусывает большую половину. Фрукт массы 1гр он съедает полностью.
 * Определить за сколько подходов Вовочка съест все фрукты в корзине.
 *
 * Формат входных данных. Вначале вводится n - количество фруктов и n строк с массами фруктов.
 * Затем K - "грузоподъемность".
 *
 * Формат выходных данных. Неотрицательное число - количество подходов к корзине.
 *
 * Пример 1:
 * 3
 * 1 2 2
 * 2
 * Вывод:
 * 4
 *
 * Пример 2:
 * 3
 * 4 3 5
 * 6
 * Вывод:
 * 5
 *
 * Пример 3:
 * 7
 * 1 1 1 1 1 1 1
 * 3
 * Вывод:
 * 3
 */

class CBinaryHeap {
public:
    CBinaryHeap();

    ~CBinaryHeap();

    CBinaryHeap(const CBinaryHeap &other);

    CBinaryHeap(std::vector<int> array);

    void Add(int element);

    int ExtractMax();

    bool IsEmpty();

    int SeeMax();

    void Print();

private:
    std::vector<int> array;

    void siftUp(int index);

    void siftDown(int index);
};

CBinaryHeap::CBinaryHeap() {
    //Init
}

CBinaryHeap::~CBinaryHeap() {
    //Delete
}

CBinaryHeap::CBinaryHeap(const CBinaryHeap &other) {
    //Copy
}

void CBinaryHeap::siftUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (array[index] <= array[parent])
            return;
        std::swap(array[index], array[parent]);
        index = parent;
    }
}

void CBinaryHeap::siftDown(int index) {
    int left = index * 2 + 1; //Элемент ниже ребра графа, слева
    int right = index * 2 + 2; //Тоже самое, справа
    int largest = index;
    assert(index < array.size());
    if (!(left < array.size() && array[left] > array[index]))
        left = index;
    if (!(right < array.size() && array[right] > array[index]))
        right = index;
    if (array[left] > array[right])
        largest = left;
    else largest = right;

    if (largest != index) {
        std::swap(array[index], array[largest]);
        siftDown(largest);
    }
}

CBinaryHeap::CBinaryHeap(std::vector<int> array) {
    this->array = array;
    for (int i = (int) (array.size() / 2 - 1); i >= 0; --i) {
        siftDown(i);
    }
}

void CBinaryHeap::Add(int element) {
    array.push_back(element);
    siftUp((int) (array.size() - 1));
}

int CBinaryHeap::ExtractMax() {
    assert(!array.empty());
    int result = array[0];
    array[0] = array.back();
    array.pop_back();

    if (!array.empty())
        siftDown(0);

    return result;
}

bool CBinaryHeap::IsEmpty() {
    return array.empty();
}

int CBinaryHeap::SeeMax() {
    assert(!IsEmpty());
    return array[0];
}

void CBinaryHeap::Print() {
    for(int i = 0; i < array.size(); i++)
        std::cout << array[i] << ' ';
    std::cout << '\n';
}

int getAccessCount(std::vector<int> fruitsArray, int maxCapacity /* Грузоподьемность */ ) {
    int count = 0;
    CBinaryHeap fruits(fruitsArray);
    while (!fruits.IsEmpty()) {
        int weightAviliable = maxCapacity;
        count++;
        std::vector<int> tmpVector;
        while (!fruits.IsEmpty() && fruits.SeeMax() <= weightAviliable) {
            weightAviliable -= fruits.SeeMax();
            tmpVector.push_back(fruits.ExtractMax());
        }

        int tmp;
        while(!tmpVector.empty()) {
            tmp = tmpVector.back();
            tmpVector.pop_back();
            if (tmp != 1)
                fruits.Add(tmp / 2);

        }
        //fruits.Print();
    }
    return count;
}

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<int> fruits((unsigned long) n);
    for (int i = 0; i < n; i++)
        std::cin >> fruits[i];

    int k = 0; // Грузоподьемность
    std::cin >> k;

    int result = getAccessCount(fruits, k);
    std::cout << result;
    return 0;
}