#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class DSU {
public:
    vector<int> parent;
    vector<int> sz;
    
    DSU(int n) {
        parent.resize(n);
        sz.resize(n, 1);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return;
        if (sz[rx] < sz[ry]) {
            swap(rx, ry);
        }
        parent[ry] = rx;
        sz[rx] += sz[ry];
    }
    
    int size(int x) {
        return sz[find(x)];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        if (N == 0) {
            cout << 0 << "\n";
            continue;
        }
        DSU dsu(N);
        for (int i = 0; i < M; ++i) {
            int a, b;
            cin >> a >> b;
            dsu.unite(a, b);
        }
        cout << dsu.size(0) << "\n";
    }
    
    return 0;
}
