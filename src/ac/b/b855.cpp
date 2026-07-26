#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using u64   = unsigned long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            vector<int> a(N);
            int64 total = 0;
            for (int i = 0; i < N; ++i) {
                cin >> a[i];
                total += a[i];
            }

            int64 target = total / 2;                     // we need sums ≤ target
            size_t words = (target + 64) / 64;            // number of 64‑bit words
            vector<u64> bits(words, 0);
            bits[0] = 1ULL;                               // sum 0 is reachable

            for (int v : a) {
                int shift = v;
                int wshift = shift >> 6;                  // whole‑word shift
                int offset = shift & 63;                  // intra‑word shift
                if (wshift >= (int)words) continue;      // shift exceeds target, ignore

                vector<u64> shifted(words, 0);
                if (offset == 0) {
                    for (size_t i = words - 1; i >= (size_t)wshift; --i) {
                        shifted[i] = bits[i - wshift];
                        if (i == (size_t)wshift) break;
                    }
                } else {
                    for (size_t i = words - 1; i >= (size_t)wshift; --i) {
                        u64 low = bits[i - wshift] << offset;
                        u64 high = 0;
                        if (i - wshift > 0)
                            high = bits[i - wshift - 1] >> (64 - offset);
                        shifted[i] = low | high;
                        if (i == (size_t)wshift) break;
                    }
                }

                for (size_t i = 0; i < words; ++i) bits[i] |= shifted[i];
                // mask bits beyond target in the most significant word
                int excess = (int)(words * 64 - (target + 1));
                if (excess > 0) {
                    bits.back() &= (~0ULL >> excess);
                }
            }

            // find the largest reachable sum ≤ target
            int64 best = 0;
            bool found = false;
            for (int64 s = target; s >= 0; --s) {
                size_t idx = s >> 6;
                int pos = s & 63;
                if (bits[idx] & (1ULL << pos)) {
                    best = s;
                    found = true;
                    break;
                }
            }
            if (!found) best = 0; // should never happen

            int64 other = total - best;
            int64 answer = best * best + other * other;
            cout << answer << '\n';
        }
    }
    return 0;
}
