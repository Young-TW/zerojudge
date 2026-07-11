#include <iostream>

using namespace std;
using u128 = __int128;
using u64 = unsigned long long;

u64 mul_mod(u64 a, u64 b, u64 mod) {
    return (u64)((u128)a * b % mod);
}

u64 pow_mod(u64 a, u64 b, u64 mod) {
    u64 res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = mul_mod(res, a, mod);
        a = mul_mod(a, a, mod);
        b >>= 1;
    }
    return res;
}

bool is_prime(u64 n) {
    if (n < 2) return false;
    if (n < 4) return true;
    if (!(n & 1)) return false;

    u64 d = n - 1;
    int r = 0;
    while (!(d & 1)) {
        d >>= 1;
        r++;
    }

    u64 bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (u64 a : bases) {
        if (a % n == 0) continue;
        u64 x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int i = 0; i < r - 1; i++) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    u64 n;
    while (cin >> n) {
        if (is_prime(n)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
