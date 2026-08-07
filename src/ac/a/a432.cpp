#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using lll   = __int128;

static const int64 OUT_LIM = 1000000000000000000LL;   // 10^18, output threshold
// Powers up to CAP (10^36) are stored EXACTLY (they fit in __int128).  Powers
// that would exceed CAP cannot take part in a finite (<=10^18) answer, but they
// must still be *ordered correctly* inside the decision-monotonicity deque:
// collapsing them all to one constant creates ties (CAP<=CAP) that let the
// back-pop wrongly evict a still-needed finite decision.  So an over-cap power
// is mapped to  CAP + d*BIG  -- strictly increasing in |diff| = d, which matches
// the true ordering of |diff|^P, and with BIG > OUT_LIM so |diff| dominates the
// dp[] tie-break just as the true (huge) power dominates it.
static const lll   CAP = (lll)1000000000000000000LL * (lll)1000000000000000000LL; // 10^36
static const lll   BIG = (lll)2000000000000000000LL;                              // 2*10^18 > OUT_LIM

int P;                                            // exponent (1..10)

/* d^P.  Exact when <= CAP; otherwise a monotone-in-d surrogate above CAP.
   乘之前先判會不會超 CAP,避免 __int128 先溢位(d 可達 ~3.2e6、P=10 → d^P 可達 1e65)。 */
static inline lll pow_cap(unsigned long long d) {
    if (d == 0) return 0;                 // 0^P = 0 (P>=1)
    lll cur = 1, D = (lll)d;
    for (int i = 0; i < P; ++i) {
        if (cur > CAP / D) return CAP + D * BIG;   // over cap -> monotone surrogate (no tie)
        cur *= D;
    }
    return cur;                            // exact, <= CAP
}

static int N;
static vector<int64> S;   // prefix of (len+1)
static vector<lll>   dp;  // dp[i]
static int64 C;           // L + 1

/* cost of using decision j for position i: dp[j] + |S[i]-S[j]-C|^P.
   No re-capping of the sum: that would re-introduce the flattening tie.  The sum
   stays < 1.7e38, so it never overflows __int128. */
static inline lll cost(int j, int i) {
    if (dp[j] >= CAP) return CAP + (lll)3200001 * BIG;   // safety: unreachable in practice
    int64 diffSigned = S[i] - S[j] - C;
    unsigned long long d = diffSigned >= 0 ? (unsigned long long)diffSigned
                                           : (unsigned long long)(-diffSigned);
    return dp[j] + pow_cap(d);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int64 L;
        cin >> N >> L >> P;
        S.assign(N + 1, 0);
        string s;
        for (int i = 1; i <= N; ++i) {
            cin >> s;
            S[i] = S[i - 1] + (int64)s.size() + 1;
        }
        C = L + 1;
        dp.assign(N + 1, CAP);
        dp[0] = 0;

        // decision-monotonicity monotonic deque:
        // each item = {decision j, pos = first index i for which j is the best decision}
        struct Item { int j, pos; };
        deque<Item> dq;
        dq.push_back({0, 1});

        for (int i = 1; i <= N; ++i) {
            while (dq.size() >= 2 && dq[1].pos <= i) dq.pop_front();
            dp[i] = cost(dq.front().j, i);

            if (dp[i] > (lll)OUT_LIM) continue;   // can never lead to a finite answer

            int j = i;
            while (!dq.empty() &&
                   cost(j, dq.back().pos) <= cost(dq.back().j, dq.back().pos))
                dq.pop_back();

            if (dq.empty()) {
                dq.push_back({j, i + 1});
            } else {
                // first pos in [i+1, N] where j becomes at least as good as back.j
                int lo = i + 1, hi = N, found = -1;
                while (lo <= hi) {
                    int mid = lo + (hi - lo) / 2;
                    if (cost(j, mid) <= cost(dq.back().j, mid)) { found = mid; hi = mid - 1; }
                    else lo = mid + 1;
                }
                if (found != -1) dq.push_back({j, found});
            }
        }

        if (dp[N] > (lll)OUT_LIM) cout << "Too hard to arrange\n";
        else cout << (int64)dp[N] << "\n";
        cout << "--------------------\n";
    }
    return 0;
}
