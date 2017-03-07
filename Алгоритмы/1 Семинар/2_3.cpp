#include <cstdio>

//
// Created by lionzxy on 07.03.17.
//
void findRepeat(int *array, size_t arraySize) {
    // Cделаем n+1 шаг из вершины 0. После этого мы обязательно окажемся в вершине на цикле.
    int tmpIndex = 0;
    for (int i = 0; i < arraySize; i++)
        if (tmpIndex != array[tmpIndex])
            tmpIndex = array[tmpIndex];

    //Запомним эту вершину и будем продолжать шагать, пока не вернёмся в неё. Тем самым узнаем длину цикла sizeOfCycle
    int tmpResult = array[tmpIndex];
    int sizeOfCycle = 0;
    do {
        tmpIndex = tmpResult;
        sizeOfCycle++;
    } while (array[tmpIndex] != tmpResult);

    for(int i = 0; i < sizeOfCycle; i++)
        if (tmpIndex != array[tmpIndex])
            tmpIndex = array[tmpIndex];
}
