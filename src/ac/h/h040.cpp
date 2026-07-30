#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        vector<long double> factor(N);
        for (int i = 0; i < N; ++i) {
            unsigned long long F;
            cin >> F;
            long double lg = log2((long double)F + 1.0L);
            if (lg > 30.0L) lg = 30.0L;
            factor[i] = lg;                     // L_i
        }

        int Q;
        cin >> Q;
        while (Q--) {
            long long K;
            cin >> K;

            long long lo = 1, hi = K, ans = K;
            while (lo <= hi) {
                long long mid = lo + (hi - lo) / 2;   // candidate V0

                // ----- compute total(mid) -----
                long long cur = mid;
                unsigned long long sum = cur;         // use unsigned to avoid overflow
                if (sum < (unsigned long long)K) {
                    for (int i = 0; i < N; ++i) {
                        long double prod = (long double)cur * factor[i] / 30.0L;
                        long long nxt = (long long)prod;   // floor, prod >= 0
                        cur = nxt;
                        sum += cur;
                        if (cur == 0) break;
                        if (sum >= (unsigned long long)K) break;
                    }
                }
                // ----- end compute -----

                if (sum >= (unsigned long long)K) {
                    ans = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
