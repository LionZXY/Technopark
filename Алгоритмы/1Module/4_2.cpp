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
        nodeBuffer = new CNode[bufferSize];
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
        nodeBuffer = new CNode[bufferSize];

        //Первым элементом устанавливаем ключ так как мы вызываем PushBack
        nodeBuffer[0].Key = key;
        count++;
        //TODO переставить на memcpy
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
        nodeBuffer = new CNode[bufferSize];

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

    if (tailIndex < bufferSize - 1)
        tailIndex++;
    else tailIndex = 0;

    nodeBuffer[tailIndex].Key = key;
    count++;
}

void CDeque::Zip() {
    int oldBufferSize = bufferSize;
    bufferSize = count % BUFFER_SIZE + count;
    CNode *oldBuffer = nodeBuffer;

    nodeBuffer = new CNode[bufferSize];

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

    if (headIndex < bufferSize - 1)
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

int main() {
    int requestValue = 0;
    int requestsCount = 0;
    std::cin >> requestsCount;

    CDeque deque;
    for (int i = 0; i < requestsCount; ++i) {
        int requestType = 0;
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