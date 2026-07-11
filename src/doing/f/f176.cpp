#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int k;
        cin >> k;
        int m, n;
        cin >> m >> n;

        if (m > n) swap(m, n);
        int g = gcd(m, n);
        if (g != 1) {
            cout << "good\n";
            continue;
        }

        vector<bool> dp(k + 1, false);
        dp[0] = true;
        for (int i = 1; i <= k; ++i) {
            if (i >= m && dp[i - m]) dp[i] = true;
            if (i >= n && dp[i - n]) dp[i] = true;
        }

        int ans = -1;
        for (int i = k; i >= 0; --i) {
            if (!dp[i]) {
                ans = i;
                break;
            }
        }

        if (ans == -1) {
            cout << "good\n";
        } else {
            cout << ans << '\n';
        }
    }

    return 0;
}
