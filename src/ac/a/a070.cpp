#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        vector<int> x(n), y(n), c(n);
        map<pair<int,int>, int> idx;
        vector<vector<int>> adj(n);

        for (int i = 0; i < n; i++) {
            cin >> x[i] >> y[i] >> c[i];
            idx[{x[i], y[i]}] = i;
        }

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        for (int i = 0; i < n; i++) {
            for (int d = 0; d < 4; d++) {
                auto it = idx.find({x[i]+dx[d], y[i]+dy[d]});
                if (it != idx.end()) {
                    adj[i].push_back(it->second);
                }
            }
        }

        vector<long long> dp(n);
        vector<bool> visited(n, false);

        function<void(int)> dfs = [&](int u) {
            visited[u] = true;
            dp[u] = c[u];
            for (int v : adj[u]) {
                if (!visited[v]) {
                    dfs(v);
                    if (dp[v] > 0) dp[u] += dp[v];
                }
            }
        };

        dfs(0);

        long long ans = dp[0];
        for (int i = 0; i < n; i++) {
            ans = max(ans, dp[i]);
        }

        cout << ans << "\n";
    }
    return 0;
}
