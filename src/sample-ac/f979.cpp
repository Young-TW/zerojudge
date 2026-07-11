#include <iostream>

using namespace std;

const long long M = 1000000007;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= M;
    if (base < 0) base += M;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % M;
        base = (base * base) % M;
        exp >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long x, n;
    while (cin >> x >> n) {
        if (x == 1) {
            long long a = n + 1;
            long long b = n + 2;
            if (a % 2 == 0) a /= 2;
            else b /= 2;
            long long ans = (a % M) * (b % M) % M;
            cout << ans << "\n";
        } else {
            long long n1 = (n + 1) % M;
            long long n2 = (n + 2) % M;
            long long xn1 = power(x, n + 1);
            long long xn2 = (xn1 * (x % M)) % M;
            
            long long A = (1 - n2 * xn1 % M + M) % M;
            A = (A + n1 * xn2 % M) % M;
            
            long long inv_1_x = power((1 - x % M + M) % M, M - 2);
            long long inv_B = (inv_1_x * inv_1_x) % M;
            
            long long ans = A * inv_B % M;
            cout << ans << "\n";
        }
    }
    return 0;
}
