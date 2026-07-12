#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w > other.w;
    }
};

int parent[20005];

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        parent[root_i] = root_j;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int K;
    while (cin >> K) {
        while (K--) {
            int N, M, R;
            cin >> N >> M >> R;
            for (int i = 0; i < N + M; ++i) {
                parent[i] = i;
            }
            vector<Edge> edges(R);
            for (int i = 0; i < R; ++i) {
                int x, y, d;
                cin >> x >> y >> d;
                edges[i].u = x;
                edges[i].v = N + y;
                edges[i].w = d;
            }
            sort(edges.begin(), edges.end());
            
            long long total_discount = 0;
            for (int i = 0; i < R; ++i) {
                if (find(edges[i].u) != find(edges[i].v)) {
                    unite(edges[i].u, edges[i].v);
                    total_discount += edges[i].w;
                }
            }
            
            long long total_cost = 10000LL * (N + M) - total_discount;
            cout << total_cost << "\n";
        }
    }
    return 0;
}
