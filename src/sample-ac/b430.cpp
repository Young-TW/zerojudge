#include <iostream>

using namespace std;

unsigned long long mul_mod(unsigned long long a, unsigned long long b, unsigned long long mod) {
    unsigned long long res = 0;
    a %= mod;
    while (b > 0) {
        if (b & 1) {
            res += a;
            if (res >= mod) res -= mod;
        }
        a <<= 1;
        if (a >= mod) a -= mod;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unsigned long long a, b, n;
    while (cin >> a >> b >> n) {
        cout << mul_mod(a, b, n) << '\n';
    }
    
    return 0;
}
