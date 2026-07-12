#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s1, s2;
    int case_num = 1;
    
    while (std::getline(std::cin, s1)) {
        if (s1 == "#") break;
        std::getline(std::cin, s2);
        
        int n = s1.size();
        int m = s2.size();
        
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (s1[i-1] == s2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        
        std::cout << "Case #" << case_num << ": you can visit at most " << dp[n][m] << " cities.\n";
        case_num++;
    }
    
    return 0;
}
