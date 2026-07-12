#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<int> a(n);
        long long total = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            total += a[i];
        }
        int m;
        cin >> m;
        
        const long long INF = (long long)4e18;
        vector<long long> dp(n + 1, INF);
        dp[0] = 0;
        
        for (int i = 1; i <= n; i++) {
            long long sum = 0;
            for (int j = i - 1; j >= 0; j--) {
                sum += a[j];
                if (sum > m) break;
                if (dp[j] < INF) {
                    long long cost = (long long)(m - sum) * (m - sum);
                    if (dp[j] + cost < dp[i]) {
                        dp[i] = dp[j] + cost;
                    }
                }
            }
        }
        
        if (dp[n] > total) {
            cout << "QQ" << "\n";
        } else {
            cout << total - dp[n] << "\n";
        }
    }
    
    return 0;
}
