#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const int MOD = 10000000;
const int MAX_N = 1005;
const int MAX_K = 3005;

long long C[MAX_N][MAX_K];

void precompute() {
    for (int i = 0; i < MAX_N; ++i) {
        C[i][0] = 1;
        if (i > 0) {
            for (int j = 1; j <= i; ++j) {
                C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
            }
        }
    }
    // We need combinations up to C[3000][1000]. 
    // The recurrence C(n, k) = C(n-1, k-1) + C(n-1, k) works if we iterate n then k.
    // But our array dimensions are [n][k] where n is length (up to 1000) and k is alphabet size (up to 3000).
    // Actually, the formula we need is C(available_letters, count_to_pick).
    // available_letters can be up to 3000. count_to_pick up to 1000.
    // So we need C[n][k] where n is up to 3000, k up to 1000.
    // Let's redefine dimensions or logic.
    // Let dp[n][k] = C(n, k). n up to 3000, k up to 1000.
}

long long comb[3005][1005];

void init_comb() {
    for (int i = 0; i <= 3000; ++i) {
        comb[i][0] = 1;
        if (i <= 1000) comb[i][i] = 1; // Only if i <= 1000
        for (int j = 1; j <= min(i, 1000); ++j) {
            if (j == i) {
                comb[i][j] = 1;
            } else {
                comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % MOD;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_comb();

    int n;
    while (cin >> n) {
        vector<int> k(n);
        for (int i = 0; i < n; ++i) {
            cin >> k[i];
        }

        long long rank = 1; // 1-based index usually, but problem sample shows 1->1, 2999->3000? 
        // Sample: 
        // 1 \n 0 -> 0000001. (Length 1, letter 0). 
        // Words of length 1: (0), (1), ... (2999). 
        // (0) is the 1st word.
        // 1 \n 2999 -> 0003000. (Length 1, letter 2999). It is the 3000th word.
        // So rank is 1-based.
        // Wait, sample output for "1 \n 0" is "0000001". 
        // If we count strictly:
        // Length 1 words: C(3000, 1) = 3000 words.
        // Order: (0), (1), ..., (2999).
        // (0) is #1. (2999) is #3000.
        // Length 2 words start after all length 1 words.
        // Total words before length L: sum_{len=1}^{L-1} C(3000, len).
        
        // Calculate words with length < n
        for (int len = 1; len < n; ++len) {
            rank = (rank + comb[3000][len]) % MOD;
        }

        // Calculate words with length == n that are lexicographically smaller
        // A word is a sequence c1, c2, ..., cn with 0 <= c1 < c2 < ... < cn < 3000.
        // We iterate through positions i from 0 to n-1.
        // At position i, the current character is k[i].
        // The previous character was k[i-1] (or -1 if i==0).
        // We can pick any character v such that prev < v < k[i].
        // If we pick v, then we need to choose (n - 1 - i) more characters from the range (v+1, 2999).
        // Number of available characters after v is 2999 - v.
        // We need to choose rem = n - 1 - i characters.
        // So we add C(2999 - v, rem) for each valid v.
        // Instead of looping v, we can use the identity:
        // Sum_{v=prev+1}^{k[i]-1} C(2999-v, rem)
        // Let x = 2999 - v. As v goes from prev+1 to k[i]-1, x goes from 2999-(prev+1) down to 2999-(k[i]-1).
        // This is sum of C(x, rem) for x in some range.
        // Identity: Sum_{i=r}^{n} C(i, r) = C(n+1, r+1).
        // Here we sum C(x, rem) for x from L to R.
        // Sum_{x=rem}^{M} C(x, rem) = C(M+1, rem+1).
        // So Sum_{x=L}^{R} C(x, rem) = C(R+1, rem+1) - C(L, rem+1).
        
        // Range of v: [prev+1, k[i]-1].
        // Corresponding x = 2999 - v.
        // Max x (when v=min): 2999 - (prev+1).
        // Min x (when v=max): 2999 - (k[i]-1).
        // Let X_max = 2999 - prev - 1.
        // Let X_min = 2999 - k[i] + 1.
        // We need sum_{x=X_min}^{X_max} C(x, rem).
        // This equals C(X_max+1, rem+1) - C(X_min, rem+1).
        
        int prev = -1;
        for (int i = 0; i < n; ++i) {
            int current = k[i];
            int rem = n - 1 - i;
            
            // Valid v: prev+1 ... current-1
            if (current > prev + 1) {
                int X_max = 2999 - (prev + 1);
                int X_min = 2999 - (current - 1);
                
                // We need sum C(x, rem) for x in [X_min, X_max]
                // Formula: C(X_max+1, rem+1) - C(X_min, rem+1)
                // Note: if X_min < rem, C(X_min, rem+1) is 0, which is correct because sum starts effectively from rem.
                // But our comb function handles n < k as 0? 
                // Our init_comb only computes up to k=1000. rem+1 <= 1000.
                // X_max can be up to 2999.
                
                long long term1 = 0;
                if (X_max + 1 >= rem + 1) {
                     // Check bounds for comb array. comb[3000][1000] is max needed.
                     // X_max+1 <= 3000. rem+1 <= 1000. Safe.
                     term1 = comb[X_max+1][rem+1];
                }
                
                long long term2 = 0;
                if (X_min >= rem + 1) {
                    term2 = comb[X_min][rem+1];
                }
                
                long long count = (term1 - term2 + MOD) % MOD;
                rank = (rank + count) % MOD;
            }
            
            prev = current;
        }

        cout << setfill('0') << setw(7) << rank << "\n";
    }

    return 0;
}
