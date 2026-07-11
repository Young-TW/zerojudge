#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;
int dp[100005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 1;
    for (int i = 3; i <= 100000; ++i) {
        dp[i] = (dp[i - 1] + dp[i - 3]) % MOD;
    }
    
    int n, m;
    while (cin >> n >> m) {
        vector<int> a(m);
        for (int i = 0; i < m; ++i) {
            cin >> a[i];
        }
        
        long long ans = 1;
        int prev = 0;
        for (int i = 0; i < m; ++i) {
            int len = a[i] - prev;
            ans = (ans * dp[len]) % MOD;
            prev = a[i];
        }
        int len = n - prev;
        ans = (ans * dp[len]) % MOD;
        
        cout << ans << "\n";
    }
    
    return 0;
}
