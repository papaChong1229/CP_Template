#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> primes;

void sievePrimes(ll n) {
    ll m = sqrt(n);
    vector<int> isPrime(m + 1, true);
    
    for (ll i = 2; i <= m; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (ll j = i * i; j <= m; j += i) {
                isPrime[j] = false;
            }
        }
    }
}