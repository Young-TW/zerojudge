#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int MAXN = 100005;

int N, Q;
int T[MAXN];
vector<int> adj[MAXN];

int fa[MAXN], dep[MAXN], sz[MAXN], son[MAXN];
int top[MAXN], dfn[MAXN], rnk[MAXN], tot;

void dfs1(int u, int p, int d) {
    fa[u] = p; dep[u] = d; sz[u] = 1; son[u] = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs1(v, u, d + 1);
        sz[u] += sz[v];
        if (sz[son[u]] < sz[v]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t; dfn[u] = ++tot; rnk[tot] = u;
    if (son[u]) dfs2(son[u], t);
    for (int v : adj[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

int bit[MAXN];
void add(int x, int v) {
    for (; x <= N; x += x & -x) bit[x] += v;
}
int query(int x) {
    int res = 0;
    for (; x > 0; x -= x & -x) res += bit[x];
    return res;
}
int query_range(int l, int r) {
    return query(r) - query(l - 1);
}
int query_path(int u, int v) {
    int res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res += query_range(dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    res += query_range(dfn[u], dfn[v]);
    return res;
}

struct Op {
    int type;
    int u, v, delta;
    int a, b, k, id;
};

vector<Op> ops;
int ans[MAXN];
int cur_val[MAXN];

vector<int> discrete;
Op tmp[MAXN * 4];

void solve(int l, int r, int L, int R) {
    if (L > R) return;
    if (l == r) {
        for (int i = L; i <= R; ++i) {
            if (ops[i].type == 1 && ans[ops[i].id] != -2) {
                ans[ops[i].id] = l;
            }
        }
        return;
    }
    int mid = (l + r) / 2;
    int p1 = 0, p2 = R - L + 1;
    for (int i = L; i <= R; ++i) {
        if (ops[i].type == 0) {
            if (ops[i].v <= mid) {
                add(dfn[ops[i].u], ops[i].delta);
                tmp[p1++] = ops[i];
            } else {
                tmp[--p2] = ops[i];
            }
        } else {
            if (ans[ops[i].id] == -2) {
                tmp[p1++] = ops[i];
                continue;
            }
            int cnt = query_path(ops[i].a, ops[i].b);
            if (cnt >= ops[i].k) {
                tmp[p1++] = ops[i];
            } else {
                ops[i].k -= cnt;
                tmp[--p2] = ops[i];
            }
        }
    }
    for (int i = L; i <= R; ++i) {
        if (ops[i].type == 0 && ops[i].v <= mid) {
            add(dfn[ops[i].u], -ops[i].delta);
        }
    }
    int len = R - L + 1;
    memcpy(&ops[L], tmp, sizeof(Op) * p1);
    // The right partition was filled back-to-front (tmp[--p2]), so it is in
    // reverse time order. Copy it back reversed to restore the original
    // (temporal) order, which the parallel binary search relies on.
    int rc = len - p2;
    for (int t = 0; t < rc; ++t) ops[L + p1 + t] = tmp[len - 1 - t];
    
    int mid_idx = L + p1 - 1;
    solve(l, mid, L, mid_idx);
    solve(mid + 1, r, mid_idx + 1, R);
}

int main() {
    while (scanf("%d", &N) != EOF) {
        scanf("%d", &Q);
        for (int i = 1; i <= N; ++i) adj[i].clear();
        for (int i = 1; i <= N; ++i) scanf("%d", &T[i]);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        tot = 0;
        dfs1(1, 0, 1);
        dfs2(1, 1);
        
        discrete.clear();
        for (int i = 1; i <= N; ++i) discrete.push_back(T[i]);
        
        struct Query {
            int k, a, b;
        };
        vector<Query> queries;
        for (int i = 0; i < Q; ++i) {
            int k, a, b;
            scanf("%d %d %d", &k, &a, &b);
            queries.push_back({k, a, b});
            if (k == 0) {
                discrete.push_back(b);
            }
        }
        sort(discrete.begin(), discrete.end());
        discrete.erase(unique(discrete.begin(), discrete.end()), discrete.end());
        int V = discrete.size();
        // Reverse the index order so that a LARGER value maps to a SMALLER
        // index. The parallel binary search below finds the k-th smallest
        // index on the path, which then corresponds to the k-th LARGEST value.
        auto get_idx = [&](int val) -> int {
            int a = (int)(lower_bound(discrete.begin(), discrete.end(), val) - discrete.begin()) + 1;
            return V + 1 - a;
        };

        ops.clear();
        for (int i = 1; i <= N; ++i) {
            ops.push_back({0, i, get_idx(T[i]), 1, 0, 0, 0, 0});
        }
        int q_cnt = 0;
        for (int i = 1; i <= N; ++i) cur_val[i] = get_idx(T[i]);

        for (int i = 0; i < Q; ++i) {
            if (queries[i].k == 0) {
                int u = queries[i].a;
                int new_v = get_idx(queries[i].b);
                ops.push_back({0, u, cur_val[u], -1, 0, 0, 0, 0});
                ops.push_back({0, u, new_v, 1, 0, 0, 0, 0});
                cur_val[u] = new_v;
            } else {
                q_cnt++;
                int u = queries[i].a, v = queries[i].b, k = queries[i].k;
                int len = dep[u] + dep[v] - 2 * dep[lca(u, v)] + 1;
                if (k > len) {
                    ans[q_cnt] = -2;
                } else {
                    ans[q_cnt] = -1;
                }
                ops.push_back({1, 0, 0, 0, u, v, k, q_cnt});
            }
        }
        
        if (V > 0) {
            solve(1, V, 0, ops.size() - 1);
        }
        
        for (int i = 1; i <= q_cnt; ++i) {
            if (ans[i] == -2) {
                printf("invalid request!\n");
            } else {
                // ans[i] is a reversed index; map back to the real value.
                printf("%d\n", discrete[V - ans[i]]);
            }
        }
    }
    return 0;
}
