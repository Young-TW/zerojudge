#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    while (cin >> n >> k) {
        vector<long long> bikes(n + 1);
        vector<vector<pair<int, int>>> adj(n + 1);
        
        for (int i = 1; i <= n; ++i) {
            cin >> bikes[i];
        }
        
        for (int i = 0; i < n - 1; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        vector<long long> subtree_bikes(n + 1, 0);
        vector<int> subtree_nodes(n + 1, 0);
        vector<int> parent(n + 1, 0);
        vector<int> parent_weight(n + 1, 0);
        vector<int> order;
        order.reserve(n);
        
        vector<int> stk;
        stk.push_back(1);
        parent[1] = -1;
        
        while (!stk.empty()) {
            int u = stk.back();
            stk.pop_back();
            order.push_back(u);
            for (auto& edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;
                if (v != parent[u]) {
                    parent[v] = u;
                    parent_weight[v] = w;
                    stk.push_back(v);
                }
            }
        }
        
        long long total_cost = 0;
        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];
            subtree_bikes[u] += bikes[u];
            subtree_nodes[u] += 1;
            if (parent[u] != -1) {
                int p = parent[u];
                subtree_bikes[p] += subtree_bikes[u];
                subtree_nodes[p] += subtree_nodes[u];
                long long flow = subtree_bikes[u] - (long long)subtree_nodes[u] * k;
                total_cost += (flow < 0 ? -flow : flow) * parent_weight[u];
            }
        }
        
        cout << total_cost << "\n";
    }
    
    return 0;
}
