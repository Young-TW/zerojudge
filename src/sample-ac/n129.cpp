#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    unsigned long long dp[75] = {0};
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= 71; ++i) {
        dp[i] = dp[i-1] + dp[i-2] + dp[i-3];
    }
    
    int n;
    while (std::cin >> n) {
        if (n >= 0 && n <= 71) {
            std::cout << dp[n] << "\n";
        }
    }
    return 0;
}
