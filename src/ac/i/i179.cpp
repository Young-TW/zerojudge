#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int M, N, T;
vector<vector<int>> adj;
vector<int> pairU, pairV, dist;

bool bfs() {
    queue<int> q;
    for (int u = 0; u < M; ++u) {
        if (pairU[u] == M) {
            dist[u] = 0;
            q.push(u);
        } else {
            dist[u] = INF;
        }
    }
    dist[M] = INF;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (dist[u] < dist[M]) {
            for (int v : adj[u]) {
                if (dist[pairV[v]] == INF) {
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
    }
    return dist[M] != INF;
}

bool dfs(int u) {
    if (u != M) {
        for (int v : adj[u]) {
            if (dist[pairV[v]] == dist[u] + 1) {
                if (dfs(pairV[v])) {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> M >> N >> T) {
        vector<vector<bool>> edge(M, vector<bool>(N, false));
        for (int i = 0; i < T; ++i) {
            int r, c;
            cin >> r >> c;
            if (r >= 0 && r < M && c >= 0 && c < N) {
                edge[r][c] = true;
            }
        }

        adj.assign(M, vector<int>());
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (edge[i][j]) {
                    adj[i].push_back(j);
                }
            }
        }

        pairU.assign(M, M);
        pairV.assign(N, M);
        dist.assign(M + 1, 0);

        int matching = 0;
        while (bfs()) {
            for (int u = 0; u < M; ++u) {
                if (pairU[u] == M) {
                    if (dfs(u)) {
                        matching++;
                    }
                }
            }
        }

        cout << M + N - matching << "\n";
    }

    return 0;
}
