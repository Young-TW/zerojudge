#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int C, S, Q;
    int case_num = 1;
    bool first_case = true;
    
    while (cin >> C >> S >> Q && (C || S || Q)) {
        if (!first_case) {
            cout << "\n";
        }
        first_case = false;
        
        cout << "Case #" << case_num++ << "\n";
        
        const int INF = 1e9;
        vector<vector<int>> dist(C + 1, vector<int>(C + 1, INF));
        
        for (int i = 1; i <= C; ++i) {
            dist[i][i] = 0;
        }
        
        for (int i = 0; i < S; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            if (w < dist[u][v]) {
                dist[u][v] = w;
                dist[v][u] = w;
            }
        }
        
        for (int k = 1; k <= C; ++k) {
            for (int i = 1; i <= C; ++i) {
                for (int j = 1; j <= C; ++j) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        int max_noise = max(dist[i][k], dist[k][j]);
                        if (max_noise < dist[i][j]) {
                            dist[i][j] = max_noise;
                        }
                    }
                }
            }
        }
        
        for (int i = 0; i < Q; ++i) {
            int u, v;
            cin >> u >> v;
            if (dist[u][v] == INF) {
                cout << "no path\n";
            } else {
                cout << dist[u][v] << "\n";
            }
        }
    }
    
    return 0;
}
