#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        vector<int> cost(N);
        vector<int> cookies(N);
        int max_c = 0;
        for (int i = 0; i < N; ++i) {
            int a, b;
            cin >> a >> b;
            cost[i] = a;
            cookies[i] = a + b;
            if (cookies[i] > max_c) max_c = cookies[i];
        }
        
        int MAX = M + max_c;
        const int INF = INT_MAX / 2;
        vector<int> dp(MAX + 1, INF);
        dp[0] = 0;
        
        for (int i = 0; i < N; ++i) {
            int c = cookies[i];
            int a = cost[i];
            for (int j = c; j <= MAX; ++j) {
                if (dp[j - c] != INF) {
                    dp[j] = min(dp[j], dp[j - c] + a);
                }
            }
        }
        
        int ans = INF;
        for (int j = M; j <= MAX; ++j) {
            ans = min(ans, dp[j]);
        }
        cout << ans << '\n';
    }
    return 0;
}
