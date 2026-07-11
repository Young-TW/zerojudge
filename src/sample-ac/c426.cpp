#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int n, e;
            if (!(cin >> n >> e)) break;
            
            vector<vector<int>> adj(n);
            for (int i = 0; i < e; ++i) {
                int u, v;
                cin >> u >> v;
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
            
            int before_max = 0;
            for (int i = 0; i < n; ++i) {
                int cnt = 0;
                for (int v : adj[i]) {
                    if (v > i) cnt++;
                }
                before_max = max(before_max, cnt);
            }
            
            vector<int> degree(n);
            for (int i = 0; i < n; ++i) {
                degree[i] = adj[i].size();
            }
            
            vector<vector<int>> buckets(n + 1);
            for (int i = 0; i < n; ++i) {
                buckets[degree[i]].push_back(i);
            }
            
            vector<bool> removed(n, false);
            int after_max = 0;
            int min_deg = 0;
            int removed_count = 0;
            
            while (removed_count < n) {
                while (min_deg <= n && buckets[min_deg].empty()) {
                    min_deg++;
                }
                
                int u = -1;
                while (!buckets[min_deg].empty()) {
                    int cur = buckets[min_deg].back();
                    buckets[min_deg].pop_back();
                    if (!removed[cur] && degree[cur] == min_deg) {
                        u = cur;
                        break;
                    }
                }
                
                if (u == -1) continue;
                
                removed[u] = true;
                removed_count++;
                after_max = max(after_max, degree[u]);
                
                for (int v : adj[u]) {
                    if (!removed[v]) {
                        degree[v]--;
                        buckets[degree[v]].push_back(v);
                        if (degree[v] < min_deg) {
                            min_deg = degree[v];
                        }
                    }
                }
            }
            
            cout << before_max << " " << after_max << "\n";
        }
    }
    
    return 0;
}
