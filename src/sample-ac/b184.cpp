#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<int> dp(101, 0);
        for (int i = 0; i < n; ++i) {
            int v, c;
            cin >> v >> c;
            for (int j = 100; j >= v; --j) {
                dp[j] = max(dp[j], dp[j - v] + c);
            }
        }
        cout << dp[100] << "\n";
    }
    
    return 0;
}
