#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MOD = 1e9 + 7;

long long dp[105][10005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    while (cin >> T) {
        while (T--) {
            int N, A, B, K;
            cin >> N >> A >> B >> K;

            if (A > B) swap(A, B);
            int g = __gcd(A, B);
            if (K % g != 0) {
                cout << "0\n";
                continue;
            }

            A /= g;
            B /= g;
            K /= g;

            int max_val = A * B;
            if (K > N * max_val) {
                cout << "0\n";
                continue;
            }

            memset(dp, 0, sizeof(dp));
            dp[0][0] = 1;
            for (int i = 1; i <= N; ++i) {
                for (int j = 0; j <= K; ++j) {
                    dp[i][j] = dp[i-1][j];
                    if (j >= A) dp[i][j] = (dp[i][j] + dp[i-1][j-A]) % MOD;
                    if (j >= B) dp[i][j] = (dp[i][j] + dp[i-1][j-B]) % MOD;
                    if (j >= A+B) dp[i][j] = (dp[i][j] + dp[i-1][j-A-B]) % MOD;
                }
            }

            cout << dp[N][K] << '\n';
        }
    }

    return 0;
}
