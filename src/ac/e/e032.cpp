#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int w;
};

const long long NEG = -(1LL << 60);

int N, K;
int LOGN;
vector<vector<Edge>> g;

vector<int> tin, tout, depth;
vector<long long> distRoot;
vector<vector<int>> up;
int timerDFS = 0;

void dfs(int v, int p) {
    tin[v] = ++timerDFS;
    up[0][v] = p;
    for (int k = 1; k < LOGN; ++k)
        up[k][v] = up[k - 1][up[k - 1][v]];
    for (auto &e : g[v]) {
        if (e.to == p) continue;
        depth[e.to] = depth[v] + 1;
        distRoot[e.to] = distRoot[v] + e.w;
        dfs(e.to, v);
    }
    tout[v] = ++timerDFS;
}

inline bool isAncestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int u, int v) {
    if (isAncestor(u, v)) return u;
    if (isAncestor(v, u)) return v;
    for (int k = LOGN - 1; k >= 0; --k) {
        if (!isAncestor(up[k][u], v))
            u = up[k][u];
    }
    return up[0][u];
}

inline long long dist(int u, int v) {
    int w = lca(u, v);
    return distRoot[u] + distRoot[v] - 2 * distRoot[w];
}

/* ---------- solve one salesman ---------- */
long long solve_one(const vector<int> &req) {
    if (req.empty()) return 0LL;
    vector<int> nodes = req;
    auto cmpTin = [&](int a, int b) { return tin[a] < tin[b]; };
    sort(nodes.begin(), nodes.end(), cmpTin);
    int sz = (int)nodes.size();
    for (int i = 0; i < sz - 1; ++i) {
        int w = lca(nodes[i], nodes[i + 1]);
        nodes.push_back(w);
    }
    sort(nodes.begin(), nodes.end(), cmpTin);
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

    int V = (int)nodes.size();
    unordered_map<int, int> idx;
    idx.reserve(V * 2);
    for (int i = 0; i < V; ++i) idx[nodes[i]] = i;

    vector<char> isReq(V, 0);
    for (int x : req) {
        int id = idx[x];
        isReq[id] = 1;
    }

    vector<vector<pair<int, long long>>> vt(V);
    long long totalWeight = 0;

    vector<int> st;
    st.push_back(nodes[0]);
    for (int i = 1; i < V; ++i) {
        int v = nodes[i];
        while (!isAncestor(st.back(), v)) st.pop_back();
        int p = st.back();
        long long w = distRoot[v] - distRoot[p];          // p is ancestor of v
        int ip = idx[p];
        int iv = idx[v];
        vt[ip].push_back({iv, w});
        vt[iv].push_back({ip, w});
        totalWeight += w;
        st.push_back(v);
    }

    /* ----- DP for diameter ----- */
    int root = idx[nodes[0]];
    vector<int> parent(V, -1);
    vector<long long> edgeToParent(V, 0);
    vector<int> order;
    order.reserve(V);
    stack<int> s;
    s.push(root);
    parent[root] = -1;
    while (!s.empty()) {
        int u = s.top(); s.pop();
        order.push_back(u);
        for (auto &pr : vt[u]) {
            int v = pr.first;
            if (v == parent[u]) continue;
            parent[v] = u;
            edgeToParent[v] = pr.second;
            s.push(v);
        }
    }

    vector<long long> down(V, NEG);
    long long bestDiameter = 0;
    for (int i = V - 1; i >= 0; --i) {
        int u = order[i];
        long long best1 = NEG, best2 = NEG;
        if (isReq[u]) down[u] = 0;
        for (auto &pr : vt[u]) {
            int v = pr.first;
            if (v == parent[u]) continue;
            if (down[v] != NEG) {
                long long cand = down[v] + pr.second;
                if (cand > best1) { best2 = best1; best1 = cand; }
                else if (cand > best2) { best2 = cand; }
                down[u] = max(down[u], cand);
            }
        }
        if (best1 != NEG && best2 != NEG)
            bestDiameter = max(bestDiameter, best1 + best2);
        else if (best1 != NEG)
            bestDiameter = max(bestDiameter, best1);   // single branch case
    }

    return 2 * totalWeight - bestDiameter;
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> N >> K) {
        g.assign(N, {});
        for (int i = 0; i < N - 1; ++i) {
            int a, b, w;
            cin >> a >> b >> w;
            g[a].push_back({b, w});
            g[b].push_back({a, w});
        }

        LOGN = 1;
        while ((1 << LOGN) <= N) ++LOGN;
        tin.assign(N, 0);
        tout.assign(N, 0);
        depth.assign(N, 0);
        distRoot.assign(N, 0);
        up.assign(LOGN, vector<int>(N, 0));
        timerDFS = 0;
        dfs(0, 0);                     // root at 0, its parent is itself

        long long totalAnswer = 0;
        for (int i = 0; i < K; ++i) {
            int m;
            cin >> m;
            vector<int> req(m);
            for (int j = 0; j < m; ++j) cin >> req[j];
            totalAnswer += solve_one(req);
        }
        cout << totalAnswer << '\n';
    }
    return 0;
}
