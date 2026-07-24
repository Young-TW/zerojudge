#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    while (cin >> N >> K) {
        int M = N / K;
        vector<int> val(N);
        for (int i = 0; i < N; ++i) {
            cin >> val[i];
        }

        int size = 1 << N;
        vector<int> sum(size, 0);
        for (int mask = 1; mask < size; ++mask) {
            int lb = mask & -mask;
            int i = __builtin_ctz(lb);
            sum[mask] = sum[mask ^ lb] + val[i];
        }

        vector<long long> dp(size, 0);
        dp[0] = 1;

        for (int mask = 1; mask < size; ++mask) {
            if (__builtin_popcount(mask) % M != 0) continue;
            int lb = mask & -mask;
            for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
                if ((sub & lb) && __builtin_popcount(sub) == M) {
                    dp[mask] = max(dp[mask], dp[mask ^ sub] * sum[sub]);
                }
            }
        }

        cout << dp[size - 1] << "\n";
    }

    return 0;
}
