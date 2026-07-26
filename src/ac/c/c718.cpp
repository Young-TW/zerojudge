#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    int h;
    long long val;
};

struct Query {
    int type;          // 0 = ask, 1 = update
    int a, b, c;       // meaning depends on type
};

int N, Q;

/* ---------- Heavy Light Decomposition ---------- */
vector<vector<pair<int,int>>> adj;          // (to, edge id)
vector<int> parent_, depth_, heavy_, head_, pos_, sz_;
int curPos;

int dfs1(int v, int p) {
    parent_[v] = p;
    sz_[v] = 1;
    int maxSub = 0;
    for (auto [to, id] : adj[v]) if (to != p) {
        depth_[to] = depth_[v] + 1;
        int sub = dfs1(to, v);
        sz_[v] += sub;
        if (sub > maxSub) {
            maxSub = sub;
            heavy_[v] = to;
        }
    }
    return sz_[v];
}

void dfs2(int v, int h) {
    head_[v] = h;
    pos_[v] = ++curPos;
    if (heavy_[v] != -1) dfs2(heavy_[v], h);
    for (auto [to, id] : adj[v]) if (to != parent_[v] && to != heavy_[v])
        dfs2(to, to);
}

/* ---------- BIT of BITs ---------- */
vector<vector<int>> innerVals;          // sorted h values for each outer node
vector<vector<long long>> innerBIT;     // 1‑based Fenwick trees

inline void innerAdd(int idx, int i, long long delta) {
    auto &bit = innerBIT[idx];
    int n = (int)bit.size() - 1;
    while (i <= n) {
        bit[i] += delta;
        i += i & -i;
    }
}
inline long long innerSum(int idx, int i) {
    long long s = 0;
    auto &bit = innerBIT[idx];
    while (i > 0) {
        s += bit[i];
        i -= i & -i;
    }
    return s;
}

/* add / erase an edge value at position p */
void addEdgePos(int p, int h, long long delta) {
    for (int i = p; i <= N; i += i & -i) {
        const auto &vec = innerVals[i];
        int id = (int)(lower_bound(vec.begin(), vec.end(), h) - vec.begin()) + 1;
        innerAdd(i, id, delta);
    }
}

/* prefix sum of v for positions ≤ p and h > d */
long long prefixSum(int p, int d) {
    long long ans = 0;
    for (int i = p; i > 0; i -= i & -i) {
        const auto &vec = innerVals[i];
        int leCnt = (int)(upper_bound(vec.begin(), vec.end(), d) - vec.begin());
        long long total = innerSum(i, (int)vec.size());
        long long le = innerSum(i, leCnt);
        ans += total - le;
    }
    return ans;
}

/* range query on positions [l,r] */
inline long long rangeQuery(int l, int r, int d) {
    if (l > r) return 0;
    return prefixSum(r, d) - prefixSum(l - 1, d);
}

/* path query using HLD */
long long queryPath(int u, int v, int d) {
    long long res = 0;
    while (head_[u] != head_[v]) {
        if (depth_[head_[u]] < depth_[head_[v]]) swap(u, v);
        int h = head_[u];
        res += rangeQuery(pos_[h], pos_[u], d);
        u = parent_[h];
    }
    if (depth_[u] > depth_[v]) swap(u, v);
    if (u != v) {
        res += rangeQuery(pos_[u] + 1, pos_[v], d);
    }
    return res;
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> N >> Q) {
        adj.assign(N + 1, {});
        vector<Edge> edges(N);               // 1 … N-1, ignore index 0
        for (int i = 1; i < N; ++i) {
            int a, b, h, v;
            cin >> a >> b >> h >> v;
            edges[i] = {a, b, h, v};
            adj[a].push_back({b, i});
            adj[b].push_back({a, i});
        }

        /* HLD initialisation */
        parent_.assign(N + 1, 0);
        depth_.assign(N + 1, 0);
        heavy_.assign(N + 1, -1);
        head_.assign(N + 1, 0);
        pos_.assign(N + 1, 0);
        sz_.assign(N + 1, 0);
        curPos = 0;
        dfs1(1, 0);
        dfs2(1, 1);

        /* edge position (deeper endpoint) */
        vector<int> edgePos(N);
        for (int i = 1; i < N; ++i) {
            int u = edges[i].u, v = edges[i].v;
            edgePos[i] = (depth_[u] > depth_[v]) ? pos_[u] : pos_[v];
        }

        /* read all queries, store them, collect future h values */
        vector<Query> queries(Q);
        vector<vector<int>> edgeH(N);          // all h that may appear for edge i
        for (int i = 1; i < N; ++i) edgeH[i].push_back(edges[i].h); // initial

        for (int i = 0; i < Q; ++i) {
            int tp; cin >> tp;
            if (tp == 0) {
                int S, T, d; cin >> S >> T >> d;
                queries[i] = {0, S, T, d};
            } else {
                int x, h, v; cin >> x >> h >> v;
                queries[i] = {1, x, h, v};
                edgeH[x].push_back(h);
            }
        }

        /* build inner vectors for BIT of BITs */
        innerVals.assign(N + 1, {});
        for (int e = 1; e < N; ++e) {
            int p = edgePos[e];
            for (int i = p; i <= N; i += i & -i) {
                for (int hval : edgeH[e]) innerVals[i].push_back(hval);
            }
        }
        innerBIT.assign(N + 1, {});
        for (int i = 1; i <= N; ++i) {
            auto &vec = innerVals[i];
            sort(vec.begin(), vec.end());
            vec.erase(unique(vec.begin(), vec.end()), vec.end());
            innerBIT[i].assign(vec.size() + 1, 0);
        }

        /* insert initial edge values */
        vector<int> cur_h(N);
        vector<long long> cur_v(N);
        for (int e = 1; e < N; ++e) {
            cur_h[e] = edges[e].h;
            cur_v[e] = edges[e].val;
            addEdgePos(edgePos[e], cur_h[e], cur_v[e]);
        }

        /* process queries */
        for (const auto &qr : queries) {
            if (qr.type == 0) {
                long long ans = queryPath(qr.a, qr.b, qr.c);
                cout << ans << '\n';
            } else {
                int x = qr.a;
                int newh = qr.b;
                long long newv = qr.c;
                int p = edgePos[x];
                addEdgePos(p, cur_h[x], -cur_v[x]);   // erase old
                addEdgePos(p, newh, newv);            // insert new
                cur_h[x] = newh;
                cur_v[x] = newv;
            }
        }
    }
    return 0;
}
