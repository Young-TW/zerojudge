#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MOD = 998244353;
const int MAXK = 200000;

vector<int> a;
int n, m, k;
int cnt[MAXK + 10];
int dp[MAXK + 10];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> m >> k) {
        a.resize(m);
        for (int i = 0; i < m; i++) {
            cin >> a[i];
        }

        memset(cnt, 0, sizeof(cnt));
        cnt[0] = 1;

        for (int i = 0; i < n; i++) {
            memset(dp, 0, sizeof(dp));
            for (int j = 0; j <= k; j++) {
                if (cnt[j]) {
                    dp[j] = (dp[j] + cnt[j]) % MOD;
                    for (int x : a) {
                        if (j + x <= k) {
                            dp[j + x] = (dp[j + x] + cnt[j]) % MOD;
                        }
                    }
                }
            }
            memcpy(cnt, dp, sizeof(dp));
        }

        int res = 0;
        for (int i = 0; i <= k; i++) {
            res ^= cnt[i];
        }
        cout << res << '\n';
    }

    return 0;
}
