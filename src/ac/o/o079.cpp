#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long k;
    while (cin >> n >> k) {
        vector<long long> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }

        vector<long long> sum(n + 1, 0);
        vector<int> diff(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] + a[i];
            int odd = (a[i] % 2 != 0) ? 1 : 0;
            int even = 1 - odd;
            diff[i] = diff[i - 1] + odd - even;
        }

        vector<long long> suf_sum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            suf_sum[i] = suf_sum[i - 1] + a[n - i + 1];
        }

        const int OFFSET = 8000;
        vector<set<long long>> sets(16005);

        sets[diff[n] + OFFSET].insert(0);

        long long ans = 0;

        for (int L = n; L >= 0; --L) {
            int target = diff[L] + diff[n];
            long long max_allowed = k - sum[L];
            
            if (max_allowed >= 0) {
                auto it = sets[target + OFFSET].upper_bound(max_allowed);
                if (it != sets[target + OFFSET].begin()) {
                    --it;
                    ans = max(ans, sum[L] + *it);
                }
            }

            if (L > 0) {
                int R_new = n - L + 1;
                long long sum_R_new = suf_sum[R_new];
                int diff_val = diff[L - 1];
                sets[diff_val + OFFSET].insert(sum_R_new);
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
