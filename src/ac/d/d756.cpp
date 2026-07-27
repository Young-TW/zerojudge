#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
using i128  = __int128_t;

bool isTriangular(int64 n) {
    // test whether 8*n + 1 is a perfect square
    i128 v = (i128)8 * n + 1;
    long double d = sqrt((long double)v);
    int64 s = (int64)d;
    while ((i128)(s + 1) * (s + 1) <= v) ++s;
    while ((i128)s * s > v) --s;
    return (i128)s * s == v;
}

int64 oddDivisorCount(int64 n) {
    // remove all factors 2
    while ((n & 1LL) == 0) n >>= 1;
    int64 cnt = 1;
    for (int64 p = 3; p * p <= n; p += 2) {
        if (n % p == 0) {
            int exp = 0;
            while (n % p == 0) {
                n /= p;
                ++exp;
            }
            cnt *= (exp + 1);
        }
    }
    if (n > 1) cnt *= 2;          // remaining prime factor
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int64 N;
    while (cin >> N) {
        if (N == 0) {
            cout << 1 << '\n';
            continue;
        }
        int64 ans = oddDivisorCount(N);
        if (isTriangular(N)) ++ans;
        cout << ans << '\n';
    }
    return 0;
}
