#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int n;
            cin >> n;
            vector<int> a(n);
            for (int i = 0; i < n; ++i) {
                cin >> a[i];
            }
            sort(a.begin(), a.end());
            int max_val = a.back();
            vector<bool> dp(max_val + 1, false);
            dp[0] = true;
            int ans = 0;
            for (int i = 0; i < n; ++i) {
                if (dp[a[i]]) continue;
                ans++;
                for (int j = a[i]; j <= max_val; ++j) {
                    if (dp[j - a[i]]) {
                        dp[j] = true;
                    }
                }
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
