#include <iostream>

using namespace std;
typedef unsigned long long ull;

const ull MOD1 = 1000000007ULL;
const ull MOD2 = 2000000016ULL;

ull fib(ull n, ull mod) {
    if (n == 0) return 0;
    ull a00 = 1, a01 = 1, a10 = 1, a11 = 0;
    ull r00 = 1, r01 = 0, r10 = 0, r11 = 1;
    while (n > 0) {
        if (n & 1) {
            ull c00 = (r00 * a00 + r01 * a10) % mod;
            ull c01 = (r00 * a01 + r01 * a11) % mod;
            ull c10 = (r10 * a00 + r11 * a10) % mod;
            ull c11 = (r10 * a01 + r11 * a11) % mod;
            r00 = c00; r01 = c01; r10 = c10; r11 = c11;
        }
        ull c00 = (a00 * a00 + a01 * a10) % mod;
        ull c01 = (a00 * a01 + a01 * a11) % mod;
        ull c10 = (a10 * a00 + a11 * a10) % mod;
        ull c11 = (a10 * a01 + a11 * a11) % mod;
        a00 = c00; a01 = c01; a10 = c10; a11 = c11;
        n >>= 1;
    }
    return r01;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        while (n--) {
            ull x;
            cin >> x;
            ull y = fib(x, MOD2);
            ull ans = fib(y, MOD1);
            cout << ans << "\n";
        }
    }
    return 0;
}
