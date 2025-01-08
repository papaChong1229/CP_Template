#include "bits/stdc++.h"

using ll = long long;
int MOD = 1e9 + 7;
int MX = 1e5 + 1;
std::vector<ll> f, fi;

ll qpow(ll x, int p) {
    ll res = 1;
    while (p) {
        if (p & 1) {
            res = res * x % MOD;
        }
        x = x * x % MOD;
        p >>= 1;
    }
    return res;
}

auto init = []{
    f.resize(MX);
    fi.resize(MX);

    f[0] = 1;
    for (int i = 1; i < MX; i++) {
        f[i] = i * f[i - 1] % MOD;
    }
    fi[MX - 1] = qpow(f[MX - 1], MOD - 2);
    for (int i = MX - 1; i > 0; i--) {
        fi[i - 1] = fi[i] * i % MOD;
    }
    return 0;
}();

ll comb(int n, int r) {
    return f[n] * fi[r] % MOD * fi[n - r] % MOD; 
}

ll perm(int n, int r) {
    return f[n] * fi[n - r] % MOD;
}