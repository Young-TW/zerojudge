#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    while (cin >> n >> m) {
        vector<int> out_deg(n + 1, 0);
        vector<int> in_deg(n + 1, 0);
        vector<int> to(n + 1, 0);
        vector<int> weight(n + 1, 0);
        vector<bool> visited(n + 1, false);

        for (int i = 0; i < m; i++) {
            int a, b, w;
            cin >> a >> b >> w;
            out_deg[a]++;
            in_deg[b]++;
            to[a] = b;
            weight[a] = w;
        }

        long long ans = 0;

        for (int i = 1; i <= n; i++) {
            if (in_deg[i] == 0 && out_deg[i] > 0) {
                long long current_sum = 0;
                int u = i;
                while (u != 0 && out_deg[u] > 0) {
                    if (visited[u]) break;
                    visited[u] = true;
                    current_sum += weight[u];
                    if (current_sum < 0) current_sum = 0;
                    ans = max(ans, current_sum);
                    u = to[u];
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            if (out_deg[i] > 0 && !visited[i]) {
                vector<long long> weights;
                int u = i;
                while (u != 0 && out_deg[u] > 0 && !visited[u]) {
                    visited[u] = true;
                    weights.push_back(weight[u]);
                    u = to[u];
                }
                
                long long total_sum = 0;
                for (long long w : weights) total_sum += w;

                long long max_sum = 0;
                long long current_sum = 0;
                for (long long w : weights) {
                    current_sum += w;
                    if (current_sum < 0) current_sum = 0;
                    max_sum = max(max_sum, current_sum);
                }

                long long min_sum = 0;
                current_sum = 0;
                for (long long w : weights) {
                    current_sum += w;
                    if (current_sum > 0) current_sum = 0;
                    min_sum = min(min_sum, current_sum);
                }

                long long cycle_max = max(max_sum, total_sum - min_sum);
                ans = max(ans, cycle_max);
            }
        }

        cout << ans << "\n";
    }
    return 0;
}
