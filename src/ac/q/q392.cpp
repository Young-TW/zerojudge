#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    long long t;   // travelling time
    long long p;   // price
};

const long long INF = (LLONG_MAX / 4);

void dijkstra(const vector<vector<Edge>>& g,
              int src,
              vector<long long>& dist,
              vector<long long>* price = nullptr,
              bool freeOnly = false)
{
    int n = g.size() - 1;               // vertices are 1..maxId
    dist.assign(n + 1, INF);
    if (price) price->assign(n + 1, 0);
    dist[src] = 0;
    if (price) (*price)[src] = 0;

    using Node = pair<long long,int>;   // (dist, vertex)
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.emplace(0, src);

    while (!pq.empty()) {
        auto [d, v] = pq.top(); pq.pop();
        if (d != dist[v]) continue;
        for (const Edge& e : g[v]) {
            if (freeOnly && e.p != 0) continue;
            long long nd = d + e.t;
            if (nd < dist[e.to]) {
                dist[e.to] = nd;
                if (price) (*price)[e.to] = (*price)[v] + e.p;
                pq.emplace(nd, e.to);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a;
    int S, T;
    while (cin >> a >> S >> T) {
        vector<tuple<int,int,long long,long long>> edges;
        edges.reserve(a);
        int maxId = max(S, T);
        for (long long i = 0; i < a; ++i) {
            int u, v;
            long long t, p;
            cin >> u >> v >> t >> p;
            edges.emplace_back(u, v, t, p);
            maxId = max(maxId, max(u, v));
        }

        vector<vector<Edge>> g(maxId + 1);
        for (auto &e : edges) {
            int u, v; long long t, p;
            tie(u, v, t, p) = e;
            g[u].push_back({v, t, p});
            g[v].push_back({u, t, p});
        }

        vector<long long> distAll, priceAll;
        dijkstra(g, S, distAll, &priceAll, false);

        vector<long long> distFree;
        dijkstra(g, S, distFree, nullptr, true);

        long long ansTime = distAll[T];
        long long ansPrice = priceAll[T];
        long long ansFree = (distFree[T] == INF) ? -1 : distFree[T];

        cout << ansTime << ' ' << ansPrice << ' ' << ansFree << "\n";
    }
    return 0;
}
