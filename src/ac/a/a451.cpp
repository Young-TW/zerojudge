#include <cstdio>
using namespace std;

typedef long long ll;

static void fib(ll n, ll mod, ll &fn, ll &fn1) {
    if (n == 0) { fn = 0 % mod; fn1 = 1 % mod; return; }
    ll a, b;
    fib(n >> 1, mod, a, b);
    ll c = (a * (((2 * b - a) % mod + mod) % mod)) % mod;
    ll d = (a * a + b * b) % mod;
    if (n & 1) { fn = d; fn1 = (c + d) % mod; }
    else { fn = c; fn1 = d; }
}

int main() {
    ll n, m;
    while (scanf("%lld %lld", &n, &m) == 2) {
        ll mod = 1LL << m;
        ll fn, fn1;
        fib(n, mod, fn, fn1);
        printf("%lld\n", fn);
    }
    return 0;
}
