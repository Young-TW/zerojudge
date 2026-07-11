#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, m;
    while (cin >> N >> m) {
        vector<int> dp(N + 1, 0);
        for (int i = 0; i < m; ++i) {
            int v, p;
            cin >> v >> p;
            int val = v * p;
            for (int j = N; j >= v; --j) {
                if (dp[j - v] + val > dp[j]) {
                    dp[j] = dp[j - v] + val;
                }
            }
        }
        cout << dp[N] << "\n";
    }
    
    return 0;
}
