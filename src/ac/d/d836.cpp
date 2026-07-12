#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m) {
        long long a[105];
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            a[i + n] = a[i];
        }
        
        long long prefix[105];
        prefix[0] = 0;
        for (int i = 0; i < 2 * n; ++i) {
            prefix[i + 1] = prefix[i] + a[i];
        }
        
        const long long INF = 1e18;
        long long dp_min[105][105][10];
        long long dp_max[105][105][10];
        
        for (int i = 0; i < 2 * n; ++i) {
            for (int j = 0; j < 2 * n; ++j) {
                for (int k = 0; k <= m; ++k) {
                    dp_min[i][j][k] = INF;
                    dp_max[i][j][k] = -INF;
                }
            }
        }
        
        for (int len = 1; len <= 2 * n; ++len) {
            for (int i = 0; i + len - 1 < 2 * n; ++i) {
                int j = i + len - 1;
                long long sum = prefix[j + 1] - prefix[i];
                long long mod_sum = (sum % 10 + 10) % 10;
                dp_min[i][j][1] = mod_sum;
                dp_max[i][j][1] = mod_sum;
                for (int k = 2; k <= m; ++k) {
                    for (int p = i; p < j; ++p) {
                        if (dp_min[i][p][1] != INF && dp_min[p + 1][j][k - 1] != INF) {
                            dp_min[i][j][k] = min(dp_min[i][j][k], dp_min[i][p][1] * dp_min[p + 1][j][k - 1]);
                        }
                        if (dp_max[i][p][1] != -INF && dp_max[p + 1][j][k - 1] != -INF) {
                            dp_max[i][j][k] = max(dp_max[i][j][k], dp_max[i][p][1] * dp_max[p + 1][j][k - 1]);
                        }
                    }
                }
            }
        }
        
        long long ans_min = INF;
        long long ans_max = -INF;
        for (int i = 0; i < n; ++i) {
            if (dp_min[i][i + n - 1][m] < ans_min) {
                ans_min = dp_min[i][i + n - 1][m];
            }
            if (dp_max[i][i + n - 1][m] > ans_max) {
                ans_max = dp_max[i][i + n - 1][m];
            }
        }
        
        cout << ans_min << "\n" << ans_max << "\n";
    }
    
    return 0;
}
