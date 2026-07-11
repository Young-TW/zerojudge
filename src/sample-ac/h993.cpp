#include <iostream>
#include <string>
#include <vector>

using namespace std;

const long long MOD = 998244353;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int X;
    if (!(cin >> X)) return 0;
    
    string N_str;
    cin >> N_str;

    int len = N_str.length();
    
    // Precompute powers of 10 modulo MOD
    // pow10[i] = 10^i % MOD
    vector<long long> pow10(len + 1);
    pow10[0] = 1;
    for (int i = 1; i <= len; ++i) {
        pow10[i] = (pow10[i-1] * 10) % MOD;
    }

    long long total_sum = 0;

    // Iterate over possible prefix lengths k (from 1 to len)
    // We want to count how many numbers i in [1, N] have a prefix of 1s of length >= k.
    // If G(i) >= k, it means the first k digits of i are all '1'.
    // The contribution of such a number to the sum is 1 for this specific k.
    // Summing over all k gives sum G(i).
    
    for (int k = 1; k <= len; ++k) {
        // We are looking for numbers with at least k leading ones.
        // Case 1: Numbers with fewer than k digits.
        // A number with d < k digits cannot have k leading ones. Contribution 0.
        
        // Case 2: Numbers with exactly d digits, where k <= d < len.
        // The number must start with k '1's. The remaining d-k digits can be anything (0-9).
        // Count = 10^(d-k).
        // However, we must ensure the number doesn't start with 0, but since it starts with '1', it's valid.
        // So for each length d from k to len-1:
        // count += 10^(d-k)
        
        long long count = 0;
        
        // Sum for lengths d = k to len - 1
        // Sum_{j=0}^{len-1-k} 10^j
        if (len - 1 >= k) {
            int max_pow = len - 1 - k;
            // Geometric series sum: (10^(max_pow+1) - 1) / 9
            // But we need modular inverse of 9? Or just iterate since len is up to 5*10^5?
            // Iterating inside the loop would make it O(N^2). We need O(1) or O(N) total.
            // Let's precompute prefix sums of powers of 10? 
            // Actually, sum_{j=0}^{M} 10^j = (10^{M+1} - 1) * inv(9).
            // Since MOD is prime and not 3, inv(9) exists.
            // But wait, we can just accumulate this differently.
            
            // Let's restructure.
            // Instead of iterating k then summing lengths, let's stick to the logic but optimize the sum.
            // Sum_{d=k}^{len-1} 10^(d-k) = 1 + 10 + ... + 10^(len-1-k)
            // This is a geometric series.
            // Let S(M) = sum_{j=0}^{M} 10^j.
            // We can precompute S(M) array.
        }
        
        // Let's precompute prefix sums of powers of 10 to handle the range sum quickly.
        // prefix_pow_sum[i] = sum_{j=0}^{i} 10^j % MOD
        // Then sum for d=k to len-1 is prefix_pow_sum[len-1-k].
        
        // Case 3: Numbers with exactly len digits (same length as N).
        // The number must start with k '1's.
        // Let the prefix of N of length k be P_k.
        // If P_k consists of all '1's:
        //   Then any number starting with k '1's and followed by any (len-k) digits 
        //   that forms a number <= the suffix of N is valid.
        //   Actually, if the first k digits of N are all '1', then the numbers starting with k '1's
        //   range from 11...100...0 to 11...1(suffix).
        //   Specifically, the prefix is fixed to "11...1" (k times).
        //   The remaining len-k digits can range from 0 to the integer value of N's suffix.
        //   Count = (suffix_value + 1).
        // If P_k is greater than "11...1" (lexicographically, which means numerically since same length):
        //   Since N starts with something larger than k ones (e.g., N=2..., k=1), 
        //   then ALL numbers starting with k ones (and any subsequent digits) are less than N.
        //   Because the smallest number with k+1 digits starting with 1 is 10...0 which is < N if N starts with >1?
        //   Wait, we are comparing numbers of length LEN.
        //   If N starts with digit > 1 at position 0, then any number of length LEN starting with 1 is smaller.
        //   If N starts with 1, we check next.
        //   Generally: Construct the number formed by k '1's followed by (len-k) '0's. Call it Base.
        //   Construct the number formed by k '1's followed by (len-k) '9's. Call it MaxVal.
        //   Actually simpler:
        //   Compare the first k digits of N with the string of k '1's.
        //   Let target = string(k, '1').
        //   Let prefixN = N_str.substr(0, k).
        //   If prefixN > target:
        //      All numbers of length len starting with k '1's are <= N.
        //      Count = 10^(len-k).
        //   If prefixN == target:
        //      The numbers starting with k '1's are valid up to the suffix of N.
        //      Count = (stoll(N_str.substr(k)) + 1). But N is huge, so we need mod arithmetic carefully?
        //      Wait, the count itself might be large, but we only need it modulo MOD?
        //      Yes, because we are summing counts.
        //      However, stoll won't work for 5*10^5 digits. We need to compute the value of the suffix modulo MOD.
        //      But wait, is it just modulo MOD?
        //      We are counting integers. The number of integers is (SuffixValue + 1).
        //      We need (SuffixValue + 1) % MOD.
        //      SuffixValue is the integer represented by N_str[k..end].
        //      We can compute this incrementally or using precomputed powers.
        //   If prefixN < target:
        //      No number of length len starting with k '1's is <= N.
        //      Because the smallest such number is 11..100..0 which is > N (since N starts with something smaller).
        //      Count = 0.

        // Optimization: Precompute prefix sums of powers of 10.
    }

    // Let's restart the loop structure with precomputations.
    
    // Precompute prefix sums of powers of 10: S[i] = 1 + 10 + ... + 10^i
    vector<long long> S(len + 1);
    S[0] = 1; // 10^0
    for (int i = 1; i <= len; ++i) {
        S[i] = (S[i-1] + pow10[i]) % MOD;
    }

    // Precompute suffix values modulo MOD?
    // We need value of N_str[k..len-1] modulo MOD.
    // Let suffix_val[k] = integer value of N_str[k..end] % MOD.
    // suffix_val[len] = 0.
    // suffix_val[k] = (digit[k] * 10^(len-1-k) + ... + digit[len-1] * 10^0) % MOD
    // We can compute this backwards.
    vector<long long> suffix_val(len + 1, 0);
    for (int i = len - 1; i >= 0; --i) {
        int digit = N_str[i] - '0';
        int power_of_10 = len - 1 - i;
        long long term = (digit * pow10[power_of_10]) % MOD;
        suffix_val[i] = (term + suffix_val[i+1]) % MOD;
    }
    
    // However, there is a catch. 
    // When prefixN == target, the count is (actual_suffix_value + 1).
    // Is (actual_suffix_value % MOD + 1) % MOD correct?
    // Yes, because we are adding this count to the total sum modulo MOD.
    // (A + B) % M = (A%M + B%M) % M.
    // So taking the suffix value modulo MOD is fine.

    bool prefix_all_ones = true; // Tracks if N_str[0..k-1] is all '1's

    for (int k = 1; k <= len; ++k) {
        long long count_k = 0;

        // Part A: Numbers with length d where k <= d < len
        // Count = sum_{d=k}^{len-1} 10^(d-k) = sum_{j=0}^{len-1-k} 10^j = S[len-1-k]
        if (len - 1 >= k) {
            count_k = (count_k + S[len - 1 - k]) % MOD;
        }

        // Part B: Numbers with length == len
        // Check the k-th digit (0-indexed k-1) to update prefix_all_ones status
        // Before processing k, prefix_all_ones tells us if N_str[0..k-2] were all '1's.
        // Now we check N_str[k-1].
        if (N_str[k-1] != '1') {
            prefix_all_ones = false;
        }

        if (prefix_all_ones) {
            // The first k digits of N are all '1's.
            // Any number of length len starting with k '1's is <= N if the remaining part <= N's suffix.
            // The remaining part ranges from 0 to suffix_val[k].
            // Count = suffix_val[k] + 1.
            long long current_suffix = suffix_val[k];
            count_k = (count_k + current_suffix + 1) % MOD;
        } else {
            // The first k digits of N are NOT all '1's.
            // Two cases:
            // 1. The prefix of N (length k) is lexicographically > "11...1".
            //    Then all numbers of length len starting with "11...1" are strictly less than N.
            //    Count = 10^(len-k).
            // 2. The prefix of N is lexicographically < "11...1".
            //    Then no number of length len starting with "11...1" is <= N.
            //    Count = 0.
            
            // How to check if prefixN > "11...1" without constructing string?
            // We know prefix_all_ones is false, so there is a mismatch.
            // Find the first position j < k where N_str[j] != '1'.
            // If N_str[j] > '1', then prefixN > target.
            // If N_str[j] < '1', then prefixN < target.
            // Since we iterate k sequentially, we can maintain the state of comparison?
            // Actually, if prefix_all_ones becomes false at step k, it means N_str[k-1] != '1'.
            // If N_str[k-1] > '1', then for THIS k and any larger k?
            // Wait, if N_str[k-1] > '1', then the prefix of length k is definitely > "11..1".
            // What about k+1? The prefix of length k+1 starts with the same mismatch, so it's also > "11..1" (of length k+1)?
            // Yes, because the most significant difference determines the order.
            // So once we encounter a digit > '1', all subsequent prefixes (longer) will also be greater than the corresponding all-ones string.
            // If we encounter a digit < '1' (i.e., '0'), then the prefix is smaller. And all subsequent prefixes will also be smaller.
            
            // So we can maintain a flag: 
            // state = 0 (all ones so far), 1 (already greater), -1 (already smaller).
            // But wait, can we have "110..."? 
            // k=1: '1' -> equal.
            // k=2: '1' -> equal.
            // k=3: '0' -> smaller. State becomes -1.
            // For k=3, target="111", prefix="110". 110 < 111. Count = 0.
            // For k=4, target="1111", prefix="110x". 110x < 1111. Count = 0.
            // Correct.
            
            // What about "112..."?
            // k=3: '2' -> greater. State becomes 1.
            // For k=3, target="111", prefix="112". 112 > 111. Count = 10^(len-3).
            // For k=4, target="1111", prefix="112x". 112x > 1111. Count = 10^(len-4).
            // Correct.
            
            // So we need a state variable.
            // Let's refactor the loop to maintain this state.
        }
    }
    
    // Refactored Loop
    total_sum = 0;
    // state: 0 = equal so far, 1 = already greater, -1 = already smaller
    int state = 0; 
    
    // We also need to re-calculate Part A and Part B properly inside the loop with the state.
    // But Part A depends only on k and len, not on N's content. So that part is static.
    // Part B depends on state.
    
    // Re-initialize state
    state = 0;
    
    for (int k = 1; k <= len; ++k) {
        long long count_k = 0;
        
        // Part A: Lengths < len
        if (len - 1 >= k) {
            count_k = (count_k + S[len - 1 - k]) % MOD;
        }
        
        // Update state based on current digit N_str[k-1]
        if (state == 0) {
            if (N_str[k-1] > '1') {
                state = 1;
            } else if (N_str[k-1] < '1') {
                state = -1;
            }
            // else remains 0
        }
        
        // Part B: Length == len
        if (state == 0) {
            // Prefix matches "11...1" exactly
            long long current_suffix = suffix_val[k];
            count_k = (count_k + current_suffix + 1) % MOD;
        } else if (state == 1) {
            // Prefix is greater than "11...1"
            // All combinations of remaining digits are valid
            count_k = (count_k + pow10[len - k]) % MOD;
        } else {
            // state == -1, Prefix is smaller
            // No valid numbers of length len
            // count_k += 0
        }
        
        total_sum = (total_sum + count_k) % MOD;
    }

    cout << total_sum << endl;

    return 0;
}
