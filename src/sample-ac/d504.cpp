#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n) {
        int size = 1 << n;
        vector<int> weights(size);
        for (int i = 0; i < size; ++i) {
            cin >> weights[i];
        }
        
        vector<int> dp(size, -1);
        dp[0] = weights[0];
        
        for (int u = 0; u < size; ++u) {
            if (dp[u] == -1) continue;
            for (int i = 0; i < n; ++i) {
                if (!(u & (1 << i))) {
                    int v = u | (1 << i);
                    dp[v] = max(dp[v], dp[u] + weights[v]);
                }
            }
        }
        
        cout << dp[size - 1] << "\n";
    }
    
    return 0;
}
