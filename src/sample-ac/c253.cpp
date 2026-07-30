#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;
    DSU(int n = 0) { init(n); }
    void init(int n) { p.resize(n); sz.assign(n, 1); iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int V, E, T, tc = 1;
    while (cin >> V >> E >> T) {
        if (!V && !E && !T) break;
        DSU dsu(V);
        vector<int> deg(V, 0);
        for (int i = 0, a, b; i < E; ++i) {
            cin >> a >> b; --a; --b;
            ++deg[a]; ++deg[b];
            dsu.unite(a, b);
        }
        vector<int> compSize(V, 0), oddCnt(V, 0);
        for (int i = 0; i < V; ++i) if (deg[i]) {
            int r = dsu.find(i);
            ++compSize[r];
            if (deg[i] & 1) ++oddCnt[r];
        }
        int C = 0, K = 0, O = 0, maxsz = 0;
        for (int i = 0; i < V; ++i) if (compSize[i]) {
            ++C;
            O += oddCnt[i];
            if (oddCnt[i]) ++K;
            maxsz = max(maxsz, compSize[i]);
        }
        long long added = 0;
        if (C) {
            added = C - 1;
            if (K) {
                int restOdd = O - 2 * (K - 1);
                if (restOdd > 2) added += restOdd / 2 - 1;
            }
        }
        long long ans = 1LL * E * T + added * 100;
        cout << "Case " << tc++ << ": " << ans << "\n" << maxsz << "\n";
    }
    return 0;
}
