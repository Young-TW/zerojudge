#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int dp[205][1005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, tau, L;
    while (cin >> n >> tau >> L) {
        vector<pair<int,int>> items(n);
        for (int i = 0; i < n; i++) {
            cin >> items[i].first >> items[i].second;
        }
        // Sort by weight descending: heavier items placed closer to motor (position 1)
        sort(items.begin(), items.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
            return a.first > b.first;
        });
        
        memset(dp, -1, sizeof(dp));
        dp[0][0] = 0;
        
        for (int i = 0; i < n; i++) {
            int w = items[i].first;
            int v = items[i].second;
            for (int j = min(i, L-1); j >= 0; j--) {
                for (int t = 0; t <= tau; t++) {
                    if (dp[j][t] < 0) continue;
                    int newT = t + w * (j + 1);
                    if (newT <= tau) {
                        if (dp[j+1][newT] < dp[j][t] + v)
                            dp[j+1][newT] = dp[j][t] + v;
                    }
                }
            }
        }
        
        int ans = 0;
        for (int j = 0; j <= L; j++) {
            for (int t = 0; t <= tau; t++) {
                if (dp[j][t] > ans) ans = dp[j][t];
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
