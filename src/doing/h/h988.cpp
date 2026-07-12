#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <climits>
using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;

const ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, b, s;
    cin >> n >> m >> a >> b >> s;
    s--;

    vector<int> d(n), c(n);
    for (int i = 0; i < n; i++) cin >> d[i];
    for (int i = 0; i < n; i++) cin >> c[i];

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        x--; y--;
        adj[x].emplace_back(y, w);
        adj[y].emplace_back(x, w);
    }

    vector<ll> dist(n, INF);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[s] = 0;
    pq.emplace(0, s);

    while (!pq.empty()) {
        auto [current_dist, u] = pq.top();
        pq.pop();
        if (current_dist > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }

    vector<ll> original(n), transformed(n);
    for (int i = 0; i < n; i++) {
        original[i] = dist[i];
        transformed[i] = (ll)d[i] * dist[i] + c[i];
    }

    vector<ll> diff(n);
    for (int i = 0; i < n; i++) {
        diff[i] = transformed[i] - original[i];
    }

    vector<ll> all_vals;
    for (int i = 0; i < n; i++) {
        if (i == s) continue;
        all_vals.push_back(original[i]);
    }

    sort(all_vals.begin(), all_vals.end(), greater<ll>());
    sort(diff.begin(), diff.end(), greater<ll>());

    ll sum_original = 0;
    for (int i = 0; i < a; i++) {
        if (i < all_vals.size()) {
            sum_original += all_vals[i];
        }
    }

    ll max_diff = 0;
    ll current_diff = 0;
    for (int i = 0; i < b; i++) {
        current_diff += diff[i];
    }
    max_diff = current_diff;

    for (int i = b; i < n; i++) {
        current_diff += diff[i];
        current_diff -= diff[i - b];
        if (current_diff > max_diff) {
            max_diff = current_diff;
        }
    }

    cout << sum_original + max_diff << '\n';

    return 0;
}
