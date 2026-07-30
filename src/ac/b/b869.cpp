#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N;
    while (cin >> N) {
        string s;
        if (!(cin >> s)) break;          // safety, should not happen
        long long dp0 = 0, dp1 = 0, dp2 = 0;   // day, dusk, night
        for (char c : s) {
            if (c == 'r') {
                ++dp0;                     // take the red
            } else if (c == 'g') {
                dp1 = max(dp0, dp1) + 1;   // take the green
            } else if (c == 'b') {
                long long best = dp0;
                if (dp1 > best) best = dp1;
                if (dp2 > best) best = dp2;
                dp2 = best + 1;            // take the blue
            }
        }
        long long ans = dp0;
        if (dp1 > ans) ans = dp1;
        if (dp2 > ans) ans = dp2;
        cout << ans << '\n';
    }
    return 0;
}
