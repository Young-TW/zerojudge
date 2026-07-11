#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>

using namespace std;

inline int char_index(char c) {
    switch (c) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string X, Y;
    while (cin >> X >> Y) {
        // Make X the shorter string to minimize the number of outer iterations
        if (X.size() > Y.size()) {
            swap(X, Y);
        }
        int n = X.size();
        int m = Y.size();
        int W = (m + 63) >> 6;                 // number of 64-bit words
        uint64_t last_mask = (m % 64 == 0) ? ~0ULL : ((1ULL << (m % 64)) - 1);
        
        vector<uint64_t> char_mask[4];
        for (int k = 0; k < 4; ++k) {
            char_mask[k].assign(W, 0);
        }
        for (int j = 0; j < m; ++j) {
            int ci = char_index(Y[j]);
            char_mask[ci][j >> 6] |= (1ULL << (j & 63));
        }
        
        vector<uint64_t> dp(W, 0);
        vector<uint64_t> shifted(W);
        
        for (char c : X) {
            int ci = char_index(c);
            // shifted = (dp << 1) | 1
            uint64_t carry = 1;
            for (int i = 0; i < W; ++i) {
                uint64_t new_carry = dp[i] >> 63;
                shifted[i] = (dp[i] << 1) | carry;
                carry = new_carry;
            }
            shifted[W - 1] &= last_mask;
            
            // dp = x & ~(x - shifted), where x = char_mask[ci] | dp
            uint64_t borrow = 0;
            for (int i = 0; i < W; ++i) {
                uint64_t xi = char_mask[ci][i] | dp[i];
                uint64_t si = shifted[i];
                uint64_t tmp = si + borrow;
                uint64_t new_borrow = (tmp < si) | (xi < tmp);
                uint64_t diff = xi - tmp;
                dp[i] = xi & ~diff;
                borrow = new_borrow;
            }
            dp[W - 1] &= last_mask;
        }
        
        int ans = 0;
        for (int i = 0; i < W; ++i) {
            ans += __builtin_popcountll(dp[i]);
        }
        cout << ans << '\n';
    }
    return 0;
}
