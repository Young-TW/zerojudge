#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

const ll MOD = 1000000007LL;

ll pw(ll a, ll b, ll m){ a%=m; if(a<0)a+=m; ll r=1; while(b>0){ if(b&1) r=(lll)r*a%m; a=(lll)a*a%m; b>>=1;} return r; }
ll inv(ll a, ll m){ return pw(a, m-2, m); }

// ---- NTT ----
struct NTT {
    ll mod, root;
    NTT(ll m, ll g):mod(m),root(g){}
    ll pwm(ll a, ll b){ a%=mod; if(a<0)a+=mod; ll r=1; while(b>0){ if(b&1) r=(lll)r*a%mod; a=(lll)a*a%mod; b>>=1;} return r; }
    void ntt(vector<ll>&a, bool inv_){
        int n=a.size();
        for(int i=1,j=0;i<n;i++){ int bit=n>>1; for(;j&bit;bit>>=1) j^=bit; j^=bit; if(i<j) swap(a[i],a[j]); }
        for(int len=2;len<=n;len<<=1){
            ll w = pwm(root, (mod-1)/len);
            if(inv_) w = pwm(w, mod-2);
            for(int i=0;i<n;i+=len){
                ll wn=1;
                for(int k=0;k<len/2;k++){
                    ll u=a[i+k], v=(lll)a[i+k+len/2]*wn%mod;
                    a[i+k]=(u+v)%mod; a[i+k+len/2]=(u-v+mod)%mod;
                    wn=(lll)wn*w%mod;
                }
            }
        }
        if(inv_){ ll ninv=pwm(n,mod-2); for(auto&x:a) x=(lll)x*ninv%mod; }
    }
    vector<ll> mul(vector<ll> a, vector<ll> b, int need){
        int sz=1; while(sz < (int)(a.size()+b.size())) sz<<=1;
        a.resize(sz); b.resize(sz);
        ntt(a,false); ntt(b,false);
        for(int i=0;i<sz;i++) a[i]=(lll)a[i]*b[i]%mod;
        ntt(a,true);
        a.resize(need);
        return a;
    }
};

// CRT combine 3 residues -> value mod MOD
const ll M1=998244353, M2=469762049, M3=167772161;

// compute stirling row S(c, j) for j=0..c, mod MOD. Using arbitrary-mod NTT.
vector<ll> stirling_row_ntt(ll c){
    int C=(int)c;
    // factorials
    vector<ll> fact(C+1), ifact(C+1);
    fact[0]=1; for(int i=1;i<=C;i++) fact[i]=(lll)fact[i-1]*i%MOD;
    ifact[C]=inv(fact[C],MOD); for(int i=C;i>0;i--) ifact[i-1]=(lll)ifact[i]*i%MOD;
    vector<ll> A(C+1), B(C+1);
    for(int k=0;k<=C;k++){
        A[k]= (k&1)? (MOD - ifact[k])%MOD : ifact[k];
        B[k]= (lll)pw(k, c, MOD)*ifact[k]%MOD; // 0^c=0 for c>=1
    }
    int need=C+1; // we need indices 0..C
    NTT n1(M1,3), n2(M2,3), n3(M3,3);
    // reduce A,B mod each prime
    auto redA1=A, redB1=B, redA2=A, redB2=B, redA3=A, redB3=B;
    for(int i=0;i<=C;i++){ redA1[i]%=M1; redB1[i]%=M1; redA2[i]%=M2; redB2[i]%=M2; redA3[i]%=M3; redB3[i]%=M3; }
    vector<ll> r1=n1.mul(redA1,redB1,need);
    vector<ll> r2=n2.mul(redA2,redB2,need);
    vector<ll> r3=n3.mul(redA3,redB3,need);
    // CRT
    ll inv12 = inv(M1 % M2, M2);
    ll M12mod3 = (lll)(M1%M3)*(M2%M3)%M3;
    ll invM12_3 = inv(M12mod3, M3);
    ll M1M2 = M1*M2; // ~4.69e17 fits int64
    vector<ll> res(need);
    for(int i=0;i<need;i++){
        ll a1=r1[i]%M1, a2=r2[i]%M2, a3=r3[i]%M3;
        // x12 = a1 + M1 * (((a2-a1)*inv12) mod M2)
        ll t = ( (a2 - a1%M2) % M2 + M2 ) % M2;
        t = (lll)t*inv12 % M2;
        ll x12 = a1 + M1 * t; // < M1*M2
        // x = x12 + M1M2 * (((a3 - x12) * invM12_3) mod M3)
        ll x12mod3 = x12 % M3;
        ll u = ( (a3 - x12mod3) % M3 + M3 ) % M3;
        u = (lll)u*invM12_3 % M3;
        lll x = (lll)x12 + (lll)M1M2 * u;
        res[i] = (ll)(x % MOD);
    }
    return res;
}

vector<ll> stirling_row_small(ll c){
    int C=(int)c;
    vector<ll> cur(C+1,0), prev(C+1,0);
    prev[0]=1; // S(0,0)=1
    for(int t=1;t<=C;t++){
        fill(cur.begin(),cur.end(),0);
        for(int j=1;j<=t;j++){
            cur[j]=(prev[j-1] + (lll)j*prev[j]%MOD)%MOD;
        }
        swap(prev,cur);
    }
    return prev; // S(c, j)
}

int main(){
    string nstr; ll c;
    if(!(cin>>nstr>>c)) return 0;

    // parse n mod MOD and mod MOD-1, and decide small/large
    ll nmod=0, npm1=0; // mod MOD, mod MOD-1
    for(char ch: nstr){ int d=ch-'0'; nmod=(nmod*10+d)%MOD; npm1=(npm1*10+d)%(MOD-1); }

    // determine if n is small (<= threshold) as exact integer
    const ll THRESH = 2000000;
    bool small=false; ll nsmall=0;
    if(nstr.size()<=7){
        ll v=0; for(char ch:nstr) v=v*10+(ch-'0');
        if(v<=THRESH){ small=true; nsmall=v; }
    }

    ll ans=0;
    if(small){
        // ans = sum_{i=1}^{n} i^c * C(n,i)
        ll n=nsmall;
        // precompute inverses 1..n
        vector<ll> invv(n+1);
        if(n>=1) invv[1]=1;
        for(int i=2;i<=n;i++) invv[i]=(lll)(MOD-MOD/i)*invv[MOD%i]%MOD;
        ll comb=1; // C(n,0)
        for(ll i=1;i<=n;i++){
            // C(n,i)=C(n,i-1)*(n-i+1)/i
            comb=(lll)comb*((n-i+1)%MOD)%MOD;
            comb=(lll)comb*invv[i]%MOD;
            ll term=(lll)pw(i,c,MOD)*comb%MOD;
            ans=(ans+term)%MOD;
        }
    } else {
        // large n: Stirling. c <= 1e5 guaranteed by constraints.
        vector<ll> S;
        if(c<=2000) S=stirling_row_small(c);
        else S=stirling_row_ntt(c);
        // falling factorial ff[j] = n(n-1)...(n-j+1) mod MOD
        // term2[j] = 2^{n-j} mod MOD, computed incrementally from 2^n
        ll pow2n = pw(2, npm1, MOD); // 2^n mod MOD
        ll i2 = inv(2, MOD);
        ll ff=1; // ff[0]
        ll t2=pow2n; // will become 2^{n-j}
        int C=(int)c;
        for(int j=1;j<=C;j++){
            ff=(lll)ff*(((nmod - (j-1))%MOD + MOD)%MOD)%MOD; // ff[j]
            t2=(lll)t2*i2%MOD; // 2^{n-j}
            ll term=(lll)S[j]%MOD;
            term=(lll)term*ff%MOD;
            term=(lll)term*t2%MOD;
            ans=(ans+term)%MOD;
        }
    }
    cout<<ans%MOD<<"\n";
    return 0;
}
