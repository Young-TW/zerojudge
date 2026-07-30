#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128  = __int128_t;

// truncate a signed integer to the last M decimal digits (keep sign)
static inline int64 truncate_val(int64 v, int64 mod) {
    return v % mod;                     // C++ remainder keeps the sign
}

// signed multiplication with truncation
static inline int64 mul_mod(int64 a, int64 b, int64 mod) {
    i128 prod = (i128)a * (i128)b;
    return (int64)(prod % mod);
}

// signed addition with truncation
static inline int64 add_mod(int64 a, int64 b, int64 mod) {
    int64 sum = a + b;                  // never overflows (|a|,|b| < mod ≤ 1e9)
    return sum % mod;
}

// binary exponentiation, all multiplications are truncated
static int64 pow_mod(int64 base, int exp, int64 mod) {
    int64 result = 1 % mod;
    int64 cur = base;
    while (exp > 0) {
        if (exp & 1) result = mul_mod(result, cur, mod);
        cur = mul_mod(cur, cur, mod);
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    int64 C;
    while (cin >> N >> C >> M) {
        int64 mod = 1;
        for (int i = 0; i < M; ++i) mod *= 10LL;   // 10^M, M ≤ 9

        int64 c = truncate_val(C, mod);           // variable value

        int64 answer = 0;                         // current Horner sum
        for (int i = 0; i < N; ++i) {
            int64 A; int B;
            cin >> A >> B;
            int64 a = truncate_val(A, mod);       // coefficient

            int64 term;
            if (B == 0) {
                term = a;
            } else {
                int64 p = pow_mod(c, B, mod);     // C^B truncated
                term = mul_mod(a, p, mod);        // A·C^B truncated
            }
            answer = add_mod(answer, term, mod); // add term, truncate
        }

        int64 out = llabs(answer);                // sign ignored
        cout << setw(M) << setfill('0') << out << '\n';
    }
    return 0;
}
