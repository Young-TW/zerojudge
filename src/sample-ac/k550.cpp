#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) == 2) {
        for (int i = 0; i < M; ++i) {
            int S, R;
            scanf("%d %d", &S, &R);
            vector<int> prices(N);
            for (int j = 0; j < N; ++j) {
                scanf("%d", &prices[j]);
            }
            long long ans_cents;
            if (S >= N) {
                ans_cents = 0;
                for (int p : prices) {
                    long long full = p * 100LL;
                    long long disc = p * 1LL * R;
                    ans_cents += min(full, disc);
                }
            } else {
                const long long INF = (1LL << 60);
                vector<long long> dp(S + 1, INF), new_dp(S + 1, INF);
                dp[0] = 0;
                for (int p : prices) {
                    fill(new_dp.begin(), new_dp.end(), INF);
                    long long full = p * 100LL;
                    long long disc = p * 1LL * R;
                    for (int s = 0; s <= S; ++s) {
                        if (dp[s] == INF) continue;
                        // Pay full price
                        int ns_full = (s < S) ? s + 1 : S;
                        new_dp[ns_full] = min(new_dp[ns_full], dp[s] + full);
                        // Pay discounted price
                        new_dp[s] = min(new_dp[s], dp[s] + disc);
                        // Use free meal
                        if (s == S) {
                            new_dp[0] = min(new_dp[0], dp[s]);
                        }
                    }
                    dp.swap(new_dp);
                }
                ans_cents = *min_element(dp.begin(), dp.end());
            }
            printf("%lld.%02lld\n", ans_cents / 100, ans_cents % 100);
        }
    }
    return 0;
}
