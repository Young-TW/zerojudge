#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> bit;
    Fenwick(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }
    // add delta at index i (1‑based)
    void add(int i, long long delta) {
        for (++i; i <= n; i += i & -i) bit[i] += delta;
    }
    // prefix sum [0, i] (0‑based)
    long long sumPrefix(int i) const {
        long long s = 0;
        for (++i; i > 0; i -= i & -i) s += bit[i];
        return s;
    }
    // sum on [l, r] (both inclusive, 0‑based)
    long long rangeSum(int l, int r) const {
        if (l > r) return 0;
        return sumPrefix(r) - (l ? sumPrefix(l - 1) : 0);
    }
};

int n, s, t, w;
vector<vector<pair<int,int>>> adj;
vector<int> parent_, depth_, heavy, head, pos, sz;
int curPos;
vector<pair<int,int>> edges;          // 1‑based, edges[1..n-1]
vector<int> edgeChild;                // child vertex of each edge

int dfs1(int v, int p) {
    parent_[v] = p;
    sz[v] = 1;
    int maxSub = 0;
    heavy[v] = -1;
    for (auto [to, id] : adj[v]) if (to != p) {
        depth_[to] = depth_[v] + 1;
        int sub = dfs1(to, v);
        if (sub > maxSub) {
            maxSub = sub;
            heavy[v] = to;
        }
        sz[v] += sub;
    }
    return sz[v];
}

void dfs2(int v, int h) {
    head[v] = h;
    pos[v] = curPos++;
    if (heavy[v] != -1) dfs2(heavy[v], h);
    for (auto [to, id] : adj[v]) if (to != parent_[v] && to != heavy[v]) {
        dfs2(to, to);
    }
}

// sum of taxes on path root … v (root = s)
long long queryRoot(int v, const Fenwick &bit) {
    long long res = 0;
    while (head[v] != head[s]) {
        res += bit.rangeSum(pos[head[v]], pos[v]);
        v = parent_[head[v]];
    }
    if (v != s) {
        res += bit.rangeSum(pos[s] + 1, pos[v]); // skip root itself
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> s >> t >> w) {
        adj.assign(n + 1, {});
        edges.assign(n, {0,0});          // index 1..n-1
        for (int i = 1; i <= n - 1; ++i) {
            int u, v; cin >> u >> v;
            edges[i] = {u, v};
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});
        }

        parent_.assign(n + 1, 0);
        depth_.assign(n + 1, 0);
        heavy.assign(n + 1, -1);
        head.assign(n + 1, 0);
        pos.assign(n + 1, 0);
        sz.assign(n + 1, 0);
        curPos = 0;
        depth_[s] = 0;
        dfs1(s, 0);
        dfs2(s, s);

        // child endpoint of each edge
        edgeChild.assign(n, 0);
        for (int i = 1; i <= n - 1; ++i) {
            int u = edges[i].first, v = edges[i].second;
            if (parent_[u] == v) edgeChild[i] = u;
            else edgeChild[i] = v;               // the deeper one
        }

        Fenwick bit(n);
        for (int v = 1; v <= n; ++v) {
            if (v != s) bit.add(pos[v], 1);      // initial tax = 1
        }

        int total = t + w;
        for (int i = 0; i < total; ++i) {
            int type; cin >> type;
            if (type == 1) {
                long long x; int y;
                cin >> x >> y;
                long long cnt = queryRoot(y, bit);
                cout << cnt * x << '\n';
            } else { // type == 2
                int z; cin >> z;
                int c = edgeChild[z];
                bit.add(pos[c], -1);              // 1 -> 0
            }
        }
    }
    return 0;
}
