#include <iostream>
#include <cstring>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const int MAX_N = 20;
    const int MAX_S = 6 * MAX_N;               // 120
    unsigned long long dp[MAX_N + 1][MAX_S + 1];
    std::memset(dp, 0, sizeof(dp));

    dp[0][0] = 1;
    for (int i = 1; i <= MAX_N; ++i) {
        for (int s = i; s <= 6 * i; ++s) {
            unsigned long long ways = 0;
            for (int k = 1; k <= 6; ++k) {
                if (s - k >= 0) ways += dp[i - 1][s - k];
            }
            dp[i][s] = ways;
        }
    }

    int K;
    if (!(std::cin >> K)) return 0;
    while (K--) {
        int N, M;
        std::cin >> N >> M;
        if (N >= 0 && N <= MAX_N && M >= 0 && M <= MAX_S)
            std::cout << dp[N][M] << '\n';
        else
            std::cout << 0 << '\n';
    }
    return 0;
}
