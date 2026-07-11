#include <iostream>

using namespace std;

typedef unsigned long long ull;

const ull MOD = 1000000007;
const ull MOD_MINUS_1 = 1000000006;

ull fib(ull n, ull m) {
    if (n == 0) return 0;
    ull a = 0, b = 1;
    for (int i = 31; i >= 0; i--) {
        ull c = (a * ((2 * b + m - a) % m)) % m;
        ull d = (a * a + b * b) % m;
        if ((n >> i) & 1) {
            a = d;
            b = (c + d) % m;
        } else {
            a = c;
            b = d;
        }
    }
    return a;
}

ull power(ull base, ull exp, ull m) {
    ull res = 1;
    base %= m;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % m;
        base = (base * base) % m;
        exp >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    while (cin >> t) {
        while (t--) {
            ull a, b;
            cin >> a >> b;
            ull fa = fib(a, MOD);
            if (fa == 0) {
                cout << 0 << "\n";
            } else {
                ull fb = fib(b, MOD_MINUS_1);
                cout << power(fa, fb, MOD) << "\n";
            }
        }
    }
    return 0;
}
