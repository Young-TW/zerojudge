#include <iostream>

using namespace std;

long long gcd(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        a %= b;
        long long tmp = a;
        a = b;
        b = tmp;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long x1, y1, x2, y2;
    while (cin >> x1 >> y1 >> x2 >> y2) {
        long long dy = y2 - y1;
        long long dx = x2 - x1;
        long long dx2 = dx * dx;
        long long g = gcd(dy, dx2);
        long long p = dy / g;
        long long q = dx2 / g;
        if (q < 0) {
            p = -p;
            q = -q;
        }
        long long a = q;
        long long b = p;
        long long c = -2 * p * x1;
        long long d = p * x1 * x1 + q * y1;
        
        cout << a << "y = " << b << "x^2 + " << c << "x + " << d << "\n";
    }
    return 0;
}
