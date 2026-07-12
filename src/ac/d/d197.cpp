#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int dfn[MAXN], low[MAXN], scc_id[MAXN];
bool in_stack[MAXN];
stack<int> stk;
int idx, scc_cnt;
int in_deg[MAXN];

void tarjan(int start) {
    stack<pair<int, int>> dfs_stk;
    dfs_stk.push({start, 0});
    
    while (!dfs_stk.empty()) {
        int u = dfs_stk.top().first;
        int i = dfs_stk.top().second;
        
        if (i == 0) {
            dfn[u] = low[u] = ++idx;
            stk.push(u);
            in_stack[u] = true;
        }
        
        if (i < (int)adj[u].size()) {
            dfs_stk.top().second++;
            int v = adj[u][i];
            if (!dfn[v]) {
                dfs_stk.push({v, 0});
            } else if (in_stack[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        } else {
            dfs_stk.pop();
            if (!dfs_stk.empty()) {
                int parent = dfs_stk.top().first;
                low[parent] = min(low[parent], low[u]);
            }
            
            if (dfn[u] == low[u]) {
                scc_cnt++;
                int v;
                do {
                    v = stk.top();
                    stk.pop();
                    in_stack[v] = false;
                    scc_id[v] = scc_cnt;
                } while (v != u);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int n, m;
        cin >> n >> m;
        
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
        }
        memset(dfn + 1, 0, sizeof(int) * n);
        memset(low + 1, 0, sizeof(int) * n);
        memset(scc_id + 1, 0, sizeof(int) * n);
        memset(in_stack + 1, 0, sizeof(bool) * n);
        memset(in_deg + 1, 0, sizeof(int) * n);
        idx = 0;
        scc_cnt = 0;
        while (!stk.empty()) stk.pop();
        
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }
        
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                tarjan(i);
            }
        }
        
        for (int u = 1; u <= n; u++) {
            for (int v : adj[u]) {
                if (scc_id[u] != scc_id[v]) {
                    in_deg[scc_id[v]]++;
                }
            }
        }
        
        int ans = 0;
        for (int i = 1; i <= scc_cnt; i++) {
            if (in_deg[i] == 0) {
                ans++;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
