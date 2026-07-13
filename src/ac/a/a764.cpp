#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 405;
const long long INF = 1e18;

long long dist[MAXN][MAXN];
long long edge[MAXN][MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    while (cin >> N >> M) {
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                dist[i][j] = INF;
                edge[i][j] = INF;
            }
            dist[i][i] = 0;
        }

        for (int i = 0; i < M; ++i) {
            int u, v;
            long long w;
            cin >> u >> v >> w;
            if (u == v) continue;
            if (w < edge[u][v]) {
                edge[u][v] = w;
                edge[v][u] = w;
                dist[u][v] = w;
                dist[v][u] = w;
            }
        }

        long long ans = INF;

        for (int k = 1; k <= N; ++k) {
            for (int i = 1; i < k; ++i) {
                if (edge[i][k] == INF) continue;
                for (int j = i + 1; j < k; ++j) {
                    if (edge[k][j] == INF || dist[i][j] == INF) continue;
                    long long cycle_len = dist[i][j] + edge[i][k] + edge[k][j];
                    if (cycle_len < ans) {
                        ans = cycle_len;
                    }
                }
            }
            for (int i = 1; i <= N; ++i) {
                if (dist[i][k] == INF) continue;
                for (int j = 1; j <= N; ++j) {
                    if (dist[k][j] == INF) continue;
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        if (ans == INF) {
            cout << "No solution.\n";
        } else {
            cout << ans << "\n";
        }
    }

    return 0;
}
