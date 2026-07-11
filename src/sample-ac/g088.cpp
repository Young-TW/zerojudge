#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 10;
int n, m;
vector<int> adj[MAXN];
int parent[MAXN];
int rank_[MAXN];

int find(int u) {
    if (parent[u] != u) {
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

void union_set(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return;
    if (rank_[u] < rank_[v]) {
        parent[u] = v;
    } else {
        parent[v] = u;
        if (rank_[u] == rank_[v]) {
            rank_[u]++;
        }
    }
}

int kirchoff() {
    int mat[MAXN][MAXN];
    memset(mat, 0, sizeof(mat));

    for (int i = 0; i < n; i++) {
        for (int j : adj[i]) {
            if (j > i) {
                mat[i][j]--;
                mat[j][i]--;
                mat[i][i]++;
                mat[j][j]++;
            }
        }
    }

    int size = n - 1;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            while (mat[j][i] != 0) {
                int ratio = mat[i][i] / mat[j][i];
                for (int k = i; k < size; k++) {
                    mat[i][k] = (mat[i][k] - mat[j][k] * ratio);
                }
                for (int k = i; k < size; k++) {
                    swap(mat[i][k], mat[j][k]);
                }
            }
        }
    }

    int det = 1;
    for (int i = 0; i < size; i++) {
        det *= mat[i][i];
    }
    return abs(det);
}

int main() {
    while (cin >> n >> m) {
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        int components = 0;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank_[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            for (int j : adj[i]) {
                if (j > i) {
                    union_set(i, j);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (find(i) == i) {
                components++;
            }
        }

        if (components > 1) {
            cout << 0 << endl;
        } else {
            cout << kirchoff() << endl;
        }
    }
    return 0;
}
