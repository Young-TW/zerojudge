#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 1e9;
int dist[105][105][105];

struct Edge {
    int u, v, w;
};

Edge edges[10005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, Q;
    while (cin >> n >> m >> Q) {
        for (int i = 0; i < m; ++i) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }
        
        for (int x = 0; x < n; ++x) {
            auto& d = dist[x];
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    d[i][j] = INF;
                }
                d[i][i] = 0;
            }
            
            for (int i = 0; i < m; ++i) {
                int u = edges[i].u;
                int v = edges[i].v;
                int w = edges[i].w;
                if (u != x && v != x) {
                    d[u][v] = min(d[u][v], w);
                }
            }
            
            for (int k = 0; k < n; ++k) {
                if (k == x) continue;
                for (int i = 0; i < n; ++i) {
                    if (i == x) continue;
                    int dik = d[i][k];
                    if (dik >= INF) continue;
                    for (int j = 0; j < n; ++j) {
                        if (j == x) continue;
                        if (dik + d[k][j] < d[i][j]) {
                            d[i][j] = dik + d[k][j];
                        }
                    }
                }
            }
        }
        
        for (int q = 0; q < Q; ++q) {
            int x, u, v;
            cin >> x >> u >> v;
            if (dist[x][u][v] >= INF / 2) {
                cout << -1 << "\n";
            } else {
                cout << dist[x][u][v] << "\n";
            }
        }
    }
    
    return 0;
}
