#include <bits/stdc++.h>
using namespace std;

const int MAXC = 1000;
const int WORDS = (MAXC + 63) / 64;          // 16

/* ---------- bitset of colours ---------- */
struct Bit {
    uint64_t w[WORDS];
    Bit() { memset(w, 0, sizeof(w)); }
    void xorWith(const Bit& o) {
        for (int i = 0; i < WORDS; ++i) w[i] ^= o.w[i];
    }
    void flip(int colour) {                 // colour is 1‑based
        int id = (colour - 1) >> 6;
        int off = (colour - 1) & 63;
        w[id] ^= (1ULL << off);
    }
    int count() const {
        int ans = 0;
        for (int i = 0; i < WORDS; ++i) ans += __builtin_popcountll(w[i]);
        return ans;
    }
};

/* ---------- Fenwick tree of Bit ---------- */
struct Fenwick {
    int n;
    vector<Bit> bit;
    Fenwick(int N = 0) { init(N); }
    void init(int N) {
        n = N;
        bit.assign(n + 1, Bit());
    }
    // XOR val into position idx
    void update(int idx, const Bit& val) {
        for (; idx <= n; idx += idx & -idx) bit[idx].xorWith(val);
    }
    // prefix XOR 1 .. idx
    Bit query(int idx) const {
        Bit res;
        for (; idx > 0; idx -= idx & -idx) res.xorWith(bit[idx]);
        return res;
    }
    // inclusive range
    Bit rangeQuery(int l, int r) const {
        Bit res = query(r);
        if (l > 1) {
            Bit left = query(l - 1);
            res.xorWith(left);
        }
        return res;
    }
};

/* ---------- global data ---------- */
int N, C, Q;
vector<vector<int>> adj;
vector<int> col;

vector<int> parent_, depth_, heavy_, head_, pos_, sz_;
int curPos;

/* ---------- first DFS : sizes & heavy child ---------- */
void dfs_sizes(int root = 1) {
    parent_.assign(N + 1, 0);
    depth_.assign(N + 1, 0);
    heavy_.assign(N + 1, 0);
    sz_.assign(N + 1, 0);

    vector<int> order;
    order.reserve(N);
    stack<int> st;
    st.push(root);
    parent_[root] = 0;
    depth_[root] = 0;
    while (!st.empty()) {
        int u = st.top(); st.pop();
        order.push_back(u);
        for (int v : adj[u]) if (v != parent_[u]) {
            parent_[v] = u;
            depth_[v] = depth_[u] + 1;
            st.push(v);
        }
    }
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int u = order[i];
        sz_[u] = 1;
        int maxSub = 0;
        for (int v : adj[u]) if (v != parent_[u]) {
            sz_[u] += sz_[v];
            if (sz_[v] > maxSub) {
                maxSub = sz_[v];
                heavy_[u] = v;
            }
        }
    }
}

/* ---------- second DFS : head & position (iterative) ---------- */
void dfs_hld(int root = 1) {
    head_.assign(N + 1, 0);
    pos_.assign(N + 1, 0);
    curPos = 0;

    stack<pair<int,int>> st;               // (node, head)
    st.emplace(root, root);
    while (!st.empty()) {
        auto [u, h] = st.top(); st.pop();
        // walk down the heavy path starting from u
        int cur = u;
        int curHead = h;
        while (cur) {
            head_[cur] = curHead;
            pos_[cur] = ++curPos;

            // push light children for later processing
            for (int v : adj[cur]) if (v != parent_[cur] && v != heavy_[cur]) {
                st.emplace(v, v);
            }
            cur = heavy_[cur];
        }
    }
}

/* ---------- helper : mask of a colour ---------- */
inline Bit colourMask(int colour) {
    Bit b;
    b.flip(colour);
    return b;
}

/* ---------- path query using HLD ---------- */
int queryPath(int u, int v, const Fenwick& ft) {
    Bit ans;
    while (head_[u] != head_[v]) {
        if (depth_[head_[u]] < depth_[head_[v]]) swap(u, v);
        Bit part = ft.rangeQuery(pos_[head_[u]], pos_[u]);
        ans.xorWith(part);
        u = parent_[head_[u]];
    }
    if (depth_[u] > depth_[v]) swap(u, v);
    Bit part = ft.rangeQuery(pos_[u], pos_[v]);
    ans.xorWith(part);
    return ans.count();
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> N >> C >> Q) {
        adj.assign(N + 1, {});
        for (int i = 0; i < N - 1; ++i) {
            int a, b; cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        col.assign(N + 1, 0);
        for (int i = 1; i <= N; ++i) cin >> col[i];

        dfs_sizes(1);
        dfs_hld(1);

        Fenwick ft(N);
        for (int i = 1; i <= N; ++i) {
            ft.update(pos_[i], colourMask(col[i]));
        }

        for (int i = 0; i < Q; ++i) {
            char type; cin >> type;
            if (type == 'U') {
                int x, c; cin >> x >> c;
                if (col[x] != c) {
                    ft.update(pos_[x], colourMask(col[x])); // remove old
                    col[x] = c;
                    ft.update(pos_[x], colourMask(col[x])); // add new
                }
            } else { // 'Q'
                int u, v; cin >> u >> v;
                cout << queryPath(u, v, ft) << '\n';
            }
        }
    }
    return 0;
}
