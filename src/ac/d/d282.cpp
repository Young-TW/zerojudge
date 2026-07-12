#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    int case_num = 1;
    
    while (cin >> N >> M && N) {
        vector<string> names(N);
        for (int i = 0; i < N; ++i) {
            cin >> names[i];
        }
        
        vector<vector<int>> dist(N, vector<int>(N, INF));
        for (int i = 0; i < N; ++i) {
            dist[i][i] = 0;
        }
        
        for (int i = 0; i < M; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            --u;
            --v;
            if (w < dist[u][v]) {
                dist[u][v] = w;
                dist[v][u] = w;
            }
        }
        
        for (int k = 0; k < N; ++k) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        if (dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                    }
                }
            }
        }
        
        int min_sum = INF;
        int best_idx = 0;
        
        for (int i = 0; i < N; ++i) {
            int current_sum = 0;
            for (int j = 0; j < N; ++j) {
                if (dist[i][j] == INF) {
                    current_sum = INF;
                    break;
                }
                current_sum += dist[i][j];
            }
            if (current_sum < min_sum) {
                min_sum = current_sum;
                best_idx = i;
            }
        }
        
        cout << "Case #" << case_num << " : " << names[best_idx] << "\n";
        case_num++;
    }
    
    return 0;
}
