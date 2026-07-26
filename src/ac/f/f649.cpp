#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned long long N, M;
    const long double EPS = 1e-12L;

    while (cin >> N >> M) {
        // cases where the result is known to be 1
        if (M == 0) {               // N^0 = 1 (including 0^0)
            cout << 1 << '\n';
            continue;
        }
        if (N == 0) {               // 0^M = 0   (M>0 here)
            cout << 1 << '\n';
            continue;
        }

        // normal case N>0 , M>0
        long double lg = log10(static_cast<long double>(N));
        long double val = static_cast<long double>(M) * lg;

        unsigned __int128 D = static_cast<unsigned __int128>(floor(val + EPS)) + 1;

        // count decimal digits of D
        int ans = 0;
        do {
            ++ans;
            D /= 10;
        } while (D != 0);

        cout << ans << '\n';
    }
    return 0;
}
