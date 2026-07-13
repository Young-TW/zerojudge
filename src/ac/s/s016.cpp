#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<vector<int>> adj(n + 1);
        vector<int> deg(n + 1, 0);
        
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
            deg[u]++;
            deg[v]++;
        }
        
        vector<bool> is_leaf(n + 1, false);
        for (int i = 1; i <= n; ++i) {
            if (deg[i] == 1) {
                is_leaf[i] = true;
            }
        }
        
        bool is_caterpillar = true;
        for (int i = 1; i <= n; ++i) {
            if (!is_leaf[i]) {
                int non_leaf_deg = 0;
                for (int neighbor : adj[i]) {
                    if (!is_leaf[neighbor]) {
                        non_leaf_deg++;
                    }
                }
                if (non_leaf_deg > 2) {
                    is_caterpillar = false;
                    break;
                }
            }
        }
        
        if (is_caterpillar) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    
    return 0;
}
