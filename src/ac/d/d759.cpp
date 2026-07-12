#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;

    const long long INF = 1e18;

    while (T--) {
        int K, N;
        cin >> K >> N;
        vector<int> L(N + 1);
        for (int i = 1; i <= N; ++i) {
            cin >> L[i];
        }

        int groups = K + 8;
        vector<vector<long long>> dp(3, vector<long long>(groups + 1, INF));
        
        dp[(N + 1) % 3][0] = 0;

        for (int i = N; i >= 1; --i) {
            int curr = i % 3;
            int next = (i + 1) % 3;
            int next2 = (i + 2) % 3;
            
            int max_j = min(groups, (N - i + 1) / 3);
            for (int j = 0; j <= groups; ++j) {
                dp[curr][j] = INF;
            }
            for (int j = 0; j <= max_j; ++j) {
                dp[curr][j] = dp[next][j];
                if (j > 0 && i + 1 <= N) {
                    long long badness = (long long)(L[i] - L[i + 1]) * (L[i] - L[i + 1]);
                    if (dp[next2][j - 1] != INF) {
                        dp[curr][j] = min(dp[curr][j], dp[next2][j - 1] + badness);
                    }
                }
            }
        }

        cout << dp[1 % 3][groups] << "\n";
    }

    return 0;
}
