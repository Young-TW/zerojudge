#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128  = __int128_t;

/* count ordered pairs (x,y) with
   x in [A,B] , y in [C,D] (all positive) and x*y >= K (K>0) */
static i128 count_ge(int64 A, int64 B, int64 C, int64 D, int64 K)
{
    if (A > B || C > D) return 0;
    i128 ans = 0;
    int64 x = A;
    while (x <= B) {
        // minimal y for current x
        int64 y_needed = (K + x - 1) / x;          // ceil(K/x)

        if (y_needed > D) {                       // impossible for this x
            // smallest x with ceil(K/x) <= D
            int64 nxt = (K + D - 1) / D;           // ceil(K/D)
            if (nxt <= x) nxt = x + 1;
            x = nxt;
            continue;
        }

        int64 y_low = y_needed < C ? C : y_needed;
        if (y_low > D) {                          // still impossible
            int64 nxt = (K + D - 1) / D;
            if (nxt <= x) nxt = x + 1;
            x = nxt;
            continue;
        }

        // all x with the same y_needed = v
        int64 v = y_needed;
        int64 x_max;
        if (v == 1) {
            x_max = B;                             // ceil(K/x)=1 for all larger x
        } else {
            x_max = (K - 1) / (v - 1);             // maximal x with this v
            if (x_max > B) x_max = B;
        }
        if (x_max < x) x_max = x;                  // safety

        int64 cntX = x_max - x + 1;
        int64 cntY = D - y_low + 1;
        ans += (i128)cntX * (i128)cntY;

        x = x_max + 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int m;
        int64 l, r;
        cin >> m >> l >> r;
        int64 LIM = 1LL << (m - 1);               // 2^{m-1}

        // positive part
        int64 lp = max<int64>(l, 1);
        int64 rp = r;
        bool hasPos = (lp <= rp);

        // negative part
        int64 ln = l;
        int64 rn = min<int64>(r, -1);
        bool hasNeg = (ln <= rn);

        // absolute values of negatives (positive interval)
        int64 anL = -rn;   // smallest absolute value
        int64 anR = -ln;   // largest absolute value

        i128 overflow = 0;

        if (hasPos) {
            overflow += count_ge(lp, rp, lp, rp, LIM);          // PP
        }
        if (hasNeg) {
            overflow += count_ge(anL, anR, anL, anR, LIM);      // NN
        }
        if (hasPos && hasNeg) {
            i128 mixed = count_ge(lp, rp, anL, anR, LIM + 1);   // PN (strict)
            overflow += mixed * 2;                             // PN + NP
        }

        uint64_t answer = (uint64_t)overflow;   // fits into 64‑bit unsigned
        cout << answer << '\n';
    }
    return 0;
}
