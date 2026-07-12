#include <iostream>

using namespace std;

int parent[15];

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void unite(int x, int y) {
    int rx = find(x);
    int ry = find(y);
    if (rx != ry) {
        parent[rx] = ry;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    while (cin >> N >> M) {
        for (int i = 1; i <= N; ++i) {
            parent[i] = i;
        }
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            unite(u, v);
        }
        int components = 0;
        for (int i = 1; i <= N; ++i) {
            if (find(i) == i) {
                components++;
            }
        }
        cout << components << "\n";
    }
    return 0;
}
