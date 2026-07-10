#include <iostream>
using namespace std;

long long extgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long x1, y1;
    long long g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int main() {
    int K;
    while (cin >> K) {
        while (K--) {
            long long m, a, b;
            cin >> m >> a >> b;
            long long c, y;
            long long g = extgcd(a, m, c, y);
            if (g != 1) {
                cout << "No inverse, gcd(a,m)=" << g << "\n";
            } else {
                c = ((c % m) + m) % m;
                long long d = ((-c * b) % m + m) % m;
                cout << c << " " << d << "\n";
            }
        }
    }
    return 0;
}
