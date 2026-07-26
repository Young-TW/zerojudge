#include <bits/stdc++.h>
using namespace std;

struct CentroidInfo {
    vector<int> pref;          // prefix maximum of vertex numbers
};

int N, Q;
vector<vector<int>> adj;
vector<int> subSize;
vector<char> removed;
vector<vector<pair<int,int>>> anc;   // for each vertex: (centroid , distance)
vector<CentroidInfo> centInfo;       // indexed by vertex number (centroid)

int dfs_size(int u, int p) {
    subSize[u] = 1;
    for (int v : adj[u]) if (v != p && !removed[v]) {
        subSize[u] += dfs_size(v, u);
    }
    return subSize[u];
}

int dfs_centroid(int u, int p, int total) {
    for (int v : adj[u]) if (v != p && !removed[v]) {
        if (subSize[v] > total / 2)
            return dfs_centroid(v, u, total);
    }
    return u;
}

// collect (node, distance) pairs inside the current block
void dfs_collect(int u, int p, int dist, int cent,
                 vector<pair<int,int>>& vec) {
    vec.emplace_back(u, dist);
    anc[u].emplace_back(cent, dist);
    for (int v : adj[u]) if (v != p && !removed[v]) {
        dfs_collect(v, u, dist + 1, cent, vec);
    }
}

void decompose(int entry) {
    int total = dfs_size(entry, -1);
    int cent = dfs_centroid(entry, -1, total);
    removed[cent] = 1;

    vector<pair<int,int>> nodes;          // (vertex , distance to cent)
    nodes.emplace_back(cent, 0);
    anc[cent].emplace_back(cent, 0);

    for (int v : adj[cent]) if (!removed[v]) {
        dfs_collect(v, cent, 1, cent, nodes);
    }

    int maxDist = 0;
    for (auto &p : nodes) if (p.second > maxDist) maxDist = p.second;
    vector<int> best(maxDist + 1, 0);
    for (auto &p : nodes) {
        int node = p.first, d = p.second;
        if (node > best[d]) best[d] = node;
    }
    for (int i = 1; i <= maxDist; ++i)
        if (best[i] < best[i-1]) best[i] = best[i-1];
    centInfo[cent].pref.swap(best);

    for (int v : adj[cent]) if (!removed[v]) {
        decompose(v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!(cin >> N >> Q)) return 0;
    adj.assign(N + 1, {});
    for (int i = 0; i < N - 1; ++i) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    subSize.assign(N + 1, 0);
    removed.assign(N + 1, 0);
    anc.assign(N + 1, {});
    centInfo.assign(N + 1, {});

    decompose(1);

    while (Q--) {
        int X, K; cin >> X >> K;
        int ans = 0;
        for (auto &pr : anc[X]) {
            int c = pr.first;
            int dX = pr.second;
            if (dX > K) continue;
            int allowed = K - dX;
            const vector<int> &pref = centInfo[c].pref;
            int cand;
            if (allowed >= (int)pref.size())
                cand = pref.back();
            else
                cand = pref[allowed];
            if (cand > ans) ans = cand;
        }
        cout << ans << '\n';
    }
    return 0;
}
