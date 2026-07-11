#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long dp[25][125] = {0};
    dp[0][0] = 1;
    for (int i = 1; i <= 20; ++i) {
        for (int j = i; j <= 6 * i; ++j) {
            for (int k = 1; k <= 6; ++k) {
                if (j - k >= 0) {
                    dp[i][j] += dp[i - 1][j - k];
                }
            }
        }
    }

    int K;
    while (cin >> K) {
        while (K--) {
            int N, M;
            cin >> N >> M;
            if (N >= 0 && N <= 20 && M >= 0 && M <= 120) {
                cout << dp[N][M] << "\n";
            } else {
                cout << 0 << "\n";
            }
        }
    }

    return 0;
}
