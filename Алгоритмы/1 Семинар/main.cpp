#include <iostream>
#include <assert.h>
#include <cmath>

void *getPrimes(int n, int &size, int *&primes);

int main() {
    int n = -1;
    std::cin >> n;
    assert(n != -1);

    int size = 0;
    int *primes = NULL;
    getPrimes(n, size, primes);
    assert(primes != NULL);

    for (int i = 0; i < size; i++)
        printf("%d ", primes[i]);

    delete[] primes;
    return 0;
}

/*
void *getPrimes(int n, int &size, int *&primes) {
    int sqrtVar = (int) sqrt(n) + 1;
    primes = new int[sqrtVar / 2];
    int currentPos = 0;
    primes[++currentPos] = 2;
    for (int i = 3; i < sqrtVar; i += 2) {
    }
}*/
void *getPrimes(int n, int &size, int *&primes) {
    bool *isPrime = new bool[n + 1]{true};
    size = 0;

    // Вычеркиваем непростые числа
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= n; j = i * j) {
            isPrime[i * j] = false;
        }
    }

    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            size++;
        }
    }

    primes = new int[size];
    int nonFreeIndex = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes[nonFreeIndex++] = i;
        }
    }

    assert(nonFreeIndex <= size);
    size = nonFreeIndex;
    delete[] isPrime;
}
