#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <functional>

using namespace std;

struct Edge {
    int to;
    int d;
    int v;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N, M;
            cin >> N >> M;
            int A, B;
            cin >> A >> B;
            
            vector<vector<Edge>> adj(N + 1);
            for (int i = 0; i < M; ++i) {
                int a, b, d, v;
                cin >> a >> b >> d >> v;
                adj[a].push_back({b, d, v});
                adj[b].push_back({a, d, v});
            }
            
            // Dijkstra 1: shortest distance
            vector<long long> dist(N + 1, LLONG_MAX);
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq1;
            dist[A] = 0;
            pq1.push({0, A});
            while (!pq1.empty()) {
                pair<long long, int> top1 = pq1.top();
                pq1.pop();
                long long d = top1.first;
                int u = top1.second;
                if (d > dist[u]) continue;
                for (const auto& e : adj[u]) {
                    if (dist[e.to] > dist[u] + e.d) {
                        dist[e.to] = dist[u] + e.d;
                        pq1.push({dist[e.to], e.to});
                    }
                }
            }
            long long X = dist[B];
            
            // Dijkstra 2: shortest time, and corresponding distance
            vector<pair<double, long long>> dp(N + 1, {1e18, LLONG_MAX});
            priority_queue<pair<pair<double, long long>, int>, vector<pair<pair<double, long long>, int>>, greater<pair<pair<double, long long>, int>>> pq2;
            dp[A] = {0.0, 0};
            pq2.push({{0.0, 0}, A});
            while (!pq2.empty()) {
                pair<pair<double, long long>, int> top2 = pq2.top();
                pq2.pop();
                pair<double, long long> d = top2.first;
                int u = top2.second;
                
                if (d > dp[u]) continue;
                
                for (const auto& e : adj[u]) {
                    pair<double, long long> nd = {dp[u].first + (double)e.d / e.v, dp[u].second + e.d};
                    if (nd < dp[e.to]) {
                        dp[e.to] = nd;
                        pq2.push({nd, e.to});
                    }
                }
            }
            long long Y = dp[B].second;
            
            cout << X << " " << Y << "\n";
        }
    }
    
    return 0;
}
