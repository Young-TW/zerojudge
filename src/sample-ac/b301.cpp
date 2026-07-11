#include <bits/stdc++.h>
using namespace std;

int N, Q;
vector<int> adj[10005];
int tin[10005], tout[10005], timer;
int par[10005];

void dfs(int root) {
    vector<int> st_u, st_p, st_idx;
    st_u.push_back(root); st_p.push_back(-1); st_idx.push_back(0);
    par[root] = -1;
    tin[root] = ++timer;
    while (!st_u.empty()) {
        int u = st_u.back();
        int p = st_p.back();
        int& idx = st_idx.back();
        if (idx < (int)adj[u].size()) {
            int v = adj[u][idx++];
            if (v != p) {
                par[v] = u;
                tin[v] = ++timer;
                st_u.push_back(v); st_p.push_back(u); st_idx.push_back(0);
            }
        } else {
            tout[u] = timer;
            st_u.pop_back(); st_p.pop_back(); st_idx.pop_back();
        }
    }
}

bool isAncestor(int a, int b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> N >> Q) {
        for (int i = 0; i <= N; i++) adj[i].clear();
        for (int i = 0; i < N; i++) {
            int a, b; cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        timer = 0;
        dfs(0);
        while (Q--) {
            int W, X, Y, Z; cin >> W >> X >> Y >> Z;
            int child;
            if (par[Y] == Z) child = Y;
            else child = Z;
            bool wIn = isAncestor(child, W);
            bool xIn = isAncestor(child, X);
            if (wIn != xIn) cout << "GO\n";
            else cout << "STOP\n";
        }
    }
    return 0;
}
