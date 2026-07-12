#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int P, R;
    int network_num = 1;
    while (cin >> P >> R) {
        if (P == 0 && R == 0) break;
        
        map<string, int> name_to_id;
        vector<pair<string, string>> edges;
        
        for (int i = 0; i < R; ++i) {
            string u, v;
            cin >> u >> v;
            edges.push_back({u, v});
            if (name_to_id.find(u) == name_to_id.end()) {
                name_to_id[u] = name_to_id.size();
            }
            if (name_to_id.find(v) == name_to_id.end()) {
                name_to_id[v] = name_to_id.size();
            }
        }
        
        int actual_P = name_to_id.size();
        int N = max(P, actual_P);
        
        const int INF = 1e9;
        vector<vector<int>> dist(N, vector<int>(N, INF));
        for (int i = 0; i < N; ++i) {
            dist[i][i] = 0;
        }
        
        for (const auto& edge : edges) {
            int u = name_to_id[edge.first];
            int v = name_to_id[edge.second];
            dist[u][v] = 1;
            dist[v][u] = 1;
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
        
        int max_dist = 0;
        bool disconnected = false;
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (dist[i][j] == INF) {
                    disconnected = true;
                    break;
                }
                if (dist[i][j] > max_dist) {
                    max_dist = dist[i][j];
                }
            }
            if (disconnected) break;
        }
        
        cout << "Network " << network_num << ": ";
        if (disconnected) {
            cout << "DISCONNECTED\n";
        } else {
            cout << max_dist << "\n";
        }
        cout << "\n";
        
        network_num++;
    }
    
    return 0;
}
