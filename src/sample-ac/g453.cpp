#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        while (N--) {
            string s;
            cin >> s;
            int L = s.length();
            vector<long long> dp(L + 1, -1);
            dp[0] = 0;
            for (int i = 1; i <= L; ++i) {
                for (int j = i - 1; j >= max(0, i - 10); --j) {
                    if (dp[j] == -1) continue;
                    if (i - j > 1 && s[j] == '0') continue;
                    long long val = 0;
                    for (int k = j; k < i; ++k) {
                        val = val * 10 + (s[k] - '0');
                    }
                    if (val > 2147483647LL) continue;
                    dp[i] = max(dp[i], dp[j] + val);
                }
            }
            cout << dp[L] << "\n";
        }
    }
    return 0;
}
