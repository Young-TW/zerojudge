#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n_ll, p_ll;
    while (cin >> n_ll >> p_ll) {
        long long n = n_ll;
        long long p = p_ll;

        long long x_ll;
        cin >> x_ll;
        __int128 cur = x_ll;          // max sub‑array sum ending at current position
        __int128 best = x_ll;         // max sub‑array sum inside current prefix
        __int128 f = best;            // characteristic value of child 1
        __int128 s = f;               // score of child 1
        __int128 ans = s;             // current maximum score
        __int128 mx = s + f;          // max_{j ≤ 1} (s[j] + f[j])

        for (long long i = 2; i <= n; ++i) {
            cin >> x_ll;
            __int128 x = x_ll;

            // Kadane step
            cur = (cur + x > x) ? (cur + x) : x;
            best = (best > cur) ? best : cur;
            f = best;                 // characteristic value of child i

            s = mx;                   // score of child i
            if (s > ans) ans = s;     // update global maximum

            __int128 candidate = s + f;
            if (candidate > mx) mx = candidate;   // prepare for next child
        }

        __int128 rem = ans % (__int128)p;   // sign is kept automatically
        long long out = (long long)rem;
        cout << out << '\n';
    }
    return 0;
}
