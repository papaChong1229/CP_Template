#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 標準 UnionFind
class UnionFind {
private:
    vector<int> rank, fa;

public:
    UnionFind(int n) {
        rank.resize(n);
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int x) {
        if (x == fa[x]) {
            return x;
        }
        return fa[x] = find(fa[x]);
    }

    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px != py) {
            if (rank[px] < rank[py]) {
                swap(px, py);
            }
            fa[py] = px;
            rank[px] += (rank[px] == rank[py]);
        }
    }

    bool isConnected(int x, int y) {
        return find(x) == find(y);
    }
};