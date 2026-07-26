#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
    int nLeft, nRight;
    vector<vector<int>> adj;          // from left (0..nLeft-1) to right (global id)
    vector<int> dist, pairU, pairV;   // pairU[left] = right id or -1, pairV[right] = left id or -1

    HopcroftKarp(int L, int R) : nLeft(L), nRight(R) {
        adj.assign(nLeft, {});
        pairU.assign(nLeft, -1);
        pairV.assign(nRight, -1);
        dist.resize(nLeft);
    }

    void addEdge(int uLeft, int vRight) { adj[uLeft].push_back(vRight); }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < nLeft; ++u) {
            if (pairU[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else dist[u] = -1;
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                int pu = pairV[v];
                if (pu != -1 && dist[pu] == -1) {
                    dist[pu] = dist[u] + 1;
                    q.push(pu);
                }
                if (pu == -1) found = true;
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            int pu = pairV[v];
            if (pu == -1 || (dist[pu] == dist[u] + 1 && dfs(pu))) {
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    const int dx[4] = {-1, 0, 1, 0};   // 1: up, 2: right, 3: down, 4: left
    const int dy[4] = {0, 1, 0, -1};
    while ( (cin >> N >> M) ) {
        // blocked[x][y][dir]  (0‑based)
        vector<array<char,4>> blocked(N * N);
        for (auto &a : blocked) a.fill(0);
        for (int i = 0; i < M; ++i) {
            int x, y, k;
            cin >> x >> y >> k;
            --x; --y; --k;               // to 0‑based, k in [0,3]
            blocked[x * N + y][k] = 1;
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (0 <= nx && nx < N && 0 <= ny && ny < N) {
                int opp = (k + 2) % 4;   // opposite direction
                blocked[nx * N + ny][opp] = 1;
            }
        }

        int V = N * N;
        if (V % 2 == 1) {
            cout << "Kevin you cheat !\n\n";
            continue;
        }

        // left side = cells with (x+y) even
        vector<int> leftId(V, -1);
        int leftCnt = 0;
        for (int x = 0; x < N; ++x)
            for (int y = 0; y < N; ++y)
                if ( ((x + y) & 1) == 0 )
                    leftId[x * N + y] = leftCnt++;

        HopcroftKarp hk(leftCnt, V);
        for (int x = 0; x < N; ++x) {
            for (int y = 0; y < N; ++y) {
                int id = x * N + y;
                if ( ((x + y) & 1) != 0 ) continue; // only left side
                int u = leftId[id];
                for (int d = 0; d < 4; ++d) {
                    if (blocked[id][d]) continue;
                    int nx = x + dx[d];
                    int ny = y + dy[d];
                    if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                    int nid = nx * N + ny;
                    hk.addEdge(u, nid); // nid is a right‑side vertex (global id)
                }
            }
        }

        int match = hk.maxMatching();
        if (match * 2 == V)
            cout << "I win !\n\n";
        else
            cout << "Kevin you cheat !\n\n";
    }
    return 0;
}
