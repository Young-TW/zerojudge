#include <iostream>

using namespace std;

long long modpow(long long b, long long p, long long m) {
    long long res = 1;
    b %= m;
    while (p > 0) {
        if (p & 1) res = (res * b) % m;
        b = (b * b) % m;
        p >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long b, p, m;
    while (cin >> b >> p >> m) {
        cout << modpow(b, p, m) << "\n";
    }
    return 0;
}
