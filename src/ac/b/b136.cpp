#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n;
    while (cin >> m >> n) {
        int total_ops = m * n;
        vector<int> order(total_ops);
        for (int i = 0; i < total_ops; ++i) {
            cin >> order[i];
            order[i]--; // 轉為 0-indexed
        }

        vector<vector<int>> machine_id(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> machine_id[i][j];
                machine_id[i][j]--; // 轉為 0-indexed
            }
        }

        vector<vector<int>> time_cost(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> time_cost[i][j];
            }
        }

        vector<int> step(n, 0);
        vector<int> last_end(n, 0);
        
        vector<vector<pair<int, int>>> intervals(m);

        for (int i = 0; i < total_ops; ++i) {
            int w = order[i];
            int s = step[w];
            int mac = machine_id[w][s];
            int t = time_cost[w][s];

            int S = last_end[w];
            for (const auto& p : intervals[mac]) {
                int L = p.first;
                int R = p.second;
                if (S + t <= L) {
                    break; // 找到可用的空檔
                }
                if (S < R) {
                    S = R; // 將開始時間移到當前佔用區間之後
                }
            }

            intervals[mac].push_back({S, S + t});
            sort(intervals[mac].begin(), intervals[mac].end());

            last_end[w] = S + t;
            step[w]++;
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, last_end[i]);
        }
        cout << ans << "\n";
    }

    return 0;
}
