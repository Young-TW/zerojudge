#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int vis[MAXN];
int dist[MAXN];
int token = 0;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        token++;
        for (int i = 0; i < MAXN; ++i) {
            adj[i].clear();
        }
        int s_u, s_v, t_u, t_v;
        cin >> s_u >> s_v;
        cin >> t_u >> t_v;
        for (int i = 2; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        if (s_u == t_u || s_u == t_v || s_v == t_u || s_v == t_v) {
            cout << 0 << "\n";
            continue;
        }
        
        queue<int> q;
        vis[s_u] = token;
        dist[s_u] = 0;
        q.push(s_u);
        if (s_v != s_u) {
            vis[s_v] = token;
            dist[s_v] = 0;
            q.push(s_v);
        }
        
        int ans = -1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (vis[v] != token) {
                    vis[v] = token;
                    dist[v] = dist[u] + 1;
                    if (v == t_u || v == t_v) {
                        ans = dist[v];
                        break;
                    }
                    q.push(v);
                }
            }
            if (ans != -1) break;
        }
        cout << ans << "\n";
    }
    return 0;
}
