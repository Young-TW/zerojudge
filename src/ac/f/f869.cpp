#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M, W, S;
    cin >> N >> M >> W >> S;
    S--; // 0-indexed
    
    vector<vector<int>> adj(N, vector<int>(N, INT_MAX));
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        adj[a][b] = min(adj[a][b], c);
        adj[b][a] = min(adj[b][a], c);
    }
    
    vector<vector<int>> deps(N);
    for (int i = 0; i < W; i++) {
        int k, l;
        cin >> k >> l;
        k--; l--;
        deps[l].push_back(k);
    }
    
    // Modified Prim's algorithm
    vector<bool> in_tree(N, false);
    in_tree[S] = true;
    vector<int> parent(N, -1);
    int total_cost = 0;
    
    for (int iter = 0; iter < N - 1; iter++) {
        int best_cost = INT_MAX;
        int best_v = -1;
        int best_u = -1;
        
        for (int v = 0; v < N; v++) {
            if (in_tree[v]) continue;
            // Check dependencies
            bool ok = true;
            for (int d : deps[v]) {
                if (!in_tree[d]) {
                    ok = false;
                    break;
                }
            }
            if (!ok) continue;
            
            // Find minimum edge from v to tree
            for (int u = 0; u < N; u++) {
                if (in_tree[u] && adj[v][u] < INT_MAX) {
                    if (adj[v][u] < best_cost ||
                        (adj[v][u] == best_cost && v > best_v) ||
                        (adj[v][u] == best_cost && v == best_v && u > best_u)) {
                        best_cost = adj[v][u];
                        best_v = v;
                        best_u = u;
                    }
                }
            }
        }
        
        in_tree[best_v] = true;
        parent[best_v] = best_u;
        total_cost += best_cost;
    }
    
    // Output
    vector<pair<int,int>> edges;
    for (int v = 0; v < N; v++) {
        if (v == S) continue;
        int u = parent[v];
        edges.push_back({u + 1, v + 1}); // 1-indexed, (parent, child)
    }
    sort(edges.begin(), edges.end());
    
    cout << total_cost << "\n";
    for (auto& e : edges) {
        cout << e.first << " " << e.second << "\n";
    }
    
    return 0;
}
