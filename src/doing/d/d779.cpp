#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
int price[MAXN];
vector<int> adj[MAXN];
vector<int> rev_adj[MAXN];
int minCost[MAXN];
int maxCost[MAXN];
bool vis[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    while (cin >> n >> m) {
        for (int i = 1; i <= n; ++i) {
            cin >> price[i];
            adj[i].clear();
            rev_adj[i].clear();
        }
        for (int i = 0; i < m; ++i) {
            int u, v, z;
            cin >> u >> v >> z;
            adj[u].push_back(v);
            rev_adj[v].push_back(u);
            if (z == 2) {
                adj[v].push_back(u);
                rev_adj[u].push_back(v);
            }
        }

        for (int i = 1; i <= n; ++i) {
            minCost[i] = 1e9;
            maxCost[i] = -1;
            vis[i] = false;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq_min;
        minCost[1] = price[1];
        pq_min.push({minCost[1], 1});
        while (!pq_min.empty()) {
            int d = pq_min.top().first;
            int u = pq_min.top().second;
            pq_min.pop();
            if (vis[u]) continue;
            vis[u] = true;
            for (int v : adj[u]) {
                int new_cost = min(d, price[v]);
                if (new_cost < minCost[v]) {
                    minCost[v] = new_cost;
                    pq_min.push({minCost[v], v});
                }
            }
        }

        for (int i = 1; i <= n; ++i) vis[i] = false;
        priority_queue<pair<int, int>> pq_max;
        maxCost[n] = price[n];
        pq_max.push({maxCost[n], n});
        while (!pq_max.empty()) {
            int d = pq_max.top().first;
            int u = pq_max.top().second;
            pq_max.pop();
            if (vis[u]) continue;
            vis[u] = true;
            for (int v : rev_adj[u]) {
                int new_cost = max(d, price[v]);
                if (new_cost > maxCost[v]) {
                    maxCost[v] = new_cost;
                    pq_max.push({maxCost[v], v});
                }
            }
        }

        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (maxCost[i] != -1 && minCost[i] != 1e9) {
                ans = max(ans, maxCost[i] - minCost[i]);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
