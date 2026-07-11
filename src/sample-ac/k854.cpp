#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

long long dp[55][55];

int main() {
    int n, k;
    while (cin >> n >> k) {
        vector<int> a(k);
        int sum_len = 0;
        for (int i = 0; i < k; ++i) {
            cin >> a[i];
            sum_len += a[i];
        }

        int min_space = k - 1;
        if (sum_len + min_space > n) {
            cout << 0 << endl;
            continue;
        }

        int free_space = n - sum_len - min_space;

        for (int i = 0; i <= free_space; ++i) {
            for (int j = 0; j <= k; ++j) {
                dp[i][j] = 0;
            }
        }

        for (int i = 0; i <= free_space; ++i) {
            dp[i][0] = 1;
        }

        for (int j = 1; j <= k; ++j) {
            for (int i = 0; i <= free_space; ++i) {
                long long ways = 0;
                for (int x = 0; x <= i; ++x) {
                    ways += dp[x][j-1];
                }
                dp[i][j] = ways;
            }
        }

        cout << dp[free_space][k] << endl;
    }
    return 0;
}
