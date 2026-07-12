#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    bool first_case = true;
    while (T--) {
        if (!first_case) {
            cout << "\n";
        }
        first_case = false;
        
        int M, N;
        cin >> M >> N;
        
        vector<int> adj[26];
        for (int i = 0; i < M; ++i) {
            string a, b;
            cin >> a >> b;
            int u = a[0] - 'A';
            int v = b[0] - 'A';
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        for (int i = 0; i < N; ++i) {
            string a, b;
            cin >> a >> b;
            int start = a[0] - 'A';
            int target = b[0] - 'A';
            
            int parent[26];
            for (int j = 0; j < 26; ++j) parent[j] = -1;
            
            queue<int> q;
            q.push(start);
            parent[start] = start;
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                
                if (u == target) break;
                
                for (int v : adj[u]) {
                    if (parent[v] == -1) {
                        parent[v] = u;
                        q.push(v);
                    }
                }
            }
            
            vector<int> path;
            int curr = target;
            while (curr != start) {
                path.push_back(curr);
                curr = parent[curr];
            }
            path.push_back(start);
            
            for (int j = path.size() - 1; j >= 0; --j) {
                cout << (char)('A' + path[j]);
            }
            cout << "\n";
        }
    }
    
    return 0;
}
