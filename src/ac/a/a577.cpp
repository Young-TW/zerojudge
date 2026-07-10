#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

const ll MOD = 998244353LL;
const ll G = 3;

ll modpow(ll a, ll e) {
    ll r = 1 % MOD;
    a %= MOD;
    if (a < 0) a += MOD;
    while (e > 0) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

const int MAXN = 1 << 18;
ll A[MAXN], B[MAXN];
int rev[MAXN];
ll roots[MAXN + 1];

void init(int n) {
    rev[0] = 0;
    for (int i = 1; i < n; i++) {
        rev[i] = rev[i >> 1] >> 1;
        if (i & 1) rev[i] |= n >> 1;
    }
    ll w = modpow(G, (MOD - 1) / n);
    roots[0] = 1;
    for (int i = 1; i < n; i++) roots[i] = roots[i - 1] * w % MOD;
    roots[n] = 1;
}

void ntt(ll* a, int n, bool invert) {
    for (int i = 0; i < n; i++)
        if (i < rev[i]) { ll t = a[i]; a[i] = a[rev[i]]; a[rev[i]] = t; }
    for (int len = 2; len <= n; len <<= 1) {
        int half = len >> 1;
        int step = n / len;
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < half; j++) {
                ll w = invert ? roots[n - j * step] : roots[j * step];
                ll u = a[i + j];
                ll v = a[i + j + half] * w % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + half] = (u - v + MOD) % MOD;
            }
        }
    }
    if (invert) {
        ll ninv = modpow(n, MOD - 2);
        for (int i = 0; i < n; i++) a[i] = a[i] * ninv % MOD;
    }
}

const int MAXDIG = 1 << 18;
char sa[MAXDIG], sb[MAXDIG];
char outbuf[1 << 22];

int main() {
    int outlen = 0;
    while (scanf("%s %s", sa, sb) == 2) {
        int la = (int)strlen(sa);
        int lb = (int)strlen(sb);

        bool azero = true, bzero = true;
        for (int i = 0; i < la; i++) if (sa[i] != '0') { azero = false; break; }
        for (int i = 0; i < lb; i++) if (sb[i] != '0') { bzero = false; break; }
        if (azero || bzero) {
            outbuf[outlen++] = '0';
            outbuf[outlen++] = '\n';
            continue;
        }

        int na = (la + 1) / 2;
        int nb = (lb + 1) / 2;

        int sz = 1;
        while (sz < na + nb) sz <<= 1;

        init(sz);

        for (int i = 0; i < na; i++) {
            int idx = la - 1 - 2 * i;
            int lo = sa[idx] - '0';
            int hi = (idx - 1 >= 0) ? (sa[idx - 1] - '0') : 0;
            A[i] = hi * 10 + lo;
        }
        for (int i = na; i < sz; i++) A[i] = 0;

        for (int i = 0; i < nb; i++) {
            int idx = lb - 1 - 2 * i;
            int lo = sb[idx] - '0';
            int hi = (idx - 1 >= 0) ? (sb[idx - 1] - '0') : 0;
            B[i] = hi * 10 + lo;
        }
        for (int i = nb; i < sz; i++) B[i] = 0;

        ntt(A, sz, false);
        ntt(B, sz, false);
        for (int i = 0; i < sz; i++) A[i] = A[i] * B[i] % MOD;
        ntt(A, sz, true);

        ll carry = 0;
        for (int i = 0; i < sz; i++) {
            ll val = A[i] + carry;
            A[i] = val % 100;
            carry = val / 100;
        }

        int top = sz - 1;
        while (top > 0 && A[top] == 0) top--;

        if (A[top] >= 10)
            outbuf[outlen++] = '0' + (int)(A[top] / 10);
        outbuf[outlen++] = '0' + (int)(A[top] % 10);
        for (int i = top - 1; i >= 0; i--) {
            outbuf[outlen++] = '0' + (int)(A[i] / 10);
            outbuf[outlen++] = '0' + (int)(A[i] % 10);
        }
        outbuf[outlen++] = '\n';
    }
    fwrite(outbuf, 1, outlen, stdout);
    return 0;
}
