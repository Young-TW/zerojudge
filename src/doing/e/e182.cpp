#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<int> s(n);
        for (int i = 0; i < n; ++i) cin >> s[i];
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            int curMin = s[i], curMax = s[i];
            for (int j = i + 1; j < n; ++j) {
                if (s[j] < curMin) curMin = s[j];
                if (s[j] > curMax) curMax = s[j];
                if (curMax - curMin != j - i) continue; // not consecutive
                // endpoints must be the min and max (order irrelevant)
                if ((s[i] == curMin && s[j] == curMax) ||
                    (s[i] == curMax && s[j] == curMin)) {
                    ++ans;
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
