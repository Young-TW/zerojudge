#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 1e9;

int main() {
    int m, n;
    if (!(cin >> m >> n)) return 0;

    vector<int> treasures(n);
    for (int i = 0; i < n; ++i) {
        cin >> treasures[i];
        treasures[i]--; 
    }

    vector<vector<int>> dist(m, vector<int>(m));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> dist[i][j];
            if (dist[i][j] == 0 && i != j) {
                dist[i][j] = INF;
            }
        }
    }

    for (int k = 0; k < m; ++k) {
        for (int i = 0; i < m; ++i) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < m; ++j) {
                if (dist[k][j] == INF) continue;
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    int start_node = 0; 
    int end_node = m - 1; 

    vector<int> actual_treasures;
    for (int t : treasures) {
        if (t != start_node && t != end_node) {
            actual_treasures.push_back(t);
        }
    }

    int k = actual_treasures.size();
    int limit = 1 << k;
    
    vector<vector<int>> dp(limit, vector<int>(k + 2, INF));

    int start_mask = 0;
    int start_state_idx = k; 
    
    if (dist[start_node][end_node] == INF && k == 0) {
         cout << 0 << endl;
         return 0;
    }

    if (k == 0) {
        if (dist[start_node][end_node] >= INF) {
             cout << 0 << endl; 
        } else {
             cout << dist[start_node][end_node] << endl;
        }
        return 0;
    }

    dp[0][k] = 0;

    for (int mask = 0; mask < limit; ++mask) {
        for (int last = 0; last <= k; ++last) {
            if (dp[mask][last] == INF) continue;

            int current_u;
            if (last == k) {
                current_u = start_node;
            } else {
                current_u = actual_treasures[last];
            }

            for (int next_idx = 0; next_idx < k; ++next_idx) {
                if ((mask & (1 << next_idx)) == 0) {
                    int next_v = actual_treasures[next_idx];
                    if (dist[current_u][next_v] < INF) {
                        int new_mask = mask | (1 << next_idx);
                        if (dp[new_mask][next_idx] > dp[mask][last] + dist[current_u][next_v]) {
                            dp[new_mask][next_idx] = dp[mask][last] + dist[current_u][next_v];
                        }
                    }
                }
            }
        }
    }

    int ans = INF;
    int full_mask = limit - 1;

    for (int last = 0; last < k; ++last) {
        if (dp[full_mask][last] == INF) continue;
        int u = actual_treasures[last];
        if (dist[u][end_node] < INF) {
            int total = dp[full_mask][last] + dist[u][end_node];
            if (total < ans) {
                ans = total;
            }
        }
    }

    if (ans >= INF) {
        cout << 0 << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}
