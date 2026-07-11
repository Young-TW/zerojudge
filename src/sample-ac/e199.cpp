#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const int MAXN = 605;
int dfn[MAXN], low[MAXN], timer;
bool is_cut[MAXN];
vector<int> adj[MAXN];

void dfs(int u, int p) {
    dfn[u] = low[u] = ++timer;
    int children = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (dfn[v] == 0) {
            children++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (p != -1 && low[v] >= dfn[u]) {
                is_cut[u] = true;
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (p == -1 && children > 1) {
        is_cut[u] = true;
    }
}

void solve() {
    int N, Q;
    if (!(cin >> N >> Q)) return;
    for (int i = 1; i <= N; ++i) {
        adj[i].clear();
    }
    for (int i = 0; i < Q; ++i) {
        string op;
        cin >> op;
        if (op == "add") {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        } else if (op == "query") {
            fill(dfn, dfn + N + 1, 0);
            fill(low, low + N + 1, 0);
            fill(is_cut, is_cut + N + 1, false);
            timer = 0;
            for (int i = 1; i <= N; ++i) {
                if (dfn[i] == 0) {
                    dfs(i, -1);
                }
            }
            vector<int> ans;
            for (int i = 1; i <= N; ++i) {
                if (is_cut[i]) {
                    ans.push_back(i);
                }
            }
            cout << ans.size();
            for (int x : ans) {
                cout << " " << x;
            }
            cout << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
