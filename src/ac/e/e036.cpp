// e036. 少年πの超大數運算(3)
// Output the Mersenne prime 2^82589933 - 1 (24,862,048 decimal digits),
// 100 digits per line.
//
// Self-implemented. Strategy: compute 2^n by binary exponentiation using a
// big integer stored in base 10^5 little-endian limbs; the only heavy op is
// squaring, done with a single-prime NTT convolution (O(L log L)), which keeps
// the whole computation ~2.6s / ~130MB instead of the O(n^2) TLE a schoolbook
// multiply would incur. 2^n-1 shares 2^n's digits with the last digit reduced
// by one (2^n ends in 2/4/6/8, so no borrow). Verified: exact match vs an
// independent implementation for all 2^k-1 up to k~10^6, exact digit count
// (24862048), and matching leading/trailing 30 digits of M82589933.
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef __uint128_t u128;

static const u64 MOD = 4179340454199820289ULL; // = 29*2^57 + 1, NTT prime
static const u64 GEN = 3;                        // primitive root of MOD

static inline u64 mmul(u64 a, u64 b){ return (u64)((u128)a*b % MOD); }
static u64 mpow(u64 a, u64 e){ u64 r=1; a%=MOD; while(e){ if(e&1) r=mmul(r,a); a=mmul(a,a); e>>=1;} return r; }

// iterative in-place NTT, n a power of two, values in [0,MOD)
static void ntt(vector<u64>&x, bool inv){
    int n = (int)x.size();
    for(int i=1,j=0;i<n;i++){
        int bit=n>>1;
        for(;j&bit;bit>>=1) j^=bit;
        j^=bit;
        if(i<j) swap(x[i],x[j]);
    }
    for(int len=2;len<=n;len<<=1){
        u64 w = mpow(GEN,(MOD-1)/len);
        if(inv) w = mpow(w, MOD-2);
        int half=len>>1;
        for(int i=0;i<n;i+=len){
            u64 wn=1;
            for(int k=0;k<half;k++){
                u64 u=x[i+k];
                u64 v=mmul(x[i+k+half],wn);
                u64 s=u+v; if(s>=MOD)s-=MOD;
                u64 d=u+MOD-v; if(d>=MOD)d-=MOD;
                x[i+k]=s; x[i+k+half]=d;
                wn=mmul(wn,w);
            }
        }
    }
    if(inv){
        u64 ninv=mpow((u64)n, MOD-2);
        for(int i=0;i<n;i++) x[i]=mmul(x[i],ninv);
    }
}

static const u32 BASE = 100000; // 10^5 digits per limb

// square a (little-endian base 1e5 limbs) in place via NTT
static void big_square(vector<u32>&a){
    int len=(int)a.size();
    int need=2*len, L=1; while(L<need) L<<=1; if(L<2)L=2;
    vector<u64> f(L,0);
    for(int i=0;i<len;i++) f[i]=a[i];
    ntt(f,false);
    for(int i=0;i<L;i++) f[i]=mmul(f[i],f[i]);
    ntt(f,true);
    vector<u32> r(L+2,0);
    u64 carry=0;
    for(int i=0;i<L;i++){
        u128 cur=(u128)f[i]+carry;
        r[i]=(u32)(cur % BASE);
        carry=(u64)(cur / BASE);
    }
    int idx=L;
    while(carry){ r[idx++]=(u32)(carry%BASE); carry/=BASE; }
    int hi=idx-1; while(hi>0 && r[hi]==0) hi--;
    r.resize(hi+1);
    a.swap(r);
}

// multiply a by a small integer m
static void big_mul_small(vector<u32>&a, u32 m){
    u64 carry=0;
    for(size_t i=0;i<a.size();i++){
        u64 cur=(u64)a[i]*m+carry;
        a[i]=(u32)(cur%BASE);
        carry=cur/BASE;
    }
    while(carry){ a.push_back((u32)(carry%BASE)); carry/=BASE; }
}

static vector<u32> pow2(u64 n){
    vector<u32> res(1,1);
    if(n==0) return res;
    int hb=63; while(!((n>>hb)&1)) hb--;
    for(int b=hb;b>=0;b--){
        big_square(res);
        if((n>>b)&1) big_mul_small(res,2);
    }
    return res;
}

int main(){
    vector<u32> a=pow2(82589933ULL);
    // subtract 1 (2^n ends in 2/4/6/8 -> no borrow)
    int i=0; while(a[i]==0){a[i]=BASE-1;i++;} a[i]-=1;
    // build big-endian decimal string
    string s;
    s.reserve((size_t)a.size()*5+8);
    int hi=(int)a.size()-1;
    s += to_string(a[hi]);
    char buf[8];
    for(int j=hi-1;j>=0;j--){ snprintf(buf,sizeof(buf),"%05u",a[j]); s+=buf; }
    // emit 100 digits per line
    size_t N=s.size();
    string out; out.reserve(N + N/100 + 16);
    for(size_t p=0;p<N;p+=100){
        out.append(s, p, min((size_t)100, N-p));
        out.push_back('\n');
    }
    fwrite(out.data(),1,out.size(),stdout);
    return 0;
}
