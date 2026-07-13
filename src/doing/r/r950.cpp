#include <bits/stdc++.h>
using namespace std;

struct AdjEdge {
    int to;
    int id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N, M, Q;
    while (cin >> N >> M >> Q) {
        vector<vector<AdjEdge>> adj(N);
        vector<pair<int,int>> edges(M);
        for (int i = 0; i < M; ++i) {
            int u, v; cin >> u >> v;
            edges[i] = {u, v};
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});
        }
        vector<pair<int,int>> queries(Q);
        for (int i = 0; i < Q; ++i) {
            int u, v; cin >> u >> v;
            queries[i] = {u, v};
        }

        vector<int> disc(N, -1), low(N), parent(N, -1), subtree(N, 0);
        vector<int> compSize(N, 0);
        unordered_set<unsigned long long> bridgeSet;
        unordered_map<unsigned long long, int> bridgeSubSize;
        int timer = 0;

        function<void(int,int,vector<int>&)> dfs = [&](int u, int parentEdge, vector<int>& compNodes) {
            disc[u] = low[u] = timer++;
            subtree[u] = 1;
            compNodes.push_back(u);
            for (const auto &e : adj[u]) {
                int v = e.to;
                if (e.id == parentEdge) continue;
                if (disc[v] == -1) {
                    parent[v] = u;
                    dfs(v, e.id, compNodes);
                    low[u] = min(low[u], low[v]);
                    if (low[v] > disc[u]) {
                        int a = u, b = v;
                        if (a > b) swap(a, b);
                        unsigned long long key = (static_cast<unsigned long long>(a) << 32) | static_cast<unsigned long long>(b);
                        bridgeSet.insert(key);
                        bridgeSubSize[key] = subtree[v];   // v is child
                    }
                    subtree[u] += subtree[v];
                } else {
                    low[u] = min(low[u], disc[v]);
                }
            }
        };

        for (int i = 0; i < N; ++i) {
            if (disc[i] == -1) {
                vector<int> compNodes;
                dfs(i, -1, compNodes);
                int sz = subtree[i];
                for (int v : compNodes) compSize[v] = sz;
            }
        }

        for (auto &qr : queries) {
            int a = qr.first, b = qr.second;
            int x = a, y = b;
            if (x > y) swap(x, y);
            unsigned long long key = (static_cast<unsigned long long>(x) << 32) | static_cast<unsigned long long>(y);
            if (bridgeSet.find(key) == bridgeSet.end()) {
                cout << compSize[a] << '\n';
            } else {
                // bridge exists, determine which side a belongs to
                if (parent[b] == a) {                // a is parent of b
                    int sub = bridgeSubSize[key];
                    cout << compSize[a] - sub << '\n';
                } else if (parent[a] == b) {         // b is parent of a
                    int sub = bridgeSubSize[key];
                    cout << sub << '\n';
                } else {
                    // should not happen for a true bridge
                    cout << compSize[a] << '\n';
                }
            }
        }
    }
    return 0;
}
