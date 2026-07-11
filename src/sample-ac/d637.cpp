#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        int dp[101];
        memset(dp, 0, sizeof(dp));
        
        for (int i = 0; i < n; ++i) {
            int a, b;
            cin >> a >> b;
            for (int j = 100; j >= a; --j) {
                dp[j] = max(dp[j], dp[j - a] + b);
            }
        }
        
        cout << dp[100] << "\n";
    }
    
    return 0;
}
