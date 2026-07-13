#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<int> adj[5005];
bool vis[5005];
vector<int> cur_ans;
vector<int> best_ans;
int ban_u, ban_v;

void dfs(int u, int p) {
    vis[u] = true;
    cur_ans.push_back(u);
    for (int v : adj[u]) {
        if (!vis[v]) {
            if ((u == ban_u && v == ban_v) || (u == ban_v && v == ban_u)) continue;
            dfs(v, u);
        }
    }
}

void solve() {
    for (int i = 1; i <= n; ++i) {
        sort(adj[i].begin(), adj[i].end());
    }
    
    if (m == n - 1) {
        for (int i = 1; i <= n; ++i) vis[i] = false;
        cur_ans.clear();
        ban_u = ban_v = -1;
        dfs(1, 0);
        best_ans = cur_ans;
    } else {
        best_ans.clear();
        for (int i = 1; i <= n; ++i) {
            for (int v : adj[i]) {
                if (i < v) {
                    ban_u = i;
                    ban_v = v;
                    for (int j = 1; j <= n; ++j) vis[j] = false;
                    cur_ans.clear();
                    dfs(1, 0);
                    if (cur_ans.size() == n) {
                        if (best_ans.empty() || cur_ans < best_ans) {
                            best_ans = cur_ans;
                        }
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < n; ++i) {
        cout << best_ans[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    bool first_case = true;
    while (cin >> n >> m) {
        if (!first_case) cout << "\n";
        first_case = false;
        for (int i = 1; i <= n; ++i) {
            adj[i].clear();
        }
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        solve();
    }
    return 0;
}
