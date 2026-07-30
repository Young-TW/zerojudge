#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, rank_;
    int comps;
    DSU(int n = 0) { init(n); }
    void init(int n) {
        parent.resize(n + 1);
        rank_.assign(n + 1, 0);
        for (int i = 0; i <= n; ++i) parent[i] = i;
        comps = n;
    }
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rank_[a] < rank_[b]) swap(a, b);
        parent[b] = a;
        if (rank_[a] == rank_[b]) ++rank_[a];
        --comps;
        return true;
    }
};

struct Edge {
    int u, v;
    long long w;
    bool operator<(Edge const& other) const { return w < other.w; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    long long K;
    while (cin >> N >> M >> K) {
        vector<Edge> edges;
        edges.reserve(M);
        for (int i = 0; i < M; ++i) {
            int a, b;
            long long w;
            cin >> a >> b >> w;
            if (a == b) continue;               // ignore self‑loops
            edges.push_back({a, b, w});
        }
        sort(edges.begin(), edges.end());

        DSU dsu(N);
        int w0_idx = -1;
        for (size_t i = 0; i < edges.size(); ++i) {
            dsu.unite(edges[i].u, edges[i].v);
            if (dsu.comps == 1) {
                w0_idx = static_cast<int>(i);
                break;
            }
        }

        if (w0_idx == -1) {
            cout << -1 << '\n';
            continue;
        }

        long long cnt = 0;
        long long prev = -1;
        long long answer = -1;
        for (size_t i = w0_idx; i < edges.size(); ++i) {
            if (edges[i].w != prev) {
                ++cnt;
                if (cnt == K) {
                    answer = edges[i].w;
                    break;
                }
                prev = edges[i].w;
            }
        }
        cout << answer << '\n';
    }
    return 0;
}
