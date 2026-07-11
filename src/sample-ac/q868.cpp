#include <iostream>
#include <cstring>

using namespace std;

bool adj[105][105];
bool visited[105];

void dfs(int u) {
    visited[u] = true;
    for (int v = 0; v < 105; ++v) {
        if (adj[u][v] && !visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        memset(adj, false, sizeof(adj));
        memset(visited, false, sizeof(visited));
        
        for (int i = 0; i < n; ++i) {
            int a, b;
            cin >> a >> b;
            adj[a][b] = true;
        }
        
        int f, g;
        cin >> f >> g;
        
        dfs(f);
        
        if (visited[g]) {
            cout << "Yay\n";
        } else {
            cout << "Come on\n";
        }
    }
    
    return 0;
}
