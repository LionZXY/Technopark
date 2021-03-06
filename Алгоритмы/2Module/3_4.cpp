/**
 * Во всех задачах данного раздела необходимо реализовать и использовать локальную
 * пирамидальную сортировку ​(без использования дополнительной памяти). Общее время работы
 * алгоритма O(n log n).
 *
 * 3_4. Закраска прямой 2.
 * На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого
 * отрезка (Li и Ri). Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
 *
 * Пример 1:
 * 3
 * 1 4
 * 7 8
 * 2 5
 * Вывод:
 * 3
 *
 * Пример 2:
 * 4
 * 1 12
 * 14 21
 * 3 10
 * 11 15
 * Вывод:
 * 11
 */
#include <iostream>
#include <vector>
#include <assert.h>


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

struct Line {
    int start;
    int end;

    Line() : start(0), end(0) {};

    Line(int start, int end) : start(start), end(end) {
        if (end < start)
            std::swap(start, end);
    }
};


bool isLess(const Line &p1, const Line &p2) {
    return p1.start == p2.start ? p1.end > p2.end : p1.start > p2.start;
}

int getLen(std::vector<Line> linesArray) {
    int len = 0;
    CBinaryHeap<Line, bool(const Line &, const Line &)> lines(linesArray, isLess);

    if (!lines.IsEmpty()) {
        Line prevLine = lines.ExtractMax();
        while (!lines.IsEmpty()) {
            Line tmp = lines.ExtractMax();

            if (tmp.start < prevLine.start)
                tmp.start = prevLine.start;

            if (tmp.end >= prevLine.start)
                if (tmp.start < prevLine.end) {
                    if (tmp.end > prevLine.end) {
                        len += tmp.start - prevLine.start;
                        prevLine.start = prevLine.end;
                        prevLine.end = tmp.end;
                    } else if (tmp.end < prevLine.end) {
                        len += tmp.start - prevLine.start;
                        prevLine.start = tmp.end;
                        prevLine.end = prevLine.end;
                    } else {
                        len += tmp.start - prevLine.start;
                        prevLine.start = tmp.end;
                        prevLine.end = tmp.end;
                    }
                } else {
                    len += prevLine.end - prevLine.start;
                    prevLine = tmp;
                }
        }
        len += prevLine.end - prevLine.start;
    }
    return len;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<Line> lines;

    int start = 0;
    int end = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> start >> end;
        lines.push_back(Line(start, end));
    }

    int maxLen = getLen(lines);
    std::cout << maxLen;
    return 0;
}


