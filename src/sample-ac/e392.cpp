#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <climits>
using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;

const int MAXN = 100005;
const ll INF = 1e18;

vector<pair<int, ll>> adj[MAXN];
ll dist[MAXN];
ll kth[MAXN * 5];
int cnt[MAXN];

void dijkstra(int n, int start) {
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    fill(dist, dist + n + 1, INF);
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d > dist[u]) continue;
        for (auto &edge : adj[u]) {
            int v = edge.first;
            ll w = edge.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

void solve() {
    int N;
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        adj[i].clear();
    }
    for (int i = 0; i < N - 1; ++i) {
        int A, B;
        ll C;
        cin >> A >> B >> C;
        adj[A].push_back({B, C});
        adj[B].push_back({A, C});
    }

    vector<ll> all_dists;
    for (int s = 1; s <= N; ++s) {
        dijkstra(N, s);
        for (int t = 1; t <= N; ++t) {
            if (s != t) {
                all_dists.push_back(dist[t]);
            }
        }
    }

    sort(all_dists.begin(), all_dists.end());
    all_dists.erase(unique(all_dists.begin(), all_dists.end()), all_dists.end());

    int total = all_dists.size();
    for (int k = 1; k <= N; ++k) {
        int idx = 5 * k - 1;
        if (idx < total) {
            cout << all_dists[idx];
        } else {
            cout << -1;
        }
        if (k < N) cout << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
