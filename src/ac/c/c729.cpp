#include <bits/stdc++.h>
using namespace std;

/*** Hopcroft–Karp for bipartite matching (left size = right size = N) ***/
struct HopcroftKarp {
    int n;                              // number of vertices on each side
    vector<vector<int>> adj;           // edges from left to right
    vector<int> dist, matchL, matchR;

    HopcroftKarp(int n = 0) { init(n); }

    void init(int n_) {
        n = n_;
        adj.assign(n, {});
        matchL.assign(n, -1);
        matchR.assign(n, -1);
        dist.resize(n);
    }

    void addEdge(int u, int v) {        // u in [0,n), v in [0,n)
        adj[u].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (matchL[i] == -1) {
                dist[i] = 0;
                q.push(i);
            } else {
                dist[i] = -1;
            }
        }
        bool foundFree = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                int nxt = matchR[v];
                if (nxt != -1 && dist[nxt] == -1) {
                    dist[nxt] = dist[u] + 1;
                    q.push(nxt);
                }
                if (nxt == -1) foundFree = true;
            }
        }
        return foundFree;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            int nxt = matchR[v];
            if (nxt == -1 || (dist[nxt] == dist[u] + 1 && dfs(nxt))) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int maxMatching() {
        int matching = 0;
        while (bfs()) {
            for (int i = 0; i < n; ++i)
                if (matchL[i] == -1 && dfs(i))
                    ++matching;
        }
        return matching;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, R, C;
    while (cin >> n >> m >> R >> C) {
        vector<string> g(n);
        for (int i = 0; i < n; ++i) cin >> g[i];

        vector<vector<int>> id(n, vector<int>(m, -1));
        int V = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (g[i][j] == '.')
                    id[i][j] = V++;

        HopcroftKarp hk(V);
        const int dr[4] = {R, R, C, C};
        const int dc[4] = {C, -C, R, -R};

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) if (id[i][j] != -1) {
                int u = id[i][j];
                for (int k = 0; k < 4; ++k) {
                    int ni = i + dr[k];
                    int nj = j + dc[k];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m && id[ni][nj] != -1) {
                        int v = id[ni][nj];
                        hk.addEdge(u, v);
                    }
                }
            }
        }

        int matching = hk.maxMatching();
        int answer = V - matching;
        cout << answer << '\n';
    }
    return 0;
}
