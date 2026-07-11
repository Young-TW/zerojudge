#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class DSU {
public:
    vector<int> parent;
    vector<int> rank_;
    int components;

    DSU(int n) {
        parent.resize(n + 1);
        rank_.resize(n + 1, 0);
        components = n;
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (rank_[root_i] < rank_[root_j]) {
                parent[root_i] = root_j;
            } else if (rank_[root_i] > rank_[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank_[root_i]++;
            }
            components--;
            return true;
        }
        return false;
    }
};

struct Edge {
    int u, v, c;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, K;
    while (cin >> N >> M >> K) {
        vector<Edge> edges(M);
        for (int i = 0; i < M; ++i) {
            cin >> edges[i].u >> edges[i].v >> edges[i].c;
        }

        // Calculate min_0
        DSU dsu_min(N);
        int min_0 = 0;
        for (const auto& e : edges) {
            if (e.c == 1) {
                dsu_min.unite(e.u, e.v);
            }
        }
        for (const auto& e : edges) {
            if (e.c == 0) {
                if (dsu_min.unite(e.u, e.v)) {
                    min_0++;
                }
            }
        }
        if (dsu_min.components != 1) {
            cout << "no solution\n";
            continue;
        }

        // Calculate max_0
        DSU dsu_max(N);
        int max_0 = 0;
        for (const auto& e : edges) {
            if (e.c == 0) {
                if (dsu_max.unite(e.u, e.v)) {
                    max_0++;
                }
            }
        }
        for (const auto& e : edges) {
            if (e.c == 1) {
                dsu_max.unite(e.u, e.v);
            }
        }
        if (dsu_max.components != 1) {
            cout << "no solution\n";
            continue;
        }

        if (K >= min_0 && K <= max_0) {
            cout << "yes\n";
        } else {
            cout << "no solution\n";
        }
    }

    return 0;
}
