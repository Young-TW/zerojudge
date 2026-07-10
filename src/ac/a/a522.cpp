#include <iostream>
#include <cstring>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, p;
        cin >> n >> p;
        int bars[25];
        for (int i = 0; i < p; i++) cin >> bars[i];
        bool dp[1001];
        memset(dp, false, sizeof(dp));
        dp[0] = true;
        for (int i = 0; i < p; i++) {
            for (int j = n; j >= bars[i]; j--) {
                if (dp[j - bars[i]]) dp[j] = true;
            }
        }
        cout << (dp[n] ? "YES" : "NO") << "\n";
    }
    return 0;
}
