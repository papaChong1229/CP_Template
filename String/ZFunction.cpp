#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> computeZTable(const string& s) {
    int n = s.size();
    vector<int> z(n);
    int left = 0, right = 0;
    for (int i = 1; i < n; i++) {
        if (i <= right) {
            z[i] = min(z[i - left], right - i + 1);
        }

        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }

        if (i + z[i] - 1 > right) {
            left = i, right = i + z[i] - 1;
        }
    }
    return z;
};