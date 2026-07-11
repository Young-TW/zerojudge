#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

typedef unsigned long long ull;

struct Edge {
    int to;
    ull w;
};

vector<vector<Edge>> adj;
vector<bool> vis;
vector<ull> dis;
ull p[64];

void insert(ull x) {
    for (int i = 63; i >= 0; --i) {
        if (!((x >> i) & 1)) continue;
        if (!p[i]) {
            p[i] = x;
            return;
        }
        x ^= p[i];
    }
}

ull query(ull x) {
    for (int i = 63; i >= 0; --i) {
        if ((x ^ p[i]) > x) {
            x ^= p[i];
        }
    }
    return x;
}

void bfs(int N) {
    queue<int> q;
    q.push(1);
    vis[1] = true;
    dis[1] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (const auto& edge : adj[u]) {
            int v = edge.to;
            ull w = edge.w;
            if (!vis[v]) {
                vis[v] = true;
                dis[v] = dis[u] ^ w;
                q.push(v);
            } else {
                insert(dis[u] ^ dis[v] ^ w);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while (cin >> N >> M) {
        adj.assign(N + 1, vector<Edge>());
        vis.assign(N + 1, false);
        dis.assign(N + 1, 0);
        memset(p, 0, sizeof(p));
        
        for (int i = 0; i < M; ++i) {
            int u, v;
            ull w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        bfs(N);
        
        cout << query(dis[N]) << "\n";
    }
    return 0;
}
