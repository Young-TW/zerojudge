#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // night surcharge for each hour, 0 otherwise
    long long night[24] = {0};
    for (int h = 18; h <= 23; ++h) {
        night[h] = 185 + (h - 18) * 10;   // 185,195,205,215,225,235
    }

    long long d, t, s, e;
    while (cin >> d >> t >> s >> e) {
        long long ans = 20;                     // base fare
        if (d > 2) ans += (d - 2) * 5;          // distance part
        ans += (t / 2) * 5;                     // time part
        for (int h = static_cast<int>(s); h < static_cast<int>(e); ++h)
            ans += night[h];                    // night surcharge
        cout << ans << '\n';
    }
    return 0;
}
