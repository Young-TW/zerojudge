#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    while (cin >> n >> k) {
        vector<long long> a(n + 1);
        vector<long long> S(n + 1, 0);
        
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            S[i] = S[i - 1] + a[i];
        }
        
        vector<long long> dp(n + 1, 0);
        deque<int> q;
        q.push_back(0);
        
        for (int i = 1; i <= n; ++i) {
            int j = i - 1;
            while (!q.empty() && dp[j] - S[j] >= dp[q.back()] - S[q.back()]) {
                q.pop_back();
            }
            q.push_back(j);
            
            while (!q.empty() && q.front() < i - k - 1) {
                q.pop_front();
            }
            
            int best_j = q.front();
            dp[i] = dp[best_j] - S[best_j] + S[i - 1];
        }
        
        long long ans = 0;
        for (int j = n - k; j <= n; ++j) {
            if (j < 0) continue;
            ans = max(ans, dp[j] + S[n] - S[j]);
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
