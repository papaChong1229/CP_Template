#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Longest prefix suffix table for s
vector<int> computeLPSTable(string& s) {
    int n = s.size();
    vector<int> res(n);
    int prefix = 0;
    for (int i = 1; i < n; i++) {
        while (prefix && s[prefix] != s[i]) {
            prefix = res[prefix - 1];
        }
        if (s[prefix] == s[i]) {
            prefix++;
            res[i] = prefix;
        }
    }
    return res;
};

// 搜尋所有 pattern 在 text 中的開頭位置
vector<int> findPatternMatches(string& text, string& pattern) {
    int n = text.size(), m = pattern.size();
    vector<int> res, lps = computeLPSTable(pattern);
    int prefix = 0;
    for (int i = 0; i < n; i++) {
        while (prefix && text[i] != pattern[prefix]) {
            prefix = lps[prefix - 1];
        }
        if (text[i] == pattern[prefix]) {
            prefix++;
        }
        if (prefix == m) {
            res.push_back(i - m + 1);
            prefix = lps[prefix - 1];
        }
    }
    return res;
};