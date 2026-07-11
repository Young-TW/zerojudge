#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000009;
const int MAX_VAL = 2005; // Maximum sum of p[i] + n could be around 1000 + 1000 = 2000

long long fact[MAX_VAL];
long long invFact[MAX_VAL];

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

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAX_VAL; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    invFact[MAX_VAL - 1] = modInverse(fact[MAX_VAL - 1]);
    for (int i = MAX_VAL - 2; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();

    int T;
    if (!(cin >> T)) return 0;

    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
        }

        // The problem describes a recurrence that counts the number of paths 
        // from (p[1], p[2], ..., p[n]) to (0, 0, ..., 0) moving one step back 
        // in any dimension, maintaining the non-increasing order constraint implicitly 
        // by the definition domain.
        // However, the condition p[1] >= p[2] >= ... >= p[n] is given for the input.
        // The recurrence F(p) = sum(F(p - e_i)) is the standard recurrence for 
        // multinomial coefficients if there were no ordering constraints on the intermediate states.
        // But the problem states "F(...) = ... if p[1]>=p[2]>=...>=p[n]>=0", else 0.
        // This implies we are counting paths that stay within the region x1 >= x2 >= ... >= xn >= 0.
        // This is equivalent to counting Standard Young Tableaux of a specific shape?
        // Or is it related to the Hook Length Formula?
        // Let's re-read carefully.
        // F(0,0,...,0) = 1.
        // F(p) = sum F(p - e_i) if p is non-increasing.
        // This looks like counting the number of ways to reduce the sequence to all zeros
        // by decrementing one element at a time, such that the sequence remains non-increasing at every step.
        // This is exactly the number of Standard Young Tableaux of shape lambda = (p[1], p[2], ..., p[n]).
        // Wait, usually SYT is defined for partitions. Here p is a partition.
        // The number of SYT of shape lambda is given by the Hook Length Formula:
        // f^lambda = (sum lambda_i)! / product(hook_length(c))
        // Let's verify with sample cases.
        // Sample 1: n=3, p={7, 5, 4}. Sum = 16.
        // Shape:
        // . . . . . . .
        // . . . . .
        // . . . .
        // Hooks:
        // Row 0: (7-0)+(3-0)-1 - ? No.
        // Hook length at (i, j) (0-indexed) = (lambda_i - j) + (lambda'_j - i) - 1.
        // where lambda' is the conjugate partition.
        // Let's calculate hooks for {7, 5, 4}:
        // Row 0 (len 7):
        // j=0: right=6, down=2 (rows 1,2 have col 0). hook = 6+2+1 = 9?
        // Formula: hook(i,j) = (number of cells to right) + (number of cells below) + 1.
        // Grid:
        // (0,0) to (0,6)
        // (1,0) to (1,4)
        // (2,0) to (2,3)
        //
        // Hooks:
        // Row 0:
        // j=0: right 6, down 2 -> 9
        // j=1: right 5, down 2 -> 8
        // j=2: right 4, down 2 -> 7
        // j=3: right 3, down 2 -> 6
        // j=4: right 2, down 1 (row 2 has col 4? No, row 2 len 4, indices 0..3) -> down 1 (only row 1) -> 2+1+1=4?
        // Let's list lengths: 7, 5, 4.
        // Col lengths (conjugate):
        // Col 0: 3 rows
        // Col 1: 3 rows
        // Col 2: 3 rows
        // Col 3: 3 rows
        // Col 4: 2 rows (indices 0, 1)
        // Col 5: 1 row (index 0)
        // Col 6: 1 row (index 0)
        //
        // Calculate hooks h(i,j):
        // i=0:
        // j=0: (7-1-0) + (3-1-0) + 1 = 6 + 2 + 1 = 9
        // j=1: 5 + 2 + 1 = 8
        // j=2: 4 + 2 + 1 = 7
        // j=3: 3 + 2 + 1 = 6
        // j=4: 2 + 1 + 1 = 4 (col 4 has height 2, so below is 1)
        // j=5: 1 + 0 + 1 = 2
        // j=6: 0 + 0 + 1 = 1
        // Row 0 hooks: 9, 8, 7, 6, 4, 2, 1
        //
        // i=1 (len 5):
        // j=0: (5-1-0) + (3-1-1) + 1 = 4 + 1 + 1 = 6
        // j=1: 3 + 1 + 1 = 5
        // j=2: 2 + 1 + 1 = 4
        // j=3: 1 + 1 + 1 = 3
        // j=4: 0 + 0 + 1 = 1 (col 4 height 2, i=1, below=0)
        // Row 1 hooks: 6, 5, 4, 3, 1
        //
        // i=2 (len 4):
        // j=0: (4-1-0) + (3-1-2) + 1 = 3 + 0 + 1 = 4
        // j=1: 2 + 0 + 1 = 3
        // j=2: 1 + 0 + 1 = 2
        // j=3: 0 + 0 + 1 = 1
        // Row 2 hooks: 4, 3, 2, 1
        //
        // Product of hooks:
        // R0: 9*8*7*6*4*2*1 = 24192
        // R1: 6*5*4*3*1 = 360
        // R2: 4*3*2*1 = 24
        // Total Prod = 24192 * 360 * 24 = 209018880
        // N = 7+5+4 = 16. 16! is huge.
        // Result = 16! / Prod.
        // Let's check sample output 1: 100100.
        // 16! = 20922789888000
        // 20922789888000 / 209018880 = 100100. Exactly!
        //
        // So the problem is indeed asking for the number of Standard Young Tableaux of shape p.
        // Algorithm:
        // 1. Read p.
        // 2. Compute N = sum(p).
        // 3. Construct the conjugate partition to easily get column heights.
        // 4. Calculate product of hook lengths modulo MOD.
        // 5. Result = N! * modInverse(product) % MOD.
        //
        // Constraints: n <= 1000, p[i] <= 1000.
        // Max N = 1000 * 1000 = 1,000,000.
        // We need factorials up to 1,000,000.
        // MAX_VAL should be 1000005.
        // Precomputation of factorials is O(N_max).
        // Calculating hooks: O(N) or O(n * max_p). Since sum(p) <= 10^6, iterating over all cells is fine.
        // Time limit is usually 1s. 10^6 operations is fine.
        // We need to increase MAX_VAL.

        long long total_sum = 0;
        for (int x : p) total_sum += x;

        // Conjugate partition
        // max value in p is p[0].
        int max_col = p.empty() ? 0 : p[0];
        vector<int> col_height(max_col, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < p[i]; j++) {
                col_height[j]++;
            }
        }

        long long hook_product = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < p[i]; j++) {
                // hook length = (p[i] - j - 1) + (col_height[j] - i - 1) + 1
                // = p[i] - j + col_height[j] - i - 1
                long long h = (long long)p[i] - j + col_height[j] - i - 1;
                hook_product = (hook_product * (h % MOD)) % MOD;
            }
        }

        long long numerator = fact[total_sum];
        long long denominator_inv = modInverse(hook_product);
        long long ans = (numerator * denominator_inv) % MOD;

        cout << "Case " << t << ": " << ans << "\n";
    }

    return 0;
}
