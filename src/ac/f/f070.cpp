#include <iostream>
#include <vector>

using namespace std;

long long ext_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long a1, r1;
    if (!(cin >> a1 >> r1)) return 0;

    long long A = a1, R = r1;
    bool valid = true;

    long long a2, r2;
    while (cin >> a2 >> r2) {
        long long p, q;
        long long g = ext_gcd(A, a2, p, q);
        
        if ((r2 - R) % g != 0) {
            valid = false;
            break;
        }
        
        long long lcm = A / g * a2;
        long long mul = (r2 - R) / g;
        
        long long x = (p * mul) % (a2 / g);
        if (x < 0) x += (a2 / g);
        
        R = (R + A * x) % lcm;
        if (R < 0) R += lcm;
        A = lcm;
    }

    if (!valid) {
        cout << -1 << "\n";
    } else {
        cout << R << "\n";
    }

    return 0;
}
