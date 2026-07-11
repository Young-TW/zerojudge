#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void bfs(int start, const vector<vector<int>>& adj, vector<int>& dist) {
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        for (int t = 1; t <= T; ++t) {
            int N, R;
            cin >> N >> R;
            vector<vector<int>> adj(N);
            for (int i = 0; i < R; ++i) {
                int u, v;
                cin >> u >> v;
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
            int s, d;
            cin >> s >> d;
            
            vector<int> dist_s(N, -1), dist_d(N, -1);
            bfs(s, adj, dist_s);
            bfs(d, adj, dist_d);
            
            int ans = 0;
            for (int i = 0; i < N; ++i) {
                if (dist_s[i] != -1 && dist_d[i] != -1) {
                    ans = max(ans, dist_s[i] + dist_d[i]);
                }
            }
            
            cout << "Case " << t << ": " << ans << "\n";
        }
    }
    return 0;
}
