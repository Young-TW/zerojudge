#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>
#include <utility>

using namespace std;

const int MAXN = 100005;

int N;
int edge_u[MAXN], edge_v[MAXN], edge_w[MAXN], edge_node[MAXN];
vector<pair<int, int>> adj[MAXN];

int fa[MAXN], dep[MAXN], sz[MAXN], son[MAXN];
int top[MAXN], dfn[MAXN], rnk[MAXN], val[MAXN];
int dfs_clock;

long long tree[4 * MAXN];

void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = val[rnk[l]];
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void update(int node, int l, int r, int pos, long long new_val) {
    if (l == r) {
        tree[node] = new_val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        update(node * 2, l, mid, pos, new_val);
    } else {
        update(node * 2 + 1, mid + 1, r, pos, new_val);
    }
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

long long query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return tree[node];
    }
    int mid = (l + r) / 2;
    long long res = 0;
    if (ql <= mid) {
        res += query(node * 2, l, mid, ql, qr);
    }
    if (qr > mid) {
        res += query(node * 2 + 1, mid + 1, r, ql, qr);
    }
    return res;
}

void dfs1(int root) {
    stack<pair<int, int>> st;
    st.push({root, 0});
    fa[root] = 0;
    dep[root] = 0;
    while (!st.empty()) {
        int u = st.top().first;
        int state = st.top().second;
        st.pop();
        if (state == 0) {
            sz[u] = 1;
            son[u] = 0;
            st.push({u, 1});
            for (int i = 0; i < adj[u].size(); ++i) {
                int v = adj[u][i].first;
                int id = adj[u][i].second;
                if (v != fa[u]) {
                    fa[v] = u;
                    dep[v] = dep[u] + 1;
                    edge_node[id] = v;
                    st.push({v, 0});
                }
            }
        } else {
            for (int i = 0; i < adj[u].size(); ++i) {
                int v = adj[u][i].first;
                if (v != fa[u]) {
                    sz[u] += sz[v];
                    if (sz[v] > sz[son[u]]) {
                        son[u] = v;
                    }
                }
            }
        }
    }
}

void dfs2(int root) {
    stack<pair<int, int>> st;
    st.push({root, root});
    while (!st.empty()) {
        int u = st.top().first;
        int t = st.top().second;
        st.pop();
        top[u] = t;
        dfn[u] = ++dfs_clock;
        rnk[dfn[u]] = u;
        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].first;
            if (v != fa[u] && v != son[u]) {
                st.push({v, v});
            }
        }
        if (son[u]) {
            st.push({son[u], t});
        }
    }
}

long long query_path(int u, int v) {
    long long res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res += query(1, 1, N, dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    if (u != v) {
        res += query(1, 1, N, dfn[u] + 1, dfn[v]);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> N) {
        dfs_clock = 0;
        for (int i = 1; i <= N; ++i) {
            adj[i].clear();
        }
        for (int i = 1; i < N; ++i) {
            int id, u, v, w;
            cin >> id >> u >> v >> w;
            edge_u[id] = u;
            edge_v[id] = v;
            edge_w[id] = w;
            adj[u].push_back({v, id});
            adj[v].push_back({u, id});
        }
        
        dfs1(1);
        dfs2(1);
        
        for (int i = 1; i < N; ++i) {
            val[dfn[edge_node[i]]] = edge_w[i];
        }
        build(1, 1, N);
        
        set<pair<int, int>> s;
        for (int i = 1; i < N; ++i) {
            s.insert({-edge_w[i], i});
        }
        
        int Q;
        cin >> Q;
        while (Q--) {
            int A, B, k;
            cin >> A >> B >> k;
            long long ans = query_path(A, B);
            cout << ans << "\n";
            
            if (!s.empty()) {
                auto it = s.begin();
                int id = it->second;
                int w_max = -(it->first);
                if (k < w_max) {
                    int new_w = w_max - k;
                    s.erase(it);
                    s.insert({-new_w, id});
                    edge_w[id] = new_w;
                    update(1, 1, N, dfn[edge_node[id]], new_w);
                }
            }
        }
    }
    return 0;
}
