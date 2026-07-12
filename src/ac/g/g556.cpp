#include <cstdio>

using namespace std;

const long long MOD = 998244353;

inline long long fib(long long n) {
    long long a = 0, b = 1;
    for (int i = 63; i >= 0; i--) {
        long long c = (a * (2 * b - a + MOD)) % MOD;
        long long d = (a * a + b * b) % MOD;
        if ((n >> i) & 1) {
            a = d;
            b = (c + d) % MOD;
        } else {
            a = c;
            b = d;
        }
    }
    return a;
}

int main() {
    int t;
    if (scanf("%d", &t) == 1) {
        while (t--) {
            long long n;
            scanf("%lld", &n);
            long long ans = fib(n + 2);
            ans = (ans - 1 + MOD) % MOD;
            printf("%lld\n", ans);
        }
    }
    return 0;
}
