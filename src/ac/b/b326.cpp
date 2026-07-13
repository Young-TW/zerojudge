#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 32770;
int tree[MAXN * 4];
int val[MAXN];
vector<int> adj[MAXN];

int fa[MAXN], dep[MAXN], sz[MAXN], son[MAXN];
int top[MAXN], dfn[MAXN], rev_dfn[MAXN], tim;

void dfs1(int u, int p) {
    fa[u] = p;
    dep[u] = (p == -1) ? 0 : dep[p] + 1;
    sz[u] = 1;
    son[u] = -1;
    int max_sz = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > max_sz) {
            max_sz = sz[v];
            son[u] = v;
        }
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++tim;
    rev_dfn[tim] = u;
    if (son[u] != -1) {
        dfs2(son[u], t);
    }
    for (int v : adj[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void update(int node, int l, int r, int pos, int v) {
    if (l == r) {
        tree[node] = v;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(node * 2, l, mid, pos, v);
    else update(node * 2 + 1, mid + 1, r, pos, v);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int find_last(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l || tree[node] == 0) return -1;
    if (l == r) return l;
    int mid = (l + r) / 2;
    int right_res = find_last(node * 2 + 1, mid + 1, r, ql, qr);
    if (right_res != -1) return right_res;
    return find_last(node * 2, l, mid, ql, qr);
}

int query_path(int x) {
    int res = -1;
    while (x != -1) {
        int t = top[x];
        int pos = find_last(1, 1, tim, dfn[t], dfn[x]);
        if (pos != -1) {
            res = rev_dfn[pos];
            break;
        }
        x = fa[t];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        memset(tree, 0, sizeof(tree));
        memset(val, 0, sizeof(val));
        for (int i = 0; i < N; ++i) adj[i].clear();
        tim = 0;

        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        if (N > 0) {
            dfs1(0, -1);
            dfs2(0, 0);
        }

        int Q;
        cin >> Q;
        for (int i = 0; i < Q; ++i) {
            char op;
            int x;
            cin >> op >> x;
            if (op == 'M') {
                val[x] ^= 1;
                update(1, 1, tim, dfn[x], val[x]);
            } else {
                cout << query_path(x) << "\n";
            }
        }
        cout << "\n";
    }
    return 0;
}
