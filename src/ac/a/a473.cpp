#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cstdint>
using namespace std;

typedef long long ll;
typedef __int128 lll;

static char ibuf[1 << 20];
static int ilen = 0, ipos = 0;
static inline int gc() {
    if (ipos == ilen) {
        ilen = (int)fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}
static inline bool readLL(ll &x) {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9') && c != '-' && c != '+') c = gc();
    if (c == -1) return false;
    bool neg = false;
    if (c == '-') { neg = true; c = gc(); }
    else if (c == '+') { c = gc(); }
    if (c == -1 || c < '0' || c > '9') return false;
    x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    if (neg) x = -x;
    return true;
}

struct RNG {
    unsigned long long s;
    RNG(unsigned long long seed) : s(seed ? seed : 1) {}
    inline unsigned long long next() {
        s ^= s << 13; s ^= s >> 7; s ^= s << 17; return s;
    }
};

int main() {
    ll tmpN;
    RNG rng(0x9E3779B97F4A7C15ULL);
    ll primes[5] = { 998244353LL, 1000000007LL, 1000000009LL, 1000000021LL, 1000000033LL };
    while (readLL(tmpN)) {
        int N = (int)tmpN;
        size_t sz = (size_t)N * N;
        vector<ll> A(sz), B(sz), C(sz);
        for (size_t i = 0; i < sz; i++) readLL(A[i]);
        for (size_t i = 0; i < sz; i++) readLL(B[i]);
        for (size_t i = 0; i < sz; i++) readLL(C[i]);

        vector<ll> r(N), br(N), abr(N);
        bool ok = true;
        for (int pi = 0; pi < 5 && ok; pi++) {
            ll p = primes[pi];
            for (int i = 0; i < N; i++) r[i] = (ll)(rng.next() % (unsigned long long)p);
            // br = B * r  (mod p)
            for (int i = 0; i < N; i++) {
                lll s = 0;
                const ll* Bi = B.data() + (size_t)i * N;
                for (int j = 0; j < N; j++) s += (lll)Bi[j] * r[j];
                ll v = (ll)(s % (lll)p);
                if (v < 0) v += p;
                br[i] = v;
            }
            // abr = A * br  (mod p)
            for (int i = 0; i < N; i++) {
                lll s = 0;
                const ll* Ai = A.data() + (size_t)i * N;
                for (int j = 0; j < N; j++) s += (lll)Ai[j] * br[j];
                ll v = (ll)(s % (lll)p);
                if (v < 0) v += p;
                abr[i] = v;
            }
            // compare with C * r (mod p)
            for (int i = 0; i < N && ok; i++) {
                lll s = 0;
                const ll* Ci = C.data() + (size_t)i * N;
                for (int j = 0; j < N; j++) s += (lll)Ci[j] * r[j];
                ll v = (ll)(s % (lll)p);
                if (v < 0) v += p;
                if (v != abr[i]) ok = false;
            }
        }
        printf(ok ? "YES\n" : "NO\n");
    }
    return 0;
}
