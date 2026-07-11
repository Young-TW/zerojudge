#include <iostream>

using namespace std;

long long extgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    long long e = 23333;
    long long phi = 524288; // 2^19
    long long d, y;
    extgcd(e, phi, d, y);
    d = (d % phi + phi) % phi;
    
    long long mod = 1048576; // 2^20
    
    while (cin >> n) {
        long long base = n % mod;
        long long exp = d;
        long long res = 1;
        while (exp > 0) {
            if (exp & 1) {
                res = (res * base) % mod;
            }
            base = (base * base) % mod;
            exp >>= 1;
        }
        cout << res << "\n";
    }
    
    return 0;
}
