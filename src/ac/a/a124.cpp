#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;

struct Edge {
    int to;
    long long w;
};

vector<Edge> adj[MAXN];
long long dist[MAXN];
long long dist_U[MAXN];
int q[MAXN];

int bfs(int start, int N) {
    for (int i = 1; i <= N; ++i) dist[i] = -1;
    int head = 0, tail = 0;
    q[tail++] = start;
    dist[start] = 0;
    int farthestNode = start;
    long long maxDist = 0;
    
    while (head < tail) {
        int u = q[head++];
        for (const auto& edge : adj[u]) {
            int v = edge.to;
            if (dist[v] == -1) {
                dist[v] = dist[u] + edge.w;
                if (dist[v] > maxDist) {
                    maxDist = dist[v];
                    farthestNode = v;
                }
                q[tail++] = v;
            }
        }
    }
    return farthestNode;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        for (int i = 1; i <= N; ++i) {
            adj[i].clear();
        }
        for (int i = 0; i < M; ++i) {
            int u, v;
            long long w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        int U = bfs(1, N);
        int V = bfs(U, N);
        for (int i = 1; i <= N; ++i) dist_U[i] = dist[i];
        
        bfs(V, N);
        long long diameter = dist_U[V];
        long long maxMinDist = 0;
        for (int i = 1; i <= N; ++i) {
            long long d = min(dist_U[i], dist[i]);
            if (d > maxMinDist) {
                maxMinDist = d;
            }
        }
        
        cout << maxMinDist + diameter << "\n";
    }
    
    return 0;
}
