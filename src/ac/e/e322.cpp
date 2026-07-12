#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#include <functional>

using namespace std;

const int INF = 0x3f3f3f3f;

struct Edge {
    int to;
    int weight;
};

int T;
int N, M, K, P;
vector<vector<Edge>> graph;
vector<vector<Edge>> rev_graph;
vector<int> dist_n;
vector<vector<int>> dp;
vector<vector<bool>> in_stack;
bool has_infinite;

void dijkstra() {
    dist_n.assign(N + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist_n[N] = 0;
    pq.push({0, N});
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist_n[u]) continue;
        
        for (const auto& edge : rev_graph[u]) {
            int v = edge.to;
            int w = edge.weight;
            if (dist_n[v] > dist_n[u] + w) {
                dist_n[v] = dist_n[u] + w;
                pq.push({dist_n[v], v});
            }
        }
    }
}

int dfs(int u, int k) {
    if (has_infinite) return 0;
    if (dp[u][k] != -1) return dp[u][k];
    
    in_stack[u][k] = true;
    
    int result = 0;
    if (u == N) {
        result = 1;
    }
    
    for (const auto& edge : graph[u]) {
        int v = edge.to;
        int w = edge.weight;
        int new_k = k - (dist_n[v] + w - dist_n[u]);
        
        if (new_k >= 0 && new_k <= K) {
            if (in_stack[v][new_k]) {
                has_infinite = true;
                return 0;
            }
            result = (result + dfs(v, new_k)) % P;
        }
    }
    
    in_stack[u][k] = false;
    dp[u][k] = result;
    return result;
}

void solve() {
    cin >> N >> M >> K >> P;
    
    graph.assign(N + 1, vector<Edge>());
    rev_graph.assign(N + 1, vector<Edge>());
    
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        rev_graph[b].push_back({a, c});
    }
    
    dijkstra();
    
    if (dist_n[1] == INF) {
        cout << 0 << endl;
        return;
    }
    
    dp.assign(N + 1, vector<int>(K + 1, -1));
    in_stack.assign(N + 1, vector<bool>(K + 1, false));
    has_infinite = false;
    
    int ans = dfs(1, K);
    
    if (has_infinite) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    
    return 0;
}
