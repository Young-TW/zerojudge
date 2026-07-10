#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        const long long INF = (long long)4e18;
        vector<vector<long long>> dist(n+1, vector<long long>(n+1, INF));
        vector<vector<double>> cnt(n+1, vector<double>(n+1, 0.0));
        for (int i = 1; i <= n; i++) { dist[i][i] = 0; cnt[i][i] = 1; }
        for (int i = 0; i < m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            dist[a][b] = c; dist[b][a] = c;
            cnt[a][b] = 1; cnt[b][a] = 1;
        }
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                if (i == k || dist[i][k] == INF) continue;
                for (int j = 1; j <= n; j++) {
                    if (j == k || j == i || dist[k][j] == INF) continue;
                    long long nd = dist[i][k] + dist[k][j];
                    if (nd < dist[i][j]) {
                        dist[i][j] = nd;
                        cnt[i][j] = cnt[i][k] * cnt[k][j];
                    } else if (nd == dist[i][j]) {
                        cnt[i][j] += cnt[i][k] * cnt[k][j];
                    }
                }
            }
        }
        cout << fixed << setprecision(3);
        for (int v = 1; v <= n; v++) {
            double imp = 0.0;
            for (int s = 1; s <= n; s++) {
                if (s == v) continue;
                for (int t = 1; t <= n; t++) {
                    if (t == v || t == s) continue;
                    if (dist[s][t] == INF || cnt[s][t] == 0.0) continue;
                    if (dist[s][v] + dist[v][t] == dist[s][t]) {
                        imp += (cnt[s][v] * cnt[v][t]) / cnt[s][t];
                    }
                }
            }
            cout << imp << "\n";
        }
    }
    return 0;
}
