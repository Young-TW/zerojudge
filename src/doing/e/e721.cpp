#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<long long> a(n);
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            sum += a[i];
        }
        
        if (n == 0) {
            cout << 0 << "\n";
            continue;
        }
        
        // dp[i] = 區間 [i, i+len-1] 中先手比後手多拿的最大值（滾動陣列）
        vector<long long> dp(n), ndp(n);
        for (int i = 0; i < n; i++) dp[i] = a[i];
        
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len <= n; i++) {
                int j = i + len - 1;
                ndp[i] = max(a[i] - dp[i+1], a[j] - dp[i]);
            }
            swap(dp, ndp);
        }
        
        cout << (sum + dp[0]) / 2 << "\n";
    }
    
    return 0;
}
