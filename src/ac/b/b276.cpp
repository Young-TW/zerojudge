#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    while (cin >> n >> m) {
        vector<int> medicine(m + 1, 0);
        for (int i = 0; i < n; ++i) {
            int a, b;
            cin >> a >> b;
            if (b <= m) {
                medicine[b] += a;
            }
        }

        vector<long long> dp(m + 1, -1);
        dp[0] = 0;

        long long max_medicine = 0;

        for (int i = 0; i <= m; ++i) {
            if (dp[i] == -1) continue;

            long long current_total = dp[i] + medicine[i];
            if (current_total > max_medicine) {
                max_medicine = current_total;
            }

            int next_pos_4 = i + 4;
            if (next_pos_4 <= m) {
                if (dp[next_pos_4] < current_total) {
                    dp[next_pos_4] = current_total;
                }
            }

            int next_pos_7 = i + 7;
            if (next_pos_7 <= m) {
                if (dp[next_pos_7] < current_total) {
                    dp[next_pos_7] = current_total;
                }
            }
        }

        cout << max_medicine << "\n";
    }

    return 0;
}
