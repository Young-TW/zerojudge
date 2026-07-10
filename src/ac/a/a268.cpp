#include <iostream>
#include <vector>
#include <array>
#include <cstdio>
using namespace std;

static const long long MOD = 1000000007LL;
static const int MAXB = 10010;
static const int MAXW = (MAXB + 63) / 64; // number of 64-bit words

// ---- fast input ----
static const int INBUF = 1 << 16;
static char inbuf[INBUF];
static int inpos = 0, inlen = 0;
static inline int gc(){
    if(inpos == inlen){
        inlen = (int)fread(inbuf, 1, INBUF, stdin);
        inpos = 0;
        if(inlen == 0) return -1;
    }
    return inbuf[inpos++];
}
static inline bool readInt(int& out){
    int c = gc();
    while(c != -1 && (c < '0' || c > '9') && c != '-') c = gc();
    if(c == -1) return false;
    bool neg = false;
    if(c == '-'){ neg = true; c = gc(); }
    int x = 0;
    while(c >= '0' && c <= '9'){ x = x*10 + (c - '0'); c = gc(); }
    out = neg ? -x : x;
    return true;
}

typedef array<uint64_t, MAXW> Big;

static inline void big_clear(Big& a){ a.fill(0); }

static inline void big_setbit(Big& a, int b){
    a[b >> 6] |= (1ULL << (b & 63));
}

// a + b, scanning words [0..hiw). Result in r.
static inline void big_add(const Big& a, const Big& b, Big& r, int hiw){
    uint64_t carry = 0;
    for(int i=0;i<hiw;i++){
        uint64_t x = a[i], y = b[i];
        uint64_t s = x + y + carry;
        r[i] = s;
        carry = (s < x) || (carry && s == x); // carry out
    }
    if(carry && hiw < MAXW) r[hiw] = carry;
}

// compare a vs b scanning words [hiw-1 .. 0]. -1,0,1
static inline int big_cmp(const Big& a, const Big& b, int hiw){
    for(int i=hiw-1;i>=0;i--){
        if(a[i]!=b[i]) return a[i] > b[i] ? 1 : -1;
    }
    return 0;
}

// reduce mod MOD, scanning words [0..hiw)
static inline long long big_reduce(const Big& a, const vector<long long>& pow2mod, int hiw){
    long long r=0;
    for(int i=0;i<hiw;i++){
        uint64_t w = a[i];
        int base = i*64;
        while(w){
            if(w & 1ULL) r = (r + pow2mod[base]) % MOD;
            w >>= 1;
            base++;
        }
    }
    return r;
}

// gather: disks 1..d, from config ff, to all on peg `target`.
// Sets bit (i-1) for each disk i that triggers a move.
static inline void gatherBits(Big& bits, int d, int target, const vector<int>& ff){
    big_clear(bits);
    int g = target;
    for(int i=d;i>=1;i--){
        if(ff[i]!=g){
            big_setbit(bits, i-1);
            g = 6 - ff[i] - g;
        }
    }
}

static inline void scatterBits(Big& bits, int d, int src, const vector<int>& tt){
    big_clear(bits);
    int g = src;
    for(int i=d;i>=1;i--){
        if(tt[i]!=g){
            big_setbit(bits, i-1);
            g = 6 - g - tt[i];
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<long long> pow2mod(MAXB);
    pow2mod[0]=1;
    for(int i=1;i<MAXB;i++) pow2mod[i] = pow2mod[i-1]*2 % MOD;

    string outbuf;
    outbuf.reserve(1<<20);

    int N;
    while(readInt(N)){
        if(N==0) break;
        vector<int> f(N+1), t(N+1);
        for(int i=1;i<=N;i++) readInt(f[i]);
        for(int i=1;i<=N;i++) readInt(t[i]);

        int k=-1;
        for(int i=N;i>=1;i--){ if(f[i]!=t[i]){ k=i; break; } }
        if(k==-1){ outbuf += "0\n"; continue; }

        int aux = 6 - f[k] - t[k];

        Big g1, s1, g2, s2;
        gatherBits(g1, k-1, aux, f);
        scatterBits(s1, k-1, aux, t);
        gatherBits(g2, k-1, t[k], f);
        scatterBits(s2, k-1, f[k], t);

        // bits up to position k possible (carry). word count = k/64 + 2.
        int hiw = (k + 2) / 64 + 1;
        if(hiw > MAXW) hiw = MAXW;

        Big sumA, tmp, sumB;
        big_add(g1, s1, sumA, hiw);
        big_add(g2, s2, tmp, hiw);
        Big powk; big_clear(powk); big_setbit(powk, k-1);
        big_add(tmp, powk, sumB, hiw);

        int c = big_cmp(sumA, sumB, hiw);
        const Big& chosen = (c <= 0) ? sumA : sumB;

        long long ans = (big_reduce(chosen, pow2mod, hiw) + 1) % MOD;
        outbuf += to_string(ans);
        outbuf += '\n';
    }
    fwrite(outbuf.data(), 1, outbuf.size(), stdout);
    return 0;
}
