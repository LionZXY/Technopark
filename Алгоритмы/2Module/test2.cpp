#include <chrono>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <iostream>


template<class T, class COMPARE>
class CBinaryHeap {
public:
    CBinaryHeap(COMPARE &isLess);

    ~CBinaryHeap();

    CBinaryHeap(const CBinaryHeap &other);

    CBinaryHeap(std::vector<T> array, COMPARE &isLess);

    void Add(T element);

    T ExtractMax();

    bool IsEmpty();

    T SeeMax();

private:
    std::vector<T> array;
    COMPARE *isLess;

    void siftUp(int index);

    void siftDown(int index);
};

bool isLess(const int &p1, const int &p2) {
    return p1 < p2;
}

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

template<class T, class COMPARE>
CBinaryHeap<T, COMPARE>::CBinaryHeap(COMPARE &isLess) {
    assert(isLess != NULL);
    this->isLess = isLess;
}

template<class T, class COMPARE>
CBinaryHeap<T, COMPARE>::CBinaryHeap(std::vector<T> array, COMPARE &isLess) {
    this->array = array;
    this->isLess = isLess;
    for (int i = (int) (array.size() / 2 - 1); i >= 0; --i) {
        siftDown(i);
    }
}

template<class T, class COMPARE>
CBinaryHeap<T, COMPARE>::~CBinaryHeap() {
    //Delete
}

template<class T, class COMPARE>
CBinaryHeap<T, COMPARE>::CBinaryHeap(const CBinaryHeap &other) {
    isLess = other.isLess;
}

template<class T, class COMPARE>
void CBinaryHeap<T, COMPARE>::siftUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (!isLess(array[parent], array[index]))
            return;
        std::swap(array[index], array[parent]);
        index = parent;
    }
}

template<class T, class COMPARE>
void CBinaryHeap<T, COMPARE>::siftDown(int index) {
    int left = index * 2 + 1; //Элемент ниже ребра графа, слева
    int right = index * 2 + 2; //Тоже самое, справа
    int largest = index;
    assert(index < array.size());
    if (!(left < array.size() && isLess(array[index], array[left])))
        left = index;
    if (!(right < array.size() && isLess(array[index], array[right])))
        right = index;

    if (isLess(array[left], array[right]))
        largest = right;
    else largest = left;

    if (largest != index) {
        std::swap(array[index], array[largest]);
        siftDown(largest);
    }
}

template<class T, class COMPARE>
void CBinaryHeap<T, COMPARE>::Add(T element) {
    array.push_back(element);
    siftUp((int) (array.size() - 1));
}

template<class T, class COMPARE>
T CBinaryHeap<T, COMPARE>::ExtractMax() {
    assert(!array.empty());
    T result = array[0];
    array[0] = array.back();
    array.pop_back();

    if (!array.empty())
        siftDown(0);

    return result;
}

template<class T, class COMPARE>
bool CBinaryHeap<T, COMPARE>::IsEmpty() {
    return array.empty();
}

template<class T, class COMPARE>
T CBinaryHeap<T, COMPARE>::SeeMax() {
    assert(!IsEmpty());
    return array[0];
}