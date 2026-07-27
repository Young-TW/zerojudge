#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n = 0) { init(n); }
    void init(int n) {
        p.resize(n + 1);
        r.assign(n + 1, 0);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) ++r[a];
        return true;
    }
};

struct Edge {
    int u, v;
    long long w;
    bool inMST = false;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while (cin >> N >> M) {
        vector<Edge> edges(M);
        for (int i = 0; i < M; ++i) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }

        /* ---------- 1. Kruskal ---------- */
        vector<int> idx(M);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(),
             [&](int a, int b) { return edges[a].w < edges[b].w; });

        DSU dsu(N);
        long long mstWeight = 0;
        vector<vector<pair<int,long long>>> adj(N + 1);
        int taken = 0;
        for (int id : idx) {
            Edge &e = edges[id];
            if (dsu.unite(e.u, e.v)) {
                e.inMST = true;
                mstWeight += e.w;
                ++taken;
                adj[e.u].push_back({e.v, e.w});
                adj[e.v].push_back({e.u, e.w});
                if (taken == N - 1) break;
            }
        }

        /* ---------- 2. LCA preprocessing ---------- */
        int LOG = 1;
        while ((1 << LOG) <= N) ++LOG;
        vector<int> depth(N + 1, -1);
        vector<vector<int>> up(N + 1, vector<int>(LOG, 0));
        vector<vector<long long>> mx(N + 1, vector<long long>(LOG, 0));

        queue<int> q;
        depth[1] = 0;
        q.push(1);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &pr : adj[v]) {
                int to = pr.first;
                long long w = pr.second;
                if (depth[to] != -1) continue;
                depth[to] = depth[v] + 1;
                up[to][0] = v;
                mx[to][0] = w;
                for (int k = 1; k < LOG; ++k) {
                    up[to][k] = up[ up[to][k-1] ][k-1];
                    mx[to][k] = max(mx[to][k-1], mx[ up[to][k-1] ][k-1]);
                }
                q.push(to);
            }
        }

        auto maxOnPath = [&](int a, int b) -> long long {
            long long ans = 0;
            if (depth[a] < depth[b]) swap(a, b);
            int diff = depth[a] - depth[b];
            for (int k = LOG - 1; k >= 0; --k) {
                if (diff & (1 << k)) {
                    ans = max(ans, mx[a][k]);
                    a = up[a][k];
                }
            }
            if (a == b) return ans;
            for (int k = LOG - 1; k >= 0; --k) {
                if (up[a][k] != up[b][k]) {
                    ans = max(ans, mx[a][k]);
                    ans = max(ans, mx[b][k]);
                    a = up[a][k];
                    b = up[b][k];
                }
            }
            ans = max(ans, mx[a][0]);
            ans = max(ans, mx[b][0]);
            return ans;
        };

        /* ---------- 3. evaluate second best ---------- */
        const long long INF = (1LL << 62);
        long long second = INF;
        bool anotherMST = false;

        for (const Edge &e : edges) {
            if (e.inMST) continue;
            long long mxPath = maxOnPath(e.u, e.v);
            long long cand = mstWeight + e.w - mxPath;
            if (cand == mstWeight) {
                anotherMST = true;
            } else if (cand > mstWeight && cand < second) {
                second = cand;
            }
        }

        if (anotherMST) second = mstWeight;
        cout << mstWeight << ' ' << second << '\n';
    }
    return 0;
}
