/*
void getPrimes(int n, int &size, int *&primes) {
    bool *isPrime = new bool[n + 1];
    size = 0;
    for (int i = 0; i < n + 1; i++)
        isPrime[i] = true;

    // Вычеркиваем непростые числа
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            for (int j = 2; j <= n; j = i * j) {
                isPrime[i * j] = false;
            }
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
 */