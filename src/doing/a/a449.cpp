#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, m;
    while (cin >> n >> k >> m) {
        vector<int> w(n);
        for (int i = 0; i < n; ++i) {
            cin >> w[i];
        }

        vector<int> dp(k + 1, 0);
        vector<int> sum(k + 1, 0);

        for (int i = 0; i < n; ++i) {
            for (int j = k; j >= 1; --j) {
                if (sum[j] + w[i] <= m) {
                    if (dp[j] < dp[j - 1] + 1) {
                        dp[j] = dp[j - 1] + 1;
                        sum[j] += w[i];
                    }
                } else {
                    int new_sum = w[i];
                    int new_count = 1;
                    for (int l = i - 1; l >= dp[j - 1]; --l) {
                        if (new_sum + w[l] <= m) {
                            new_sum += w[l];
                            new_count++;
                        } else {
                            break;
                        }
                    }
                    if (dp[j] < dp[j - 1] + new_count) {
                        dp[j] = dp[j - 1] + new_count;
                        sum[j] = new_sum;
                    }
                }
            }
        }

        cout << dp[k] << '\n';
    }

    return 0;
}
