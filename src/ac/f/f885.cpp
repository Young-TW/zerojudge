#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128  = __int128_t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int64 a, x;
        cin >> a >> x;

        int64 low = a;
        int64 high = x;               // answer never exceeds x

        auto sum_ge = [&](int64 n) -> bool {
            i128 cnt = (i128)(n - a + 1);   // number of terms
            i128 s   = (i128)(a + n);       // first + last
            i128 total = cnt * s / 2;       // arithmetic series sum
            return total >= (i128)x;
        };

        while (low < high) {
            int64 mid = low + (high - low) / 2;
            if (sum_ge(mid))
                high = mid;
            else
                low = mid + 1;
        }
        cout << low << '\n';
    }
    return 0;
}
