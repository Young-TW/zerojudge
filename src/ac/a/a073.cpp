#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct DSU {
    vector<int> parent, sz;
    DSU(int n) {
        parent.resize(n);
        sz.resize(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        parent[y] = x;
        sz[x] += sz[y];
        return true;
    }
};

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, Q;
    while (cin >> N >> M >> Q) {
        vector<Edge> edges(M);
        for (int i = 0; i < M; ++i) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
            edges[i].u--;
            edges[i].v--;
        }
        sort(edges.begin(), edges.end());
        
        DSU dsu(N);
        vector<pair<int, long long>> events;
        for (int i = 0; i < M; ++i) {
            int u = edges[i].u, v = edges[i].v, w = edges[i].w;
            int root_u = dsu.find(u);
            int root_v = dsu.find(v);
            if (root_u != root_v) {
                long long pairs = (long long)dsu.sz[root_u] * dsu.sz[root_v];
                events.push_back({w, pairs});
                dsu.unite(u, v);
            }
        }
        
        vector<int> weights;
        vector<long long> sums;
        weights.push_back(-1);
        sums.push_back(0);
        long long current_sum = 0;
        for (const auto& e : events) {
            current_sum += e.second;
            if (weights.back() == e.first) {
                sums.back() = current_sum;
            } else {
                weights.push_back(e.first);
                sums.push_back(current_sum);
            }
        }
        
        for (int i = 0; i < Q; ++i) {
            int A;
            cin >> A;
            int idx = upper_bound(weights.begin(), weights.end(), A) - weights.begin() - 1;
            cout << sums[idx] << "\n";
        }
    }
    return 0;
}
