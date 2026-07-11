#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;
int dp[2][512][10];
int ans[1005][10];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(dp, 0, sizeof(dp));
    for (int d = 1; d <= 9; ++d) {
        dp[1][1 << (d - 1)][d] = 1;
    }

    for (int i = 1; i <= 1000; ++i) {
        for (int d = 1; d <= 9; ++d) {
            ans[i][d] = dp[i % 2][511][d];
        }

        if (i == 1000) break;

        memset(dp[(i + 1) % 2], 0, sizeof(dp[(i + 1) % 2]));

        for (int mask = 0; mask < 512; ++mask) {
            for (int last = 1; last <= 9; ++last) {
                if (dp[i % 2][mask][last] == 0) continue;
                for (int next = max(1, last - 2); next <= min(9, last + 2); ++next) {
                    int next_mask = mask | (1 << (next - 1));
                    dp[(i + 1) % 2][next_mask][next] = (dp[(i + 1) % 2][next_mask][next] + dp[i % 2][mask][last]) % MOD;
                }
            }
        }
    }

    int N;
    while (cin >> N) {
        while (N--) {
            int P, Q;
            cin >> P >> Q;
            cout << ans[P][Q] << "\n";
        }
    }

    return 0;
}
