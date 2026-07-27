#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
    int nLeft, nRight;                     // |X| , |Y|
    vector<vector<int>> adj;               // 1‑based, edges from X to Y
    vector<int> pairU, pairV, dist;        // matching and bfs distance

    HopcroftKarp(int nL, int nR) : nLeft(nL), nRight(nR) {
        adj.assign(nLeft + 1, {});
        pairU.assign(nLeft + 1, 0);
        pairV.assign(nRight + 1, 0);
        dist.resize(nLeft + 1);
    }

    void addEdge(int u, int v) {           // u in [1..nLeft], v in [1..nRight]
        adj[u].push_back(v);
    }

    bool bfs() {
        const int INF = 1e9;
        queue<int> q;
        for (int u = 1; u <= nLeft; ++u) {
            if (pairU[u] == 0) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF;
            }
        }
        bool reachableFreeRight = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                int pu = pairV[v];
                if (pu == 0) {
                    reachableFreeRight = true;          // we can reach a free right vertex
                } else if (dist[pu] == INF) {
                    dist[pu] = dist[u] + 1;
                    q.push(pu);
                }
            }
        }
        return reachableFreeRight;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            int pu = pairV[v];
            if (pu == 0 || (dist[pu] == dist[u] + 1 && dfs(pu))) {
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }
        dist[u] = 1e9;          // mark as dead end
        return false;
    }

    int maxMatching() {
        int matching = 0;
        while (bfs()) {
            for (int u = 1; u <= nLeft; ++u)
                if (pairU[u] == 0 && dfs(u))
                    ++matching;
        }
        return matching;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int p, q, k;
        cin >> p >> q >> k;
        HopcroftKarp hk(p, q);
        for (int i = 0; i < k; ++i) {
            int x, y;
            cin >> x >> y;          // indices are already 1‑based
            hk.addEdge(x, y);
        }
        int ans = hk.maxMatching(); // = minimum vertex cover size
        cout << ans << '\n';
    }
    return 0;
}
