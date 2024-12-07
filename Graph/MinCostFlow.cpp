#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll LINF = 0x3f3f3f3f3f3f3f3f;

class MinCostFlow {
private:
    struct Edge {
        int to, next;
        ll cap, cost;

        Edge(int to, ll cap, ll cost, int next) : to(to), cap(cap), cost(cost), next(next) {}
    };

    int n, S, T;
    vector<Edge> edges;
    vector<int> head, prevNode, prevEdge;
    vector<ll> dist, flow, h; 

    void spfa() {
        ranges::fill(h, LINF);
        h[S] = 0;

        vector<bool> inq(n + 1, false);
        inq[S] = true;
        queue<int> q;
        q.push(S);
        while (!q.empty()) {
            int curr = q.front(); q.pop();
            inq[curr] = false;

            for (int i = head[curr]; i != -1; i = edges[i].next) {
                int next = edges[i].to;
                if (edges[i].cap && h[next] > h[curr] + edges[i].cost) {
                    h[next] = h[curr] + edges[i].cost;
                    if (!inq[next]) {
                        inq[next] = true;
                        q.push(next);
                    }
                }
            }
        }
    }

    bool dijkstra() {
        ranges::fill(dist, LINF);
        ranges::fill(flow, LINF);
        ranges::fill(prevNode, -1);
        ranges::fill(prevEdge, -1);
        dist[S] = 0;

        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        pq.push({0, S});    // dist, idx
        while (!pq.empty()) {
            auto [d, curr] = pq.top(); pq.pop();
            if (d > dist[curr]) continue;

            for (int i = head[curr]; i != -1; i = edges[i].next) {
                int next = edges[i].to;
                ll newCost = dist[curr] + edges[i].cost + (h[curr] - h[next]);
                if (edges[i].cap && dist[next] > newCost) {
                    dist[next] = newCost;
                    flow[next] = min(flow[curr], edges[i].cap);
                    prevNode[next] = curr;
                    prevEdge[next] = i;
                    pq.push({dist[next], next});
                }
            }
        }
        return dist[T] != LINF;
    }

public:
    MinCostFlow(int n, int S, int T) : n(n), S(S), T(T),
        head(n + 1, -1), prevNode(n + 1, -1), prevEdge(n + 1, -1), 
        dist(n + 1, LINF), flow(n + 1, LINF), h(n + 1, LINF) {}
    
    void addEdge(int from, int to, ll cap, ll cost) {
        edges.push_back(Edge(to, cap, cost, head[from]));
        head[from] = edges.size() - 1;
        edges.push_back(Edge(from, 0, -cost, head[to]));
        head[to] = edges.size() - 1;
    }

    // (minCost, maxFlow)
    pair<ll, ll> computeMinCostFlow() {
        spfa(); // init h

        ll minCost = 0, maxFlow = 0;
        while (dijkstra()) {
            ll f = flow[T];
            minCost += f * (dist[T] - (h[S] - h[T]));
            maxFlow += f;

            for (int i = T; i != S; i = prevNode[i]) {
                edges[prevEdge[i]].cap -= f;
                edges[prevEdge[i] ^ 1].cap += f;
            }

            for (int i = 0; i <= n; i++) {
                if (dist[i] != LINF) {
                    h[i] += dist[i];
                }
            }
        }
        return {minCost, maxFlow};
    }
};