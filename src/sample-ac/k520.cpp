#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

ull N;

ull compute(ull B, int k) {
    // compute 1 + B + B^2 + ... + B^(k-1), capped at N+1
    ull result = 1;
    ull power = 1;
    for (int i = 1; i < k; i++) {
        if (power > ULLONG_MAX / B) return N + 1;
        power *= B;
        if (result > ULLONG_MAX - power) return N + 1;
        result += power;
        if (result > N) return N + 1;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> N) {
        if (N == 1) {
            cout << 2 << endl;
            continue;
        }
        ull ans = N - 1; // k = 2, B = N - 1
        for (int k = 3; k <= 62; k++) {
            if (compute(2, k) > N) break;
            ull lo = 2, hi = 2;
            while (compute(hi, k) < N) {
                hi *= 2;
            }
            while (lo < hi) {
                ull mid = (lo + hi) / 2;
                if (compute(mid, k) < N) {
                    lo = mid + 1;
                } else {
                    hi = mid;
                }
            }
            if (compute(lo, k) == N) {
                ans = min(ans, lo);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
