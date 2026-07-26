#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int T;
    if (!(std::cin >> T)) return 0;
    while (T--) {
        int k, m, n;
        std::cin >> k;
        std::cin >> m >> n;
        if (m > n) std::swap(m, n);               // optional, not required
        
        std::vector<char> dp(k + 1, 0);
        dp[0] = 1;
        for (int i = 0; i <= k; ++i) {
            if (!dp[i]) continue;
            if (i + m <= k) dp[i + m] = 1;
            if (i + n <= k) dp[i + n] = 1;
        }
        
        int answer = -1;
        for (int i = k; i >= 1; --i) {
            if (!dp[i]) {
                answer = i;
                break;
            }
        }
        if (answer == -1)
            std::cout << "good\n";
        else
            std::cout << answer << '\n';
    }
    return 0;
}
