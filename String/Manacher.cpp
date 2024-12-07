#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Longest Palindrome Length table for half length
vector<int> computeLPLTable(const string& s) {
    string t = "^#";
    for (const char& c : s) {
        t += c; t += "#";
    }
    t += "$";

    int n = t.size();
    vector<int> p(n, 0);
    int center = 0, right = 0;
    for (int i = 1; i < n - 1; i++) {
        if (i < right) {
            int mirror = center * 2 - i;
            p[i] = min(p[mirror], right - i);
        }
        while (t[i + p[i]] == t[i - p[i]]) {
            p[i]++;
        }
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
    }
    return p;
};

int getLPLIndex(int i) {
    return i * 2 + 2;
};