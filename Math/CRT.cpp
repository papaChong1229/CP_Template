#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y);
    ll tmp = x;
    x = y;
    y = tmp - a / b * y;
    return d;
}

// pair(a, m)
ll exCRT(vector<pair<ll, ll>>& nums) {
    // [a, m]
    int n = nums.size();
    pair<ll, ll> base = nums[0];
    for (int i = 1; i < n; i++) {
        auto [a1, m1] = base;
        auto [a2, m2] = nums[i];

        ll d = gcd(m1, m2);
        if ((a2 - a1) % d) {
            return -1;  // 無解
        }

        ll l1, l2;
        exgcd(m1 / d, m2 / d, l1, l2);

        ll mod = lcm(m1, m2);
        ll res = (a1 + (a2 - a1) / d * l1 * m1) % mod;
        if (res < 0) res += mod;
        base = {res, mod};
    }
    return base.first;
}