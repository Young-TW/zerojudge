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
            if (i <= K) {
                dp[i] = a[i];
            } else {
                int left_bound = i - K;
                while (!q.empty() && q.front() < left_bound) {
                    q.pop_front();
                }
                dp[i] = a[i] + dp[q.front()];
            }
            
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
