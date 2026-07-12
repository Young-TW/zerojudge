#include <iostream>
#include <vector>
#include <queue>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    while (std::cin >> n && n) {
        int m;
        std::cin >> m;
        std::vector<std::vector<int>> adj(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            std::cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        std::vector<int> color(n, -1);
        bool is_bicolorable = true;
        
        for (int i = 0; i < n && is_bicolorable; ++i) {
            if (color[i] == -1) {
                std::queue<int> q;
                q.push(i);
                color[i] = 0;
                
                while (!q.empty() && is_bicolorable) {
                    int u = q.front();
                    q.pop();
                    
                    for (int v : adj[u]) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            q.push(v);
                        } else if (color[v] == color[u]) {
                            is_bicolorable = false;
                            break;
                        }
                    }
                }
            }
        }
        
        if (is_bicolorable) {
            std::cout << "BICOLORABLE.\n";
        } else {
            std::cout << "NOT BICOLORABLE.\n";
        }
    }
    
    return 0;
}
