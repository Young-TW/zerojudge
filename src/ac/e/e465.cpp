#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M, S, N;
    while (cin >> M >> S >> N) {
        vector<int> x(N);
        int total = 0;
        for (int i = 0; i < N; ++i) {
            cin >> x[i];
            total += x[i];
        }

        int free0 = M - total;
        int need = S - free0;
        if (need <= 0) {
            cout << 0 << '\n';
            continue;
        }

        vector<char> dp(M + 1, 0);
        dp[0] = 1;
        for (int v : x) {
            if (v == 0) continue;
            for (int t = M; t >= v; --t) {
                if (dp[t - v]) dp[t] = 1;
            }
        }

        int answer = total;               // upper bound
        for (int t = need; t <= M; ++t) {
            if (dp[t]) {
                answer = t;
                break;
            }
        }
        cout << answer << '\n';
    }
    return 0;
}
