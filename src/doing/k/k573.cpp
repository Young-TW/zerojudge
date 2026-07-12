#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M, K, Q;
    while (cin >> N >> M >> K >> Q) {
        vector<vector<int>> adj(N);
        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        vector<long long> antibody(N, 0);
        
        for (int q = 0; q < Q; q++) {
            int a;
            long long b;
            cin >> a >> b;
            
            vector<int> dist(N, -1);
            queue<int> bfs;
            bfs.push(a);
            dist[a] = 0;
            
            int count = 0;
            while (!bfs.empty()) {
                int u = bfs.front();
                bfs.pop();
                
                if (antibody[u] < b) {
                    antibody[u] = b;
                    count++;
                }
                
                if (dist[u] < K) {
                    for (int v : adj[u]) {
                        if (dist[v] == -1) {
                            dist[v] = dist[u] + 1;
                            bfs.push(v);
                        }
                    }
                }
            }
            
            cout << count << "\n";
        }
    }
    
    return 0;
}
