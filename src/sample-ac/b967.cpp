#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

pair<int, int> bfs(int start, const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> dist(n, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    int max_dist = 0;
    int farthest_node = start;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                if (dist[v] > max_dist) {
                    max_dist = dist[v];
                    farthest_node = v;
                }
            }
        }
    }
    return make_pair(max_dist, farthest_node);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<vector<int>> adj(N);
        for (int i = 0; i < N - 1; ++i) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        
        if (N <= 1) {
            cout << 0 << "\n";
            continue;
        }
        
        pair<int, int> p1 = bfs(0, adj);
        pair<int, int> p2 = bfs(p1.second, adj);
        cout << p2.first << "\n";
    }
    
    return 0;
}
