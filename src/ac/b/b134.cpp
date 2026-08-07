#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        // Guard against a trailing sentinel / short read at EOF: a stray token
        // (e.g. a terminating "0") must not spawn an extra "0" answer line (OLE).
        if (N < 1) break;
        vector<long long> a(N);
        bool readOk = true;
        for (int i = 0; i < N; ++i) {
            if (!(cin >> a[i])) { readOk = false; break; }
        }
        if (!readOk) break;

        vector<long long> b(2 * N + 1);
        for (int i = 0; i < 2 * N; ++i) {
            b[i] = a[i % N];
        }
        b[2 * N] = a[0];

        vector<vector<long long>> dp(2 * N, vector<long long>(2 * N, 0));

        for (int len = 2; len <= N; ++len) {
            for (int i = 0; i + len - 1 < 2 * N; ++i) {
                int j = i + len - 1;
                long long best = 0;
                for (int k = i; k < j; ++k) {
                    long long cur = dp[i][k] + dp[k + 1][j] + b[i] * b[k + 1] * b[j + 1];
                    if (cur > best) {
                        best = cur;
                    }
                }
                dp[i][j] = best;
            }
        }

        long long answer = 0;
        for (int s = 0; s < N; ++s) {
            answer = max(answer, dp[s][s + N - 1]);
        }

        cout << answer << '\n';
    }

    return 0;
}
