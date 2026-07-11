#include <iostream>

using namespace std;

typedef unsigned long long ull;

ull mod_pow(ull base, ull exp, ull mod) {
    ull res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

ull reduce_exp(ull d, ull p) {
    if (d == 0) return 0;
    return (d - 1) % (p - 1) + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ull C, d, p, q;
    while (cin >> C >> d >> p >> q) {
        ull dp = reduce_exp(d, p);
        ull dq = reduce_exp(d, q);
        ull Mp = mod_pow(C, dp, p);
        ull Mq = mod_pow(C, dq, q);
        ull inv_p = mod_pow(p, q - 2, q);
        ull diff = (Mq + q - Mp % q) % q;
        ull t = (diff * inv_p) % q;
        ull M = Mp + p * t;
        cout << M << "\n";
    }
    return 0;
}
