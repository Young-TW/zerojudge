#include <bits/stdc++.h>
using namespace std;

/* ---------- Edmonds' blossom algorithm (KACTL version) ---------- */
struct GeneralMatching {
    int n;
    vector<vector<int>> g;
    vector<int> match, base, p, q;
    vector<bool> used, blossom;
    int qh, qt;

    GeneralMatching(int n = 0) { init(n); }

    void init(int n_) {
        n = n_;
        g.assign(n, {});
    }
    void addEdge(int a, int b) {
        if (a == b) return;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int lca(int a, int b) {
        vector<char> used_lca(n, 0);
        while (true) {
            a = base[a];
            used_lca[a] = 1;
            if (match[a] == -1) break;
            a = p[match[a]];
        }
        while (true) {
            b = base[b];
            if (used_lca[b]) return b;
            b = p[match[b]];
        }
    }

    void markPath(int v, int b, int children) {
        while (base[v] != b) {
            blossom[base[v]] = blossom[base[match[v]]] = true;
            p[v] = children;
            children = match[v];
            v = p[match[v]];
        }
    }

    int findPath(int root) {
        used.assign(n, false);
        p.assign(n, -1);
        base.resize(n);
        iota(base.begin(), base.end(), 0);
        q.assign(n, 0);
        qh = qt = 0;
        q[qt++] = root;
        used[root] = true;
        while (qh < qt) {
            int v = q[qh++];
            for (int to : g[v]) {
                if (base[v] == base[to] || match[v] == to) continue;
                if (to == root || (match[to] != -1 && p[match[to]] != -1)) {
                    int curbase = lca(v, to);
                    blossom.assign(n, false);
                    markPath(v, curbase, to);
                    markPath(to, curbase, v);
                    for (int i = 0; i < n; ++i)
                        if (blossom[base[i]]) {
                            base[i] = curbase;
                            if (!used[i]) {
                                used[i] = true;
                                q[qt++] = i;
                            }
                        }
                } else if (p[to] == -1) {
                    p[to] = v;
                    if (match[to] == -1)
                        return to;
                    int nxt = match[to];
                    used[nxt] = true;
                    q[qt++] = nxt;
                }
            }
        }
        return -1;
    }

    int maxMatching() {
        match.assign(n, -1);
        for (int v = 0; v < n; ++v)
            if (match[v] == -1) {
                int to = findPath(v);
                if (to == -1) continue;
                while (to != -1) {
                    int pv = p[to];
                    int pp = match[pv];
                    match[to] = pv;
                    match[pv] = to;
                    to = pp;
                }
            }
        int cnt = 0;
        for (int i = 0; i < n; ++i) if (match[i] != -1) ++cnt;
        return cnt / 2;
    }
};

/* --------------------------- main program -------------------------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    const int dr[8] = {-1,-1,-1,0,0,1,1,1};
    const int dc[8] = {-1,0,1,-1,1,-1,0,1};

    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<string> board(N);
        for (int i = 0; i < N; ++i) cin >> board[i];

        vector<vector<int>> id(N, vector<int>(M, -1));
        int V = 0, start = -1;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (board[i][j] != '#') {
                    id[i][j] = V;
                    if (board[i][j] == 'K') start = V;
                    ++V;
                }

        GeneralMatching gm(V);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j) if (id[i][j] != -1) {
                int u = id[i][j];
                for (int d = 0; d < 8; ++d) {
                    int ni = i + dr[d], nj = j + dc[d];
                    if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
                    if (id[ni][nj] == -1) continue;
                    int v = id[ni][nj];
                    if (u < v) gm.addEdge(u, v);
                }
            }

        gm.maxMatching();                 // step 3, result stored in gm.match
        const vector<int>& match = gm.match;

        // ---------- alternating BFS ----------
        vector<char> vis0(V, 0), vis1(V, 0);   // parity 0 = even, 1 = odd
        queue<pair<int,int>> q;
        for (int v = 0; v < V; ++v)
            if (match[v] == -1) {
                vis0[v] = 1;
                q.emplace(v, 0);
            }

        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            int v = cur.first, parity = cur.second;
            if (parity == 0) { // need an unmatched edge
                for (int to : gm.g[v]) {
                    if (match[v] == to) continue;          // matched edge not allowed
                    if (!vis1[to]) {
                        vis1[to] = 1;
                        q.emplace(to, 1);
                    }
                }
            } else { // parity == 1, need the matched edge only
                int to = match[v];
                if (to != -1 && !vis0[to]) {
                    vis0[to] = 1;
                    q.emplace(to, 0);
                }
            }
        }

        bool reachable = vis0[start] || vis1[start];
        if (reachable) cout << "Wen\n";
        else           cout << "Ting\n";
    }
    return 0;
}
