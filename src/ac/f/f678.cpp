#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

int parent[1000005];

int find(int x) {
    return parent[x] == x ? x : (parent[x] = find(parent[x]));
}

bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    parent[x] = y;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    while (cin >> N >> M) {
        vector<Edge> edges(M);
        for (int i = 0; i < M; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }
        for (int i = 0; i < N; i++) {
            parent[i] = i;
        }
        sort(edges.begin(), edges.end());
        long long cost = 0;
        int edges_used = 0;
        for (int i = 0; i < M; i++) {
            if (unite(edges[i].u, edges[i].v)) {
                cost += edges[i].w;
                edges_used++;
                if (edges_used == N - 1) break;
            }
        }
        cout << cost << "\n";
    }
    return 0;
}
