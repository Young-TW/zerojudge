#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K, T;
    while (cin >> N >> K >> T) {
        vector<long long> m(N + 1);
        for (int i = 1; i <= N; ++i) {
            cin >> m[i];
        }

        // Prefix sum for range sum queries
        // P[i] = m[1] + ... + m[i]
        vector<long long> P(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            P[i] = P[i - 1] + m[i];
        }

        // dp[i] = maximum score considering up to time i, with no active freeze at time i.
        // Transitions:
        // 1. Do nothing at i: dp[i] = dp[i-1]
        // 2. End a freeze at i: The freeze covers [j, i].
        //    Conditions:
        //      - Length L = i - j + 1 <= T  => j >= i - T + 1
        //      - If this is the first freeze, no gap constraint.
        //      - If not first, previous freeze ended at 'prev_end'. Gap: (j - 1) - prev_end >= K.
        //        So prev_end <= j - 1 - K.
        //    Score = dp[prev_end] + (P[i] - P[j-1]).
        //    We want max(dp[prev_end]) where prev_end <= j - 1 - K.
        //    Let best[x] = max(dp[0], ..., dp[x]).
        //    Then max term is best[j - 1 - K] (if j - 1 - K >= 0).
        //    So candidate = best[j - 1 - K] + P[i] - P[j-1].
        //    We need max over valid j of (best[j - 1 - K] - P[j-1]).
        //    Let idx = j - 1. idx ranges from [i-T, i-1].
        //    We need max over idx in [i-T, i-1] of (best[idx - K] - P[idx]) + P[i].
        //    Note: best[x] is defined as 0 for x < 0 effectively if we handle boundaries, 
        //    but logically dp[0]=0, and best[-1] should be treated carefully.
        //    Actually, if j=1 (start at 1), then prev_end must be <= -K (impossible), so it's first freeze.
        //    For first freeze, we just take P[i] - P[j-1]. This corresponds to dp[0] (which is 0) being the base.
        //    So we can define best[x] = max(dp[0]...dp[x]) for x>=0, and conceptually best[x]=0 for x<0?
        //    Wait, if it's the first freeze, we don't need a gap. The "previous end" is effectively 0 (start state) but without gap check?
        //    Let's refine:
        //    Option A: First freeze ending at i, starting at j. Value = P[i] - P[j-1].
        //    Option B: Subsequent freeze ending at i, starting at j. Value = max_{e <= j-1-K} dp[e] + P[i] - P[j-1].
        //    Combined: Value = P[i] + max( -P[j-1] (if first), max_{e <= j-1-K} dp[e] - P[j-1] ).
        //    Since dp[0]=0 and e=0 is allowed if 0 <= j-1-K (i.e., j >= K+1), the "first freeze" case is actually covered by the general formula IF we consider the state before any freeze as dp[0]=0 and allow transition from 0 without gap?
        //    NO. The rule says "Except for the FIRST freeze, must have gap".
        //    So if we transition from dp[0] (meaning no freezes so far), we don't need gap.
        //    If we transition from dp[e] where e > 0 (meaning at least one freeze happened), we need gap.
        //    However, our dp definition: dp[i] is max score up to i with no active freeze. It doesn't distinguish "has freeze" vs "no freeze yet".
        //    But notice: if we haven't done any freeze, the score is 0. dp[0]=0.
        //    If we do a first freeze [j, i], score is sum(j..i).
        //    If we do a subsequent freeze [j, i] after one ending at e, score is dp[e] + sum(j..i).
        //    Since dp[e] >= 0, and we want max, we can unify:
        //    We need max( (e==-1 ? 0 : dp[e]) ) where e <= j-1-K OR (e==-1 representing "no prior freeze").
        //    Actually, simpler:
        //    Let M[x] = max(dp[0], dp[1], ..., dp[x]).
        //    For a start index j (1-based), the previous freeze could have ended at any e <= j-1-K.
        //    The best value from previous states is M[j-1-K] (if j-1-K >= 0).
        //    What if j-1-K < 0? That means we cannot have a prior freeze ending >= 0 satisfying the gap.
        //    In that case, this MUST be the first freeze. The value added is just sum(j..i).
        //    Is it possible that M[j-1-K] (which includes dp[0]=0) covers the "first freeze" case?
        //    If j-1-K >= 0, then e=0 is a candidate. dp[0]=0. So M[...] >= 0.
        //    The term becomes M[...] - P[j-1] + P[i]. Since M[...] >= 0, this is >= P[i] - P[j-1].
        //    So if j-1-K >= 0, the formula M[j-1-K] - P[j-1] + P[i] works for both first (if optimal to treat as such? No, if j-1-K>=0, we CAN have a prior freeze ending at 0? But 0 is start. Gap from 0 to j-1 is j-1. Need j-1 >= K. Yes.)
        //    Wait, if it's the VERY first freeze, there is no previous end. The constraint "gap >= K" applies only if there was a previous freeze.
        //    If we treat "state 0" as "last freeze ended at 0", then we enforce gap K. But the first freeze shouldn't have gap constraint relative to start.
        //    Correction: The rule says "Except for the first freeze, must gap K from last END".
        //    So if we pick a range [j, i] as the FIRST freeze, valid for any j>=1. Score = P[i]-P[j-1].
        //    If we pick [j, i] as NOT first, previous end e must satisfy e <= j-1-K. Score = dp[e] + P[i] - P[j-1].
        //    So for a fixed j, the best previous contribution is:
        //      val = max( 0 (case first), max_{0 <= e <= j-1-K} dp[e] )
        //    Note: dp[0]=0. If j-1-K >= 0, then max_{...} includes dp[0]=0. So max(0, M[j-1-K]) = M[j-1-K].
        //    If j-1-K < 0, then the set {e} is empty. So max is just 0 (the "first freeze" case).
        //    So we can define a function get_best(idx): returns M[idx] if idx>=0, else 0.
        //    Then candidate = get_best(j-1-K) - P[j-1] + P[i].
        //    We need to maximize this over j in [i-T+1, i].
        //    Let idx = j-1. idx in [i-T, i-1].
        //    Term: get_best(idx-K) - P[idx].
        //    We need max of this term for idx in [i-T, i-1].
        //    Let V[idx] = get_best(idx-K) - P[idx].
        //    We need sliding window maximum of V[idx] for window [i-T, i-1].
        //    Window size is T. As i increases, the window slides right.
        //    We can use a deque to maintain the max of V[idx].

        vector<long long> dp(N + 1, 0);
        vector<long long> M(N + 1, 0); // M[i] = max(dp[0]...dp[i])
        
        // Deque stores indices 'idx' corresponding to V[idx]
        deque<int> dq;
        
        // Helper to get V[idx]
        auto get_V = [&](int idx) -> long long {
            long long best_prev = (idx - K >= 0) ? M[idx - K] : 0;
            return best_prev - P[idx];
        };

        // Initialize for i=1 to N
        // We need to populate dq with candidates for j (which maps to idx=j-1).
        // For a specific i, valid idx are [i-T, i-1].
        // Before processing i, we should add idx = i-1 into the deque?
        // Let's iterate i from 1 to N.
        // At step i, the new candidate index entering the window is idx_new = i-1.
        // The candidate leaving is idx_old = i-T-1.
        
        // Pre-calculate M[0] = dp[0] = 0.
        M[0] = 0;

        for (int i = 1; i <= N; ++i) {
            // New index available to be a start-1 (idx = j-1) is i-1.
            int idx_new = i - 1;
            
            // Calculate V[idx_new]
            // Note: M might not be fully updated for indices > i-1, but we only need M up to idx_new-K.
            // Since idx_new = i-1, we need M[i-1-K]. Since K>=1, i-1-K < i. So M is ready.
            long long val_new = get_V(idx_new);
            
            // Maintain deque decreasing order
            while (!dq.empty()) {
                int back_idx = dq.back();
                // We need to compare V[back_idx] and val_new.
                // But V depends on M which is static for past indices.
                // However, get_V uses M. M is computed up to i-1 already.
                // Wait, M[idx-K] is fixed once idx-K is processed.
                // So we can compute V[idx] once and store it? Or recompute. Recompute is fine O(1).
                if (get_V(back_idx) <= val_new) {
                    dq.pop_back();
                } else {
                    break;
                }
            }
            dq.push_back(idx_new);
            
            // Remove indices out of window [i-T, i-1]
            // Valid idx >= i-T. So remove if < i-T.
            int min_idx = i - T;
            while (!dq.empty() && dq.front() < min_idx) {
                dq.pop_front();
            }
            
            // Best candidate
            int best_idx = dq.front();
            long long best_val = get_V(best_idx);
            
            long long candidate = best_val + P[i];
            
            // Transition 1: Don't end a freeze at i (carry over)
            dp[i] = dp[i-1];
            
            // Transition 2: End a freeze at i
            if (candidate > dp[i]) {
                dp[i] = candidate;
            }
            
            // Update M
            M[i] = max(M[i-1], dp[i]);
        }

        cout << dp[N] << "\n";
    }

    return 0;
}
