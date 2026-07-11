#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<long long> dp(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                long long x;
                cin >> x;
                dp[j + 1] = max(dp[j + 1], dp[j]) + x;
            }
        }
        cout << dp[n] << "\n";
    }
    
    return 0;
}
