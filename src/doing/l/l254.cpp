#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    long long weight;
};

vector<vector<Edge>> adj;
long long nim_sum = 0;

void dfs(int u, int p) {
    for (const auto& edge : adj[u]) {
        int v = edge.to;
        long long w = edge.weight;
        if (v == p) continue;
        
        dfs(v, u);
        
        if (w % 2 == 1) {
            nim_sum ^= 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        adj.assign(N + 1, vector<Edge>());
        
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            long long w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        nim_sum = 0;
        dfs(1, -1);
        
        if (nim_sum != 0) {
            cout << "First" << "\n";
        } else {
            cout << "Second" << "\n";
        }
        
        adj.clear();
    }
    
    return 0;
}
