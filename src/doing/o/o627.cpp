#include <iostream>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent, sz;
    DSU(int n) : parent(n + 1), sz(n + 1, 1) {
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, m;
    while (cin >> n >> m) {
        DSU dsu(n);
        for (long long i = 0; i < m; ++i) {
            long long u, v;
            cin >> u >> v;
            dsu.unite(u, v);
        }
        vector<int> seen(n + 1, 0);
        int c = 0;
        for (int i = 1; i <= n; ++i) {
            int root = dsu.find(i);
            if (!seen[root]) {
                seen[root] = 1;
                ++c;
            }
        }
        long long cyclomatic = m - n + c;
        if (cyclomatic == 0) cout << 0 << "\n";
        else if (cyclomatic == 1) cout << 1 << "\n";
        else cout << -1 << "\n";
    }
    return 0;
}
