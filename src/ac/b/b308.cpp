#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int a[5], b[5], p;
        for (int i = 0; i < 5; ++i) cin >> a[i];
        for (int i = 0; i < 5; ++i) cin >> b[i];
        cin >> p;
        
        int v[5] = {1, 5, 10, 50, 100};
        int V_inko = 0;
        for (int i = 0; i < 5; ++i) {
            V_inko += a[i] * v[i];
        }
        
        int K = V_inko - p;
        
        if (K < 0) {
            cout << "I HAVE MAGIC!\n";
            continue;
        }
        
        int c[5];
        for (int i = 0; i < 5; ++i) {
            c[i] = a[i] + b[i];
        }
        
        const int INF = 1e9;
        vector<int> dp(K + 1, INF);
        dp[0] = 0;
        
        for (int i = 0; i < 5; ++i) {
            int cnt = c[i];
            int val = v[i];
            for (int k = 1; cnt > 0; k <<= 1) {
                int take = min(k, cnt);
                cnt -= take;
                int weight = take * val;
                for (int j = K; j >= weight; --j) {
                    if (dp[j - weight] != INF) {
                        dp[j] = min(dp[j], dp[j - weight] + take);
                    }
                }
            }
        }
        
        if (dp[K] == INF) {
            cout << "YOU ARE MAGICIAN!\n";
        } else {
            cout << dp[K] << "\n";
        }
    }
    
    return 0;
}
