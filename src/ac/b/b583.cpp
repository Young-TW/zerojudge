#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (cin >> T) {
        while (T--) {
            int V, E;
            cin >> V >> E;
            
            vector<vector<int>> graph(V + 1);
            vector<int> in_degree(V + 1, 0);
            
            for (int i = 0; i < E; ++i) {
                int a, b;
                cin >> a >> b;
                graph[a].push_back(b);
                in_degree[b]++;
            }
            
            queue<int> q;
            for (int i = 1; i <= V; ++i) {
                if (in_degree[i] == 0) {
                    q.push(i);
                }
            }
            
            int count = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                count++;
                
                for (int v : graph[u]) {
                    in_degree[v]--;
                    if (in_degree[v] == 0) {
                        q.push(v);
                    }
                }
            }
            
            if (count == V) {
                cout << "W+W\n";
            } else {
                cout << "O______O\n";
            }
        }
    }
    
    return 0;
}
