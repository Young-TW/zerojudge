#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

long long isqrt(long long n) {
    if (n < 0) return -1;
    long long x = (long long)sqrtl((long double)n);
    while (x > 0 && x * x > n) x--;
    while ((x + 1) * (x + 1) <= n) x++;
    return x;
}

int main() {
    long long B, R;
    while (cin >> B >> R) {
        long long outL = -1, outW = -1;
        for (long long b = 1; b * b <= R; b++) {
            if (R % b != 0) continue;
            long long a = R / b;       // a >= b, a*b = R
            long long S = a + b;
            long long disc = S * S + 4 * B;
            long long s = isqrt(disc);
            if (s >= 0 && s * s == disc) {
                long long num = s - S;       // = 4t
                if (num > 0 && num % 4 == 0) {
                    long long t = num / 4;
                    outL = a + 2 * t;
                    outW = b + 2 * t;
                    break; // smallest b => largest a-b => largest L-W
                }
            }
        }
        cout << outL << " " << outW << "\n";
    }
    return 0;
}
