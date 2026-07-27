#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

struct Edge {
    int u, v;
    int w;
};

struct DSU {
    vector<int> p, r;
    DSU(int n = 0) { init(n); }
    void init(int n) {
        p.resize(n);
        r.assign(n, 0);
        for (int i = 0; i < n; ++i) p[i] = i;
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) ++r[a];
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while (cin >> N >> M) {
        int K;
        if (!(cin >> K)) break;
        vector<int> special(K);
        for (int i = 0; i < K; ++i) cin >> special[i];

        vector<Edge> edges;
        edges.reserve(static_cast<size_t>(M) + K);
        for (int i = 0; i < M; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            edges.push_back({a, b, c});
        }
        for (int s : special) {
            edges.push_back({0, s, 0});          // zero‑weight edges to super source
        }

        sort(edges.begin(), edges.end(),
             [](const Edge& x, const Edge& y) { return x.w < y.w; });

        DSU dsu(N + 1);                         // vertices 0 … N
        long long total = 0;
        for (const auto& e : edges) {
            if (dsu.unite(e.u, e.v))
                total += e.w;
        }
        cout << total << '\n';
    }
    return 0;
}
