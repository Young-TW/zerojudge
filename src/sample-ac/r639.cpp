#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 2005;
const int MAXT = 1000005;

vector<int> adj[MAXN];
int t[MAXN], p[MAXN];
int in_degree[MAXN];
int dp[MAXT];
int n, m, T;

void topological_sort(vector<int>& order) {
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : adj[u]) {
            if (--in_degree[v] == 0) {
                q.push(v);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> m >> T) {
        for (int i = 1; i <= n; ++i) {
            cin >> t[i];
        }
        for (int i = 1; i <= n; ++i) {
            cin >> p[i];
        }
        for (int i = 1; i <= n; ++i) {
            adj[i].clear();
            in_degree[i] = 0;
        }
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            in_degree[v]++;
        }

        vector<int> order;
        topological_sort(order);

        memset(dp, 0, sizeof(dp));
        for (int u : order) {
            int time = t[u];
            int profit = p[u];
            for (int j = T; j >= time; --j) {
                if (dp[j - time] + profit > dp[j]) {
                    dp[j] = dp[j - time] + profit;
                }
            }
        }

        int max_profit = 0;
        for (int j = 0; j <= T; ++j) {
            if (dp[j] > max_profit) {
                max_profit = dp[j];
            }
        }
        cout << max_profit << '\n';
    }

    return 0;
}
