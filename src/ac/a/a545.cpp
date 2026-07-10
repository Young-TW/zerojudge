#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

const ll MOD = 100000007LL;

ll modpow(ll base, ll exp, ll mod) {
    ll res = 1 % mod;
    base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

ll modinv(ll a, ll mod) {
    return modpow(a, mod - 2, mod);
}

static inline ll readLL() {
    ll x = 0; int c = getchar_unlocked();
    while (c < '0' || c > '9') { if (c == -1) return -1; c = getchar_unlocked(); }
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = getchar_unlocked(); }
    return x;
}

int main() {
    int m, n;
    while (scanf("%d %d", &m, &n) == 2) {
        if (m == 0 && n == 0) break;
        int total = m * n;
        ll *a = new ll[total];
        ll prodNonZero = 1 % MOD;
        int zeroCount = 0;
        for (int i = 0; i < total; i++) {
            ll v;
            if (scanf("%lld", &v) != 1) { v = 0; }
            ll r = v % MOD;
            if (r < 0) r += MOD;
            a[i] = r;
            if (r == 0) {
                zeroCount++;
            } else {
                prodNonZero = prodNonZero * r % MOD;
            }
        }
        int q;
        if (scanf("%d", &q) != 1) q = 0;
        for (int i = 0; i < q; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            int idx = (x - 1) * n + (y - 1);
            ll r = a[idx];
            ll ans;
            if (r != 0) {
                if (zeroCount > 0) {
                    ans = 0;
                } else {
                    ans = prodNonZero * modinv(r, MOD) % MOD;
                }
            } else {
                if (zeroCount > 1) {
                    ans = 0;
                } else {
                    ans = prodNonZero;
                }
            }
            printf("%lld\n", ans);
        }
        delete[] a;
    }
    return 0;
}
