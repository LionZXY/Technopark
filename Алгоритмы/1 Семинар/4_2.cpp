#include <assert.h>
#include <iostream>

#define BUFFER_SIZE 16

/**
 * Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды
 * push* и pop*.
 * Формат входных данных.
 * В первой строке количество команд n. n ≤ 1000000.
 * Каждая команда задаётся как 2 целых числа: a b.
 * a = 1 - push front
 * a = 2 - pop front
 * a = 3 - push back
 * a = 4 - pop back
 * Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
 * Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
 * Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры
 * данных, то ожидается “-1”.
 * Формат выходных данных.
 * Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не
 * оправдалось, то напечатать NO.
 *
 *
 *
 *
 * 4_2. ​Реализовать дек с динамическим зацикленным буфером
 * Пример 1:
 * 3
 * 1 44
 * 3 50
 * 2 44
 * Вывод:
 * YES
 *
 * Пример 2:
 * 2
 * 2 -1
 * 1 10
 * Вывод:
 * YES
 *
 * Пример 3:
 * 2
 * 3 44
 * 4 66
 * Вывод:
 * NO
 */

class CDeque {
public:
    CDeque() : headIndex(-1), nodeBuffer(NULL), tailIndex(-1), count(0), bufferSize(BUFFER_SIZE) {
        nodeBuffer = (CNode *) malloc(sizeof(CNode) * bufferSize);
    }

    ~CDeque() {
        if (nodeBuffer != NULL)
            delete[] nodeBuffer;
    }

    void PushBack(int key);

    void PushFront(int key);

    void Zip();

    int PopBack();

    int PopFront();

    bool IsEmpty() const { return count == 0; }

private:
    // Узел списка
    struct CNode {
        int Key;
    };
    int count;
    int bufferSize;

    int tailIndex;
    int headIndex;

    CNode *nodeBuffer;

};

void CDeque::PushBack(int key) {
    if (IsEmpty()) {
        headIndex = tailIndex = 0;
        nodeBuffer[headIndex].Key = key;
        count = 1;
        return;
    }

    assert(count != 0);
    // Добавляем элемент в конец списка.
    if (bufferSize - count < 2) {
        CNode *oldBuffer = nodeBuffer;
        int oldBufferSize = bufferSize;

        bufferSize += BUFFER_SIZE;
        nodeBuffer = (CNode *) malloc(sizeof(CNode) * bufferSize);

        //Первым элементом устанавливаем ключ так как мы вызываем PushBack
        nodeBuffer[0].Key = key;
        count++;
        for (int i = headIndex, j = 1; j < count; i++, j++)
            if (i < oldBufferSize)
                nodeBuffer[j] = oldBuffer[i];
            else {
                i = 0;
                nodeBuffer[j] = oldBuffer[i];
            }

        headIndex = 0;
        tailIndex = count - 1;
        delete[] oldBuffer;
        return;
    }

    if (headIndex != 0) {
        nodeBuffer[--headIndex].Key = key;
        count++;
    } else {
        headIndex = bufferSize - 1;
        nodeBuffer[headIndex].Key = key;
        count++;
    }
}

void CDeque::PushFront(int key) {
    if (IsEmpty()) {
        headIndex = tailIndex = 0;
        nodeBuffer[tailIndex].Key = key;
        count = 1;
        return;
    }

    assert(count != 0);
    // Добавляем элемент в конец списка.
    if (bufferSize - count < 2) {
        CNode *oldBuffer = nodeBuffer;
        int oldBufferSize = bufferSize;

        bufferSize += BUFFER_SIZE;
        nodeBuffer = (CNode *) malloc(sizeof(CNode) * bufferSize);

        for (int i = headIndex, j = 0; j < count; i++, j++)
            if (i < oldBufferSize)
                nodeBuffer[j] = oldBuffer[i];
            else {
                i = 0;
                nodeBuffer[j] = oldBuffer[i];
            }

        headIndex = 0;
        tailIndex = count - 1;
        delete[] oldBuffer;
    }

    if(tailIndex < bufferSize - 1)
        tailIndex++;
    else tailIndex = 0;

    nodeBuffer[tailIndex].Key = key;
    count++;
}

void CDeque::Zip() {
    int oldBufferSize = bufferSize;
    bufferSize = count % BUFFER_SIZE + count;
    CNode *oldBuffer = nodeBuffer;

    nodeBuffer = (CNode *) malloc(sizeof(CNode) * bufferSize);

    for (int i = headIndex, j = 0; j < count; i++, j++)
        if (i < oldBufferSize)
            nodeBuffer[j] = oldBuffer[i];
        else {
            i = 0;
            nodeBuffer[j] = oldBuffer[i];
        }

    headIndex = 0;
    tailIndex = count - 1;
    delete[] oldBuffer;
}

int CDeque::PopBack() {
    assert(!IsEmpty());

    count--;
    int result = nodeBuffer[headIndex].Key;

    if(headIndex < bufferSize - 1)
        headIndex++;
    else headIndex = 0;

    return result;
}

int CDeque::PopFront() {
    assert(!IsEmpty());

    count--;
    int result = nodeBuffer[tailIndex].Key;

    if (tailIndex > 0)
        tailIndex--;
    else tailIndex = bufferSize - 1;

    return result;
}

void unit_test() {
    CDeque deque;
    deque.PushBack(2);
    deque.PushFront(3);
    assert(deque.PopBack() == 2);

    deque.PushFront(5);
    assert(deque.PopBack() == 3);

    deque.PushBack(7);
    assert(deque.PopFront() == 5);

    assert(deque.PopBack() == 7);

    assert(deque.IsEmpty());

    for (int i = 0; i < 10000; i++)
        deque.PushFront(i);

    assert(deque.PopBack() == 0);
    assert(deque.PopFront() == 10000 - 1);

    for (int i = 1; i < 10000 - 1; i++)
        assert(deque.PopBack() == i);

    assert(deque.IsEmpty());

    for (int i = 0; i < 20000; i++)
        deque.PushBack(i);

    assert(deque.PopBack() == 20000 - 1);
    assert(deque.PopFront() == 0);

    int tmp = 0;
    for (int i = 1; i < 20000 - 1; i++) {
        tmp = deque.PopFront();
        assert(tmp == i);
    }

    assert(deque.IsEmpty());
    deque.Zip();

    for (int i = 0; i < 30000; i++)
        if (i % 2 == 0)
            deque.PushFront(i);
        else deque.PushBack(i);

    for (int i = 30000 - 1; i > 0; i -= 2)
        assert(deque.PopBack() == i);

    for (int i = 30000 - 2; i > 0; i -= 2)
        assert(deque.PopFront() == i);

    assert(deque.PopBack() == 0);

    deque.Zip();
    assert(deque.IsEmpty());

    deque.PushBack(0);
    assert(deque.PopFront() == 0);
    assert(deque.IsEmpty());

    deque.PushBack(4);
    assert(deque.PopFront() == 4);
    assert(deque.IsEmpty());

    deque.Zip();
    assert(deque.IsEmpty());

    deque.PushFront(0);
    assert(deque.PopBack() == 0);
    assert(deque.IsEmpty());

    deque.PushFront(4);
    assert(deque.PopBack() == 4);
    assert(deque.IsEmpty());

    deque.PushBack(0);
    deque.PopFront();
    assert(deque.IsEmpty());
}

int main() {
    //unit_test();

    int requestsCount = 0;
    std::cin >> requestsCount;

    CDeque deque;
    for (int i = 0; i < requestsCount; ++i) {
        int requestType = 0;
        int requestValue = 0;
        std::cin >> requestType >> requestValue;
        switch (requestType) {
            case 1:
                deque.PushFront(requestValue);
                break;
            case 2:
                if (deque.IsEmpty()) {
                    if (requestValue != -1) {
                        std::cout << "NO";
                        return 0;
                    }
                } else {
                    int tmp = deque.PopFront();
                    if (tmp != requestValue) {
                        std::cout << "NO";
                        return 0;
                    }
                }
                break;
            case 3:
                deque.PushBack(requestValue);
                break;
            case 4:
                if (deque.IsEmpty()) {
                    if (requestValue != -1) {
                        std::cout << "NO";
                        return 0;
                    }
                } else {
                    if (deque.PopBack() != requestValue) {
                        std::cout << "NO";
                        return 0;
                    }
                }
                break;
            default:
                assert(false);
        }
    }

    std::cout << "YES";
    return 0;
}