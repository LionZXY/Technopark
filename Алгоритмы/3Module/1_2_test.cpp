/*
Задача 1. Хеш-таблица

Реализуйте структуру данных типа “множество строк” на основе динамической 
хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных 
латинских букв. 
Хеш-функция строки должна быть реализована с помощью вычисления значения 
многочлена методом Горнера. 
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте 
при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 
3/4. 
Структура данных должна поддерживать операции добавления строки в множество, 
удаления строки из множества и проверки принадлежности данной строки множеству. 

1_2.​ Для разрешения коллизий используйте двойное хеширование. 
*/

#include <iostream>
#include <vector>
#include <assert.h>
#include <functional>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::function;
using std::string;

#define HASH_PRIME_1 17
#define HASH_PRIME_2 19
#define HASH_TABLE_DEFAULT_SIZE 8
#define HASH_TABLE_FILL_TO_REHASH_RATIO 0.75


int hash_1(const string &key, int size) {
    int hash = 0;
    for(int i = key.size(); i >= 0; i--)
        hash += (hash * HASH_PRIME_1 + key[i]) % size;
    return hash % size;
}


int hash_2(const string &key, int size) {
    int hash = 0;
    for(int i = key.size(); i >= 0; i--)
        hash += (hash * HASH_PRIME_2 + key[i]) % size;
    return hash % size;
}


template <typename T>
struct HashTableNode {
public:
    HashTableNode(T key, bool is_deleted=false): key(key), is_deleted(is_deleted) {}
    T key;
    bool is_deleted;
};


template <typename T>
class TechnoHashTable {
public:
    TechnoHashTable(function<int(const T&, int)> hash_1,
                    function<int(const T&, int)> extra_hash) : table(HASH_TABLE_DEFAULT_SIZE, NULL),
                                                           table_size(HASH_TABLE_DEFAULT_SIZE),
                                                           filled_table_size(0),
                                                           hash(hash_1),
                                                           extra_hash(hash_2) {}

    ~TechnoHashTable() {
        for(int i = 0; i < table.size(); i++)
            delete table[i];
    }

    bool add(const T &key);
    bool remove(const T &key);
    bool has(const T &key) const;
    

private:
    vector<HashTableNode<T>*> table;
    int table_size;
    int filled_table_size;
    function<int(const T&, int)> hash, extra_hash;

    void rehash();

};


template <typename T>
bool TechnoHashTable<T>::add(const T &key) {
        if( ((double) filled_table_size / (double) table_size)
             >= HASH_TABLE_FILL_TO_REHASH_RATIO)
            rehash();

        int h1 = hash(key, table_size);
        int first_deleted = -1;
        for (int i = 0; table[h1] != NULL && i < table_size; i++) {
            if(table[h1]->key == key && !table[h1]->is_deleted)  // Элемент уже в множестве.
                return false;

            if(table[h1]->is_deleted && first_deleted == -1)  // Нашли удалённый элемент.
                first_deleted = h1;

            int h2 = extra_hash(key, table_size);
            h1 = (h1 + h2) % table_size;
        }

        if(first_deleted == -1) {
            table[h1] = new HashTableNode<T>(key);
        }
        else {
            table[first_deleted]->key = key;
            table[first_deleted]->is_deleted = false;
        }
        filled_table_size++;

        return true;
    }


template <typename T>
bool TechnoHashTable<T>::remove(const T &key) {
    int h1 = hash(key, table_size);
    for(int i = 0; table[h1] != NULL && i < table_size; i++) {
        if(table[h1]->key == key && !table[h1]->is_deleted) {
            table[h1]->is_deleted = true;
            filled_table_size--;
            return true;
        }

        int h2 = extra_hash(key, table_size);
        h1 = (h1 + h2) % table_size;
    }

    return false;
}


template <typename T>
bool TechnoHashTable<T>::has(const T &key) const {
    int h1 = hash(key, table_size);
    for (int i = 0; table[h1] != NULL && i < table_size; i++) {
        if(table[h1]->key == key && !table[h1]->is_deleted)
            return true;

        int h2 = extra_hash(key, table_size);
        h1 = (h1 + h2) % table_size;
    }
    return false;
}

template <typename T>
void TechnoHashTable<T>::rehash() {
        int new_table_size = table_size * 2;
        vector<HashTableNode<T>*> new_table(new_table_size, NULL);

        for(int i = 0; i < table_size; i++) {
            if(table[i] != NULL && !table[i]->is_deleted) {
                int h1 = hash(table[i]->key, new_table_size);

                for(int j = 0; new_table[h1] != NULL && j < new_table_size; j++) {
                    int h2 = extra_hash(table[i]->key, new_table_size);
                    h1 = (h1 + h2) % new_table_size;
                }

                new_table[h1] = table[i];
            }
            else
                delete table[i];

            table[i] = NULL;
        }

        table = new_table;
        table_size = new_table_size;
    }


int main() {
    TechnoHashTable<string> hash_table(hash_1, hash_2);

    char command = '\0';
    string key;
    bool result = false;
    while(cin >> command >> key) {
        switch(command) {
            case '+':
                result = hash_table.add(key);
                break;
            case '-':
                result = hash_table.remove(key);
                break;
            case '?':
                result = hash_table.has(key);
                break;
            default:
                continue;
        }
        cout << (result ? "OK" : "FAIL") << endl;
    }

    return 0;
}
