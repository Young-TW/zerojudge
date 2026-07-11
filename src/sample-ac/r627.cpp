#include <iostream>
#include <algorithm>

using namespace std;

int n;
int s[8], d[8], t[8];
int dp[1 << 8];

bool check(int G) {
    for (int i = 0; i < (1 << n); ++i) {
        dp[i] = 1e9;
    }
    for (int i = 0; i < n; ++i) {
        if (s[i] + t[i] <= d[i]) {
            dp[1 << i] = s[i] + t[i];
        }
    }
    for (int mask = 1; mask < (1 << n); ++mask) {
        if (dp[mask] == 1e9) continue;
        for (int i = 0; i < n; ++i) {
            if (!(mask & (1 << i))) {
                int next_mask = mask | (1 << i);
                int start_time = max(s[i], dp[mask] + G);
                int end_time = start_time + t[i];
                if (end_time <= d[i]) {
                    if (end_time < dp[next_mask]) {
                        dp[next_mask] = end_time;
                    }
                }
            }
        }
    }
    return dp[(1 << n) - 1] != 1e9;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            cin >> s[i] >> d[i] >> t[i];
        }
        int low = 0, high = 1000, ans = 0;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (check(mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
