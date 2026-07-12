#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        while (N--) {
            string s;
            cin >> s;
            int n = s.length();
            vector<long long> dp(n + 1, -1);
            dp[0] = 0;
            
            for (int i = 1; i <= n; ++i) {
                for (int j = max(0, i - 10); j < i; ++j) {
                    if (s[j] == '0' && i - j > 1) continue;
                    if (dp[j] == -1) continue;
                    
                    long long val = 0;
                    for (int k = j; k < i; ++k) {
                        val = val * 10 + (s[k] - '0');
                    }
                    
                    if (val <= 2147483647LL) {
                        if (dp[j] + val > dp[i]) {
                            dp[i] = dp[j] + val;
                        }
                    }
                }
            }
            cout << dp[n] << "\n";
        }
    }
    return 0;
}
