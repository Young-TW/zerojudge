#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128  = __int128_t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, caseNo = 1;
    while (cin >> N) {
        if (N == 0) break;
        vector<int64> p(N + 1);
        for (int i = 0; i < N; ++i) {
            int64 r, c;
            cin >> r >> c;
            if (i == 0) p[0] = r;
            p[i + 1] = c;
        }

        const int64 INF = (int64)4e18;          // larger than any possible cost
        static int64 dp[11][11];
        static int split[11][11];

        for (int i = 1; i <= N; ++i) dp[i][i] = 0;

        for (int len = 2; len <= N; ++len) {
            for (int i = 1; i + len - 1 <= N; ++i) {
                int j = i + len - 1;
                dp[i][j] = INF;
                for (int k = i; k < j; ++k) {
                    i128 mult = (i128)p[i - 1] * p[k] * p[j];
                    i128 cand = (i128)dp[i][k] + dp[k + 1][j] + mult;
                    if (cand <= dp[i][j]) {          // <=  → rightmost optimal split
                        dp[i][j] = (int64)cand;
                        split[i][j] = k;
                    }
                }
            }
        }

        function<string(int,int)> build = [&](int i, int j) -> string {
            if (i == j) return "A" + to_string(i);
            int k = split[i][j];
            return "(" + build(i, k) + " x " + build(k + 1, j) + ")";
        };

        cout << "Case " << caseNo++ << ": " << build(1, N) << "\n";
    }
    return 0;
}
