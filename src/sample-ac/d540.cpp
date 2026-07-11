#include <iostream>
#include <vector>
#include <deque>

using namespace std;

bool solve() {
    int n, m, w;
    if (!(cin >> n >> m >> w)) return false;
    
    vector<vector<pair<int, int>>> adj(n + 1);
    
    for (int i = 0; i < m; i++) {
        int u, v, val;
        cin >> u >> v >> val;
        adj[u].push_back({v, val});
        adj[v].push_back({u, val});
    }
    
    for (int i = 0; i < w; i++) {
        int u, v, val;
        cin >> u >> v >> val;
        adj[u].push_back({v, -val});
    }
    
    vector<int> dist(n + 1, 0);
    vector<int> cnt(n + 1, 0);
    vector<bool> in_queue(n + 1, true);
    deque<int> q;
    for (int i = 1; i <= n; i++) {
        q.push_back(i);
    }
    
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        in_queue[u] = false;
        
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) {
                    return true;
                }
                if (!in_queue[v]) {
                    in_queue[v] = true;
                    if (!q.empty() && dist[v] < dist[q.front()]) {
                        q.push_front(v);
                    } else {
                        q.push_back(v);
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) {
            if (solve()) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
    return 0;
}
