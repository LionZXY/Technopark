#include <iostream>
#include <assert.h>
#include <cmath>

void getPrimesForDivN(int n, size_t &size, int *&primes);

int main() {
    int n = -1;
    std::cin >> n;
    assert(n != -1);

    size_t size = 0;
    int *primes = NULL;
    getPrimesForDivN(n, size, primes);
    assert(primes != NULL);

    for (int i = 0; i < size; i++)
        printf("%d ", primes[i]);

    delete[] primes;
    return 0;
}

void getPrimesForDivN(int n, size_t &size, int *&returnVar) {
    int maxN = n / 2 + 1;
    bool *isPrime = new bool[maxN + 1];
    size = 0;
    for (int i = 1; i <= maxN; i += 2)
        isPrime[i] = true;

    for (int i = 0; i <= maxN; i += 2)
        isPrime[i] = false;

    // Вычеркиваем непростые числа
    for (int i = 3; i <= maxN; i++) {
        if (isPrime[i]) {
            for (int j = i * 2; j <= maxN; j += i) {
                isPrime[j] = false;
            }
            size++;
        }
    }
    returnVar = (int *) malloc((size_t) (sizeof(int) * sqrt(maxN)));
    int varCount = 0;

    int tmpVarForDeliver = n;
    do {
        if (tmpVarForDeliver % 2 == 0) {
            returnVar[varCount++] = 2;
            tmpVarForDeliver = tmpVarForDeliver / 2;

        } else
            for (int i = 3; i < maxN; i += 2)
                if (tmpVarForDeliver % i == 0 && isPrime[i]) {
                    returnVar[varCount++] = i;
                    tmpVarForDeliver = tmpVarForDeliver / i;
                    break;
                }
        //printf("%d %d\n", tmpVarForDeliver, isPrime[tmpVarForDeliver]);
    } while (tmpVarForDeliver < maxN && !isPrime[tmpVarForDeliver]);

    if (tmpVarForDeliver != 1)
        returnVar[varCount++] = tmpVarForDeliver;

    size = (size_t) varCount;
    delete[] isPrime;
}