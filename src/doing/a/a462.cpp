#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <tuple>
using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;
typedef tuple<int, int, int> edge;

const ll INF = LLONG_MAX / 2;

vector<ll> dijkstra(int n, const vector<vector<pli>>& adj) {
    vector<ll> dist(n + 1, INF);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d > dist[u]) continue;
        for (const auto& e : adj[u]) {
            int v = e.first;
            ll w = e.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        vector<vector<pli>> adj(N + 1);
        vector<edge> edges;
        for (int i = 0; i < M; ++i) {
            int a, b, w;
            cin >> a >> b >> w;
            adj[a].push_back({b, w});
            adj[b].push_back({a, w});
            edges.emplace_back(a, b, w);
        }

        vector<ll> original_dist = dijkstra(N, adj);
        ll original = original_dist[N];
        ll max_diff = 0;

        for (const auto& e : edges) {
            int a = get<0>(e);
            int b = get<1>(e);
            int w = get<2>(e);

            vector<vector<pli>> temp_adj = adj;
            for (auto& edge : temp_adj[a]) {
                if (edge.first == b) {
                    edge.second = w * 2;
                    break;
                }
            }
            for (auto& edge : temp_adj[b]) {
                if (edge.first == a) {
                    edge.second = w * 2;
                    break;
                }
            }

            vector<ll> new_dist = dijkstra(N, temp_adj);
            ll new_time = new_dist[N];
            if (new_time != INF) {
                ll diff = new_time - original;
                if (diff > max_diff) {
                    max_diff = diff;
                }
            }
        }

        cout << max_diff << '\n';
    }

    return 0;
}
