#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll LINF = 0x3f3f3f3f3f3f3f3f;

class MaxFlow {
private:
    struct Edge {
        int to, next;
        ll cap;

        Edge(int to, ll cap, int next) : to(to), cap(cap), next(next) {}
    };

    int n, S, T;
    vector<Edge> edges;
    vector<int> head, iter, depth;

    bool bfs() {
        ranges::fill(depth, -1);
        depth[S] = 0;

        queue<int> q;
        q.push(S);
        while (!q.empty()) {
            int curr = q.front(); q.pop();
            for (int i = head[curr]; i != -1; i = edges[i].next) {
                int next = edges[i].to;
                if (edges[i].cap && depth[next] == -1) {
                    depth[next] = depth[curr] + 1;
                    q.push(next);
                }
            }
        }
        return depth[T] != -1;
    }

    ll dfs(int curr, ll flow) {
        if (curr == T || flow == 0) {
            return flow;
        }

        for (int& i = iter[curr]; i != -1; i = edges[i].next) {
            int next = edges[i].to;
            ll f;
            if (depth[curr] + 1 == depth[next] && edges[i].cap && (f = dfs(next, min(flow, edges[i].cap)))) {
                edges[i].cap -= f;
                edges[i ^ 1].cap += f;
                return f;
            }
        }
        return 0;
    }

public:
    MaxFlow(int n, int S, int T) : n(n), S(S), T(T),
        head(n + 1, -1), iter(n + 1, -1), depth(n + 1, -1) {}

    void addEdge(int from, int to, ll cap) {
        edges.push_back(Edge(to, cap, head[from]));
        head[from] = edges.size() - 1;
        edges.push_back(Edge(from, 0, head[to]));
        head[to] = edges.size() - 1;
    }

    ll computeMaxFlow() {
        ll ans = 0;
        while(bfs()) {
            iter = head;
            ll res;
            while ((res = dfs(S, LINF))) {
                ans += res;
            }
        }
        return ans;
    }

    // 二分圖匹配
    vector<pair<int, int>> getBipartite(int m) {
        vector<pair<int, int>> res;
        for (int u = 1; u <= m; u++) {
            for (int i = head[u]; i != -1; i = edges[i].next) {
                int v = edges[i].to;
                if (v != S && edges[i].cap == 0) {
                    res.push_back({u, v});
                    break;
                }
            }
        }
        return res;
    }
};