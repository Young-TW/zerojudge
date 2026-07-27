#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N, P, Q;
    while (cin >> N >> P >> Q) {
        vector<__int128> pref(N + 1);
        pref[0] = 0;
        for (long long i = 1; i <= N; ++i) {
            long long x;
            cin >> x;
            __int128 b = (__int128)x * Q - P;   // b[i]
            pref[i] = pref[i - 1] + b;
        }

        vector<__int128> v = pref;
        sort(v.begin(), v.end(),
             [](const __int128 &a, const __int128 &b) { return a < b; });

        unsigned long long ans = 0;
        for (size_t i = 0; i < v.size(); ) {
            size_t j = i + 1;
            while (j < v.size() && v[j] == v[i]) ++j;
            unsigned long long cnt = j - i;
            ans += cnt * (cnt - 1) / 2;
            i = j;
        }
        cout << ans << '\n';
    }
    return 0;
}
