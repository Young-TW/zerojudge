#include <bits/stdc++.h>
using namespace std;

using uint64 = unsigned long long;
using u128   = unsigned __int128;

// (a * b) % mod   – works for mod up to 1e18
static inline uint64 mul_mod(uint64 a, uint64 b, uint64 mod) {
    return (u128)a * b % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    uint64 x, z;
    string y;
    while (cin >> x >> y >> z) {
        if (z == 1) {
            cout << 0 << '\n';
            continue;
        }
        uint64 base = x % z;
        uint64 res  = 1 % z;          // =1
        for (char c : y) {
            res = mul_mod(res, res, z);   // square
            if (c == '1')
                res = mul_mod(res, base, z);
        }
        cout << res << '\n';
    }
    return 0;
}
