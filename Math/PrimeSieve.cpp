#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<class T>
vector<T> sievePrimes(T n) {
    T m = sqrt(n);
    vector<int> isPrime(m + 1, true);
    vector<T> primes;
    for (T i = 2; i <= m; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (T j = i * i; j <= m; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return primes;
}