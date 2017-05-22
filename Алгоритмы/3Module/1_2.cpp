// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <iostream>
#include <cstring>
#include <cassert>

/**
 * Реализуйте структуру данных типа “множество строк” на основе динамической
 * хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных
 * латинских букв.
 * Хеш-функция строки должна быть реализована с помощью вычисления значения
 * многочлена методом Горнера.
 * Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте
 * при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает
 * 3/4.
 * Структура данных должна поддерживать операции добавления строки в множество,
 * удаления строки из множества и проверки принадлежности данной строки множеству.
 * 1_2.​ Для разрешения коллизий используйте двойное хеширование.
 * Формат входных данных
 * Каждая строка входных данных задает одну операцию над множеством. Запись операции
 * состоит из типа операции и следующей за ним через пробел строки, над которой
 * проводится операция.
 * Тип операции – один из трех символов:
 * + означает добавление данной строки в множество;
 * - означает удаление строки из множества;
 * ? означает проверку принадлежности данной строки множеству.
 * При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом
 * множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он
 * присутствует в этом множестве.
 * Формат выходных данных
 * Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в
 * зависимости от того, встречается ли данное слово в нашем множестве.
 *
 * Пример:
 * + hello
 * + bye
 * ? bye
 * + bye
 * - bye
 * ? bye
 * ? hello
 * Вывод:
 * OK
 * OK
 * OK
 * FAIL
 * OK
 * FAIL
 * OK
 */
unsigned int hash(const char *str, int tableSize);

const int BUFFER_SIZE = 8;
const float MAX_ALPHA = 0.75F;
const char REMOVED = 'r';
const char NULL_CHR = 'n';
const char CONTAINS = 'c';

template<class T>
class CHashMap {
private:
    /**
     * @var isNull:
     * 'r' = removed
     * 'n' = null
     * 'c' = contains
     */
    struct CHashElement {
        int hashKey;
        const char *string;
        T value;
        char varState;

        CHashElement(const char *str, T val, int hash) : string(str), value(val), hashKey(hash), varState(CONTAINS) {}

        CHashElement() : string(NULL), value(NULL), hashKey(-1), varState(NULL_CHR) {}

        CHashElement(CHashElement &other) = delete;

        //TODO Так можно?
        ~CHashElement() { if (string != NULL) delete string; }
    };

public:
    CHashMap();

    ~CHashMap();

    CHashMap(CHashMap *cHashMap) = delete;

    void put(const char *str, T value);

    T get(const char *str);

    void remove(const char *str);

    bool has(const char *str) { return getElement(str) != NULL; }

    inline bool isNill(CHashElement *element);

private:
    int currentSize;
    int bufferSize;

    CHashElement *buffer;

    void rehash();

    unsigned int nextHash(unsigned int hsh1, unsigned int hsh2, int i);

    unsigned int hash(const char *str);

    unsigned int hash2(const char *str);

    bool isEmpty(CHashMap::CHashElement *element);

    CHashElement *getElement(const char *str);
};

template<class T>
CHashMap<T>::CHashMap(): buffer(NULL), currentSize(0), bufferSize(BUFFER_SIZE) {
    buffer = new CHashElement[bufferSize]();
}

template<class T>
CHashMap<T>::~CHashMap() {
    delete[] buffer;
}

template<class T>
void CHashMap<T>::put(const char *str, T value) {
    char *newString = new char[strlen(str) + 1];
    strcpy(newString, str);
    int hsh1 = hash(newString);
    int hsh2 = hash2(newString);

    assert(hsh1 < bufferSize && hsh2 < bufferSize);

    // Подразумевается, что у нас никогда не происходит переполнение
    int i = nextHash(hsh1, hsh2, 0);
    for (int j = 1; !isEmpty(&buffer[i]); i = nextHash(hsh1, hsh2, j++));
    buffer[i].string = newString;
    buffer[i].hashKey = hsh1;
    buffer[i].value = value;
    buffer[i].varState = CONTAINS;
    currentSize++;

    if ((float) ((float) currentSize / bufferSize) >= MAX_ALPHA)
        rehash();
}

template<class T>
bool CHashMap<T>::isEmpty(CHashMap::CHashElement *element) {
    assert(element->varState == NULL_CHR || element->varState == REMOVED || element->varState == CONTAINS);
    return element == NULL || element->varState == REMOVED || element->varState == NULL_CHR;
}

template<class T>
bool CHashMap<T>::isNill(CHashMap::CHashElement *element) {
    assert(element->varState == NULL_CHR || element->varState == REMOVED || element->varState == CONTAINS);
    return element == NULL || element->varState == NULL_CHR;
}

template<class T>
void CHashMap<T>::rehash() {
    int size = bufferSize;
    CHashElement *oldArray = buffer;
    bufferSize *= 2;
    buffer = new CHashElement[bufferSize]();
    currentSize = 0;

    for (int i = 0; i < size; i++)
        if (!isEmpty(&oldArray[i]))
            put(oldArray[i].string, oldArray[i].value);
    delete[] oldArray; // Специально опущены []
}

template<class T>
T CHashMap<T>::get(const char *str) {
    CHashElement *element = getElement(str);
    if (element == NULL)
        return NULL;
    else return element->value;
}

template<class T>
void CHashMap<T>::remove(const char *str) {
    CHashElement *element = getElement(str);
    currentSize--;
    if (element != NULL) {
        element->varState = REMOVED;
    }
}

template<class T>
typename CHashMap<T>::CHashElement *CHashMap<T>::getElement(const char *str) {
    int hsh = hash(str);
    int hsh2 = hash2(str);
    int i;
    int j;
    for (j = 0, i = nextHash(hsh, hsh2, j); !isNill(&buffer[i]) && j < bufferSize; i = nextHash(hsh, hsh2, ++j)) {
        if (!isEmpty(&buffer[i])) {
            if (buffer[i].hashKey == hsh) {
                if (!strcmp(str, buffer[i].string)) {
                    return &(buffer[i]);
                }
            }
        }
    }

    return NULL;
}

template<class T>
unsigned int CHashMap<T>::nextHash(unsigned int hsh1, unsigned int hsh2, int i) {
    return (hsh1 + hsh2 * i) % bufferSize;
}

int main() {
    CHashMap<int> hashMap;
    std::string tmpStr;
    const char *tmpWord;
    char operationCode;
    while (std::cin >> operationCode && std::cin >> tmpStr) {
        tmpWord = tmpStr.c_str();
        switch (operationCode) {
            case '+':
                if (!hashMap.has(tmpWord)) {
                    hashMap.put(tmpWord, 1);
                    std::cout << "OK\n";
                } else std::cout << "FAIL\n";
                break;
            case '-':
                if (hashMap.has(tmpWord)) {
                    hashMap.remove(tmpWord);
                    std::cout << "OK\n";
                } else std::cout << "FAIL\n";
                break;
            case '?':
                if (hashMap.has(tmpWord)) {
                    std::cout << "OK\n";
                } else std::cout << "FAIL\n";
                break;
            default:
                assert(false);
                break;
        }
    }
    return 0;
}


//Todo Двойное хеширование
const int MAGIC_NUMBER = 13;

// Хеш-функция строки
// Возвращает четные числа
template<class T>
unsigned int CHashMap<T>::hash(const char *str) {
    unsigned int hash = 0;
    for (; *str != 0; ++str)
        hash = (hash * MAGIC_NUMBER + *str) % bufferSize;
    return hash == 0 ? 1 : hash;
}

const int MAGIC_NUMBER2 = 11;

// Хеш-функция строки.
// Возвращает нечетные числа
template<class T>
unsigned int CHashMap<T>::hash2(const char *str) {
    unsigned int hash = 0;
    for (; *str != 0; ++str)
        hash = (hash * MAGIC_NUMBER2 + *str) % bufferSize;
    if (hash % 2 == 0)
        hash = (hash + 1) % bufferSize;
    return hash == 0 ? 1 : hash;
}