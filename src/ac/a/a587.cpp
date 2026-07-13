#include <iostream>
#include <algorithm>

using namespace std;

int dp[10005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        int items[100][2];
        for (int i = 0; i < N; ++i) {
            cin >> items[i][0] >> items[i][1];
        }
        int limit;
        cin >> limit;
        
        for (int i = 0; i <= limit; ++i) {
            dp[i] = 0;
        }
        
        int base_v = 0;
        int max_w = 0;
        for (int i = 0; i < N; ++i) {
            int w = items[i][0];
            int v = items[i][1];
            if (w == 0) {
                base_v += v;
                continue;
            }
            if (w > limit || v == 0) {
                continue;
            }
            int upper = min(max_w + w, limit);
            for (int j = upper; j >= w; --j) {
                int val = dp[j - w] + v;
                if (val > dp[j]) {
                    dp[j] = val;
                }
            }
            max_w = upper;
        }
        
        int ans = 0;
        for (int i = 0; i <= limit; ++i) {
            if (dp[i] > ans) {
                ans = dp[i];
            }
        }
        cout << ans + base_v << "\n";
    }
    
    return 0;
}
