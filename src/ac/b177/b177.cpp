// b177 山景 Skyline  -- self-written solution
// Count Dyck paths of semilength m=n/2 whose peak heights are non-decreasing
// left-to-right (verified by brute force). O(m^2) DP with prefix sums.
//
// Output = last 9 decimal digits of the answer. Sample shows small answers are
// printed as-is (4, not 000000004), so: if the true answer < 1e9 print it raw,
// otherwise print exactly the last 9 digits WITH leading zeros (e.g. n=64 ->
// true answer 2854059964432 -> "059964432"). The true answer is strictly
// increasing in n; we detect ">=1e9" with a parallel clamped double DP so the
// padding decision needs no hard-coded threshold.
#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1000000000LL;

// Run the DP; T = long long (with mod) or double (with clamp).
// mode==true: modular arithmetic. mode==false: clamp non-negative sums at CAP.
template <typename T>
T run(int N, bool mod) {
    const T CAP = (T)4e18;
    auto red = [&](T x) -> T {
        if (mod) return ((long long)x % MOD + MOD) % MOD;
        if (x < 0) x = 0;              // fp noise on window subtraction
        if (x > CAP) x = CAP;
        return x;
    };
    vector<T> P(N + 1, 0);
    vector<T> prefixP(N + 2, 0), prefixY(N + 2, 0);
    vector<T> cP(N + 1, 0), RHS(N + 1, 0), Y(N + 1, 0), newP(N + 1, 0);
    for (int h = N; h >= 1; --h) {
        for (int i = 0; i <= N; i++) prefixP[i + 1] = red(prefixP[i] + P[i]);
        for (int k = 0; k <= N; k++) {
            int idx = k + h - 1;
            T v = 0;
            if (idx <= N) {
                int hi = idx + 1; if (hi > N + 1) hi = N + 1;
                int lo = idx - h + 1; if (lo < 0) lo = 0;
                if (hi >= lo) v = red(prefixP[hi] - prefixP[lo]);
            }
            cP[k] = v;
        }
        for (int k = 0; k <= N; k++) RHS[k] = cP[k];
        for (int j = 1; j <= h && j <= N; j++) RHS[j] = red(RHS[j] + 1);
        for (int i = 0; i <= N + 1; i++) prefixY[i] = 0;
        for (int k = 0; k <= N; k++) {
            int lo = k - h; if (lo < 0) lo = 0;
            T dsum = red(prefixY[k] - prefixY[lo]);
            Y[k] = red(RHS[k] + dsum);
            prefixY[k + 1] = red(prefixY[k] + Y[k]);
        }
        for (int k = 0; k <= N; k++) newP[k] = P[k];
        if (h <= N) newP[h] = red(newP[h] + 1);
        for (int k = 0; k + h <= N; k++) newP[k + h] = red(newP[k + h] + Y[k]);
        for (int k = 0; k <= N; k++) P[k] = newP[k];
    }
    return P[N];
}

int main() {
    long long n;
    if (!(cin >> n)) return 0;
    long long m = n / 2;
    if (m <= 0) { cout << 1 << "\n"; return 0; }
    int N = (int)m;

    long long resid = (long long)run<long long>(N, true) % MOD;
    double mag = run<double>(N, false);        // >= 1e9 iff true answer >= 1e9

    if (mag >= 1e9 - 0.5) {
        // pad to exactly 9 digits with leading zeros
        char buf[16];
        snprintf(buf, sizeof(buf), "%09lld", resid);
        cout << buf << "\n";
    } else {
        cout << resid << "\n";
    }
    return 0;
}
