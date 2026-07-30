#include <bits/stdc++.h>
using namespace std;

/*** Hopcroft‑Karp for bipartite matching ***/
struct HopcroftKarp {
    int nLeft, nRight;
    vector<vector<int>> adj;          // edges from left (0..nLeft-1) to right
    vector<int> dist, pairU, pairV;   // pairU[u] = matched v or -1

    HopcroftKarp(int L, int R) : nLeft(L), nRight(R) {
        adj.assign(nLeft, {});
        pairU.assign(nLeft, -1);
        pairV.assign(nRight, -1);
        dist.resize(nLeft);
    }

    void addEdge(int u, int v) {      // u in left, v in right
        adj[u].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < nLeft; ++u) {
            if (pairU[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = -1;
            }
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                int u2 = pairV[v];
                if (u2 != -1 && dist[u2] == -1) {
                    dist[u2] = dist[u] + 1;
                    q.push(u2);
                }
                if (u2 == -1) found = true;
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            int u2 = pairV[v];
            if (u2 == -1 || (dist[u2] == dist[u] + 1 && dfs(u2))) {
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int maxMatching() {
        int matching = 0;
        while (bfs()) {
            for (int u = 0; u < nLeft; ++u)
                if (pairU[u] == -1 && dfs(u))
                    ++matching;
        }
        return matching;
    }
};

/*** Main ***/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    for (int tc = 1; tc <= T; ++tc) {
        int M, N;
        cin >> M >> N;
        vector<string> g(M);
        for (int i = 0; i < M; ++i) cin >> g[i];

        vector<vector<int>> idL(M, vector<int>(N, -1));
        vector<vector<int>> idR(M, vector<int>(N, -1));
        int cntL = 0, cntR = 0, total = 0;

        for (int r = 0; r < M; ++r) {
            for (int c = 0; c < N; ++c) {
                if (g[r][c] != '.') continue;
                ++total;
                if (c % 2 == 0) idL[r][c] = cntL++;
                else            idR[r][c] = cntR++;
            }
        }

        HopcroftKarp hk(cntL, cntR);
        const int dr[6] = {0, 0, -1, -1, 1, 1};
        const int dc[6] = {-1, 1, -1, 1, -1, 1};

        for (int r = 0; r < M; ++r) {
            for (int c = 0; c < N; ++c) {
                if (c % 2 != 0) continue;               // only left side (even columns)
                if (g[r][c] != '.') continue;
                int u = idL[r][c];
                for (int k = 0; k < 6; ++k) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if (nr < 0 || nr >= M || nc < 0 || nc >= N) continue;
                    if (g[nr][nc] != '.') continue;
                    int v = idR[nr][nc];
                    if (v != -1) hk.addEdge(u, v);
                }
            }
        }

        int matching = hk.maxMatching();
        int answer = total - matching;
        cout << "Case #" << tc << ": " << answer << "\n";
    }
    return 0;
}
