#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K;
    while (cin >> N >> K) {
        vector<long long> a(N + 1);
        for (int i = 1; i <= N; ++i) {
            cin >> a[i];
        }
        
        vector<long long> dp(N + 1, 0);
        deque<int> q;
        
        for (int i = 1; i <= N; ++i) {
            int left_bound = i - K;
            while (!q.empty() && q.front() < left_bound) {
                q.pop_front();
            }
            long long base = q.empty() ? 0 : dp[q.front()];
            // 當 i <= K 時，i 可以是第一個被蓋的數字（前面不需要任何覆蓋），
            // 也可以額外蓋前面的（負數）數字，故取 min(base, 0)。
            if (i <= K && base > 0) base = 0;
            dp[i] = a[i] + base;

            while (!q.empty() && dp[q.back()] >= dp[i]) {
                q.pop_back();
            }
            q.push_back(i);
        }
        
        long long ans = dp[max(1, N - K + 1)];
        for (int i = max(1, N - K + 1) + 1; i <= N; ++i) {
            ans = min(ans, dp[i]);
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
