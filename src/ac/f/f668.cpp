#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        vector<vector<int>> adj(N + 1);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        for (int i = 1; i <= N; ++i) {
            sort(adj[i].begin(), adj[i].end());
            cout << i << ":";
            for (size_t j = 0; j < adj[i].size(); ++j) {
                cout << " " << adj[i][j];
            }
            cout << "\n";
        }
    }
    
    return 0;
}
