#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

const int MOD = 998244353;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

long long fact[200005];
long long invFact[200005];

void precomputeFactorials(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i-1] * i) % MOD;
    }
    invFact[n] = modInverse(fact[n]);
    for (int i = n-1; i >= 0; i--) {
        invFact[i] = (invFact[i+1] * (i+1)) % MOD;
    }
}

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precomputeFactorials(200000);

    int N, M;
    while (cin >> N >> M) {
        string A, B;
        cin >> A >> B;

        vector<int> countA(26, 0);
        vector<int> countB(26, 0);

        for (char c : A) {
            countA[c - 'A']++;
        }
        for (char c : B) {
            countB[c - 'A']++;
        }

        // dp[i][j] = number of ways to match first i characters of sorted A 
        // using a subset of first j characters of sorted B
        // But this is too slow O(N*M). We need a better approach.
        
        // Let's reframe: We sort A and B.
        // We need to choose N characters from B (keeping their relative order in sorted B doesn't matter since we can permute B')
        // Actually, A' is a permutation of A, B' is a subsequence of length N from some permutation of B.
        // This means we just need to pair each character in A with a unique character in B such that
        // b_char == a_char or b_char == a_char + 1.
        // And then multiply by the number of ways to arrange them?
        // No, the problem says:
        // A' is chosen from any permutation of A.
        // B' is chosen by removing M-N characters from any permutation of B.
        // So effectively, we are forming two strings A' and B' of length N.
        // A' is a permutation of A.
        // B' is a subsequence of some permutation of B, which means B' is just any multiset of size N drawn from B.
        // Wait, "from B's any permutation remove M-N characters". This results in a string B'.
        // The condition is B'[i] == A'[i] or B'[i] == A'[i]+1.
        // Since we can permute A arbitrarily to form A', and we can choose any N characters from B and arrange them arbitrarily to form B' (because we can permute B first then pick the first N),
        // the problem reduces to:
        // Can we form pairs (a_1, b_1), (a_2, b_2), ..., (a_N, b_N) where {a_i} is the multiset A, {b_i} is a sub-multiset of B of size N,
        // such that for each pair, b_i == a_i or b_i == a_i + 1?
        // And then how many distinct pairs (A', B')?
        // A' is a specific string. B' is a specific string.
        // If we fix the multiset of pairs, say we have k_1 pairs of ('A', 'A'), k_2 pairs of ('A', 'B'), etc.
        // Then A' is formed by the first elements, B' by the second.
        // The number of distinct strings A' given the multiset of first elements is N! / (prod count_a_char!).
        // But wait, the pairing matters.
        // Actually, let's look at the constraints and the nature of the operation.
        // We can reorder A freely. We can reorder B freely and then pick N.
        // This implies we can form ANY pairing between the multiset A and a sub-multiset of B of size N,
        // as long as the condition holds for each pair.
        // Once we have a set of N pairs (a_i, b_i), we can arrange them in any order to form (A', B').
        // Specifically, if we have a collection of N pairs, the number of distinct strings (A', B') we can form
        // depends on the multiplicities of the pairs.
        // Suppose we have counts for each type of pair (c, d) where d==c or d==c+1.
        // Let x_{c,d} be the number of times we pair character c with character d.
        // Constraints:
        // Sum_d x_{c,d} = countA[c] for all c.
        // Sum_c x_{c,d} <= countB[d] for all d.
        // Sum_{c,d} x_{c,d} = N.
        // Valid pairs (c, d): ('A','A'), ('A','B'), ('B','B'), ('B','C'), ... ('Z','Z'). Note 'Z' can only pair with 'Z'.
        // For a fixed valid assignment of x_{c,d}, how many (A', B') pairs?
        // We have N positions. We need to assign the pairs to these positions.
        // The number of ways to arrange the pairs is N! / (prod_{c,d} x_{c,d}!).
        // However, different assignments of x_{c,d} might lead to the same (A', B')?
        // No, because the multiset of pairs determines the possible strings.
        // Actually, if we have a specific multiset of pairs, say {('A','A'), ('A','B')},
        // then A' must be a permutation of "AA", B' must be a permutation of "AB".
        // The condition is element-wise.
        // If we arrange the pairs as p_1, p_2, ..., p_N, then A' = p_1.first ... p_N.first, B' = p_1.second ... p_N.second.
        // Any permutation of the list of pairs gives a valid (A', B') satisfying the condition.
        // Are all these (A', B') distinct?
        // If the list of pairs has duplicates, swapping identical pairs gives the same (A', B').
        // So for a fixed matrix x_{c,d}, the number of distinct (A', B') is N! / (prod x_{c,d}!).
        // We need to sum this quantity over all valid matrices x_{c,d}.
        
        // The structure of valid pairs is a chain:
        // 'A' can go to 'A' or 'B'
        // 'B' can go to 'B' or 'C'
        // ...
        // This looks like a DP.
        // Let's process characters from 'A' to 'Z'.
        // State: dp[char][k] = sum of (ways to arrange partial pairs) where k is the number of 'char' characters from B used to satisfy 'char'-1 from A?
        // No, let's refine.
        // When processing character c (from 'A' to 'Z'):
        // We have countA[c] items of type c in A.
        // They can be matched with c or c+1 in B.
        // Also, items of type c-1 in A could have been matched with c in B.
        // Let's define the flow.
        // Let x_c be the number of times c in A is matched with c in B.
        // Let y_c be the number of times c in A is matched with c+1 in B.
        // Then x_c + y_c = countA[c].
        // The demand on B[c] comes from:
        // 1. A[c] matched with B[c] (x_c)
        // 2. A[c-1] matched with B[c] (y_{c-1})
        // So we need x_c + y_{c-1} <= countB[c]. (With y_{-1} = 0).
        // We need to sum over all valid sequences y_0, y_1, ..., y_{25} (where y_c is the amount of A[c] shifted to B[c+1]).
        // Note y_{25} must be 0 because there is no '['.
        // For a fixed sequence y_c, we have x_c = countA[c] - y_c.
        // The number of pairs of type (c, c) is x_c.
        // The number of pairs of type (c, c+1) is y_c.
        // The total multiplicity factor is N! / (prod_c (x_c! * y_c!)).
        // We need to compute Sum_{valid y} [ N! / (prod_c ( (countA[c]-y_c)! * y_c! )) ].
        // Factor out N!: N! * Sum_{valid y} [ prod_c ( 1 / ((countA[c]-y_c)! * y_c!) ) ].
        // The constraint is: (countA[c] - y_c) + y_{c-1} <= countB[c]  =>  y_c >= countA[c] + y_{c-1} - countB[c].
        // Also 0 <= y_c <= countA[c].
        // And y_{-1} = 0, y_{25} = 0.
        
        // Let's use DP.
        // dp[c][k] = sum of products of terms for characters 0..c-1, where k = y_{c-1} (the number of A[c-1] shifted to B[c]).
        // Transition for character c:
        // We iterate over possible values of y_c (let's call it j).
        // Constraints on j:
        // 1. 0 <= j <= countA[c]
        // 2. j >= countA[c] + k - countB[c]  (from the B[c] capacity constraint)
        // Term for c: 1 / ((countA[c]-j)! * j!)
        // dp[c+1][j] += dp[c][k] * term
        // The state space: c from 0 to 26. k from 0 to N.
        // Complexity: 26 * N * N? Too slow if N=200,000.
        // But note k (which is y_{c-1}) cannot exceed countA[c-1]. And also limited by countB[c].
        // Actually, y_c is bounded by countA[c]. The sum of countA is N.
        // Is it possible that k is large? Yes, up to N.
        // However, observe the constraints on y_c.
        // y_c >= countA[c] + y_{c-1} - countB[c].
        // Also y_c <= countA[c].
        // This looks like a convolution or just a simple loop if the range of valid k is small?
        // No, the range of k can be large.
        // But wait, we only have 26 characters.
        // Maybe the number of valid states k at each step is not too large?
        // Or maybe we can optimize the transition.
        // dp[c+1][j] = (1/((countA[c]-j)! j!)) * Sum_{k} dp[c][k] where k satisfies the condition.
        // Condition: k <= countB[c] - countA[c] + j.
        // Let R_c(j) = countB[c] - countA[c] + j.
        // We need sum of dp[c][k] for k such that:
        // 1. k is a valid previous state (0 <= k <= countA[c-1])
        // 2. k <= R_c(j)
        // 3. Also from previous step, k must have satisfied its own lower bound? No, dp[c][k] is already 0 if invalid.
        // So for a fixed j, we need prefix sum of dp[c][k] up to min(countA[c-1], R_c(j)).
        // Since j goes from 0 to countA[c], and we need prefix sums, we can precompute prefix sums of dp[c].
        // Then the transition is O(countA[c]).
        // Total complexity: Sum over c of countA[c] = N.
        // This is O(N * 26) = O(N). Perfect.

        vector<long long> dp(N+1, 0);
        // Base case: before processing 'A' (c=0), we have y_{-1} = 0.
        // So dp[0] = 1 (representing the empty product so far, and k=0).
        // But our dp index represents k = y_{c-1}.
        // Initially for c=0, k=y_{-1}=0.
        dp[0] = 1;
        int max_k = 0; // Current maximum possible k (y_{c-1})

        for (int c = 0; c < 26; c++) {
            vector<long long> next_dp(N+1, 0);
            int current_A = countA[c];
            int current_B = countB[c];
            
            // Precompute prefix sums of dp
            // We only care about k from 0 to max_k
            vector<long long> prefix(max_k + 2, 0);
            for (int k = 0; k <= max_k; k++) {
                prefix[k+1] = (prefix[k] + dp[k]) % MOD;
            }

            int next_max_k = 0;

            // Iterate over j = y_c
            // Constraints:
            // 0 <= j <= current_A
            // k <= current_B - current_A + j  => k <= j + (current_B - current_A)
            // We need sum of dp[k] for 0 <= k <= min(max_k, j + current_B - current_A)
            
            int diff = current_B - current_A;
            
            for (int j = 0; j <= current_A; j++) {
                int limit_k = j + diff;
                if (limit_k < 0) continue; // No valid k
                
                int idx = min(limit_k, max_k);
                if (idx < 0) {
                    // sum is 0
                    continue;
                }
                
                long long sum_val = prefix[idx+1];
                if (sum_val == 0) continue;

                long long ways = invFact[current_A - j] * invFact[j] % MOD;
                long long total = sum_val * ways % MOD;
                
                next_dp[j] = (next_dp[j] + total) % MOD;
                if (total > 0) {
                    next_max_k = max(next_max_k, j);
                }
            }
            
            dp = next_dp;
            max_k = next_max_k;
            if (max_k == 0 && dp[0] == 0) break; // Early exit if no valid states
        }

        // After processing c=25 ('Z'), we need y_{25} = 0.
        // Our dp state after the loop for c=25 corresponds to k = y_{25}.
        // So the answer is dp[0] * N!.
        long long ans = dp[0] * fact[N] % MOD;
        cout << ans << "\n";
    }

    return 0;
}
