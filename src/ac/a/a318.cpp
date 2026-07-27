// ZeroJudge a318 - NOI2011 Day1.1 兔农 (rabbit farmer)
// Algorithm: Modified Fibonacci b_i=b_{i-1}+b_{i-2}; if b_i≡1 (mod k) and i>=3 then b_i-=1.
// Between "deaths" the sequence is linear (Fibonacci matrix). After a death b≡0 (mod k) and the
// previous residue c fully determines the future: next death is min j with c*Fib(j)≡1 (mod k),
// found via the Pisano-period first-occurrence table; new residue = c*Fib(j-1). The residue
// sequence has <=k states so it cycles; the per-cycle affine transform (mod p) and its position
// advance are fixed, letting us fast-forward to n<=1e18 with matrix exponentiation. No table lookup.
#include <bits/stdc++.h>
using namespace std;
using std::vector;
typedef long long ll;

namespace a318 {

ll MODP; // current p for matrix arithmetic

struct Mat2 { ll a,b,c,d; };
static inline Mat2 mul2(const Mat2&x,const Mat2&y){
    Mat2 r;
    r.a=(x.a*y.a + x.b*y.c)%MODP;
    r.b=(x.a*y.b + x.b*y.d)%MODP;
    r.c=(x.c*y.a + x.d*y.c)%MODP;
    r.d=(x.c*y.b + x.d*y.d)%MODP;
    return r;
}
static inline Mat2 idMat(){ return Mat2{1%MODP,0,0,1%MODP}; }
// F = [[1,1],[1,0]]; F^m
static Mat2 fibPow(ll m){
    Mat2 base{1%MODP,1%MODP,1%MODP,0};
    Mat2 res=idMat();
    while(m>0){ if(m&1) res=mul2(res,base); base=mul2(base,base); m>>=1; }
    return res;
}

struct Aff { Mat2 A; ll o0,o1; }; // V' = A*V + o
static inline Aff idAff(){ return Aff{idMat(),0,0}; }
// compose g after f: apply f then g
static inline Aff compose(const Aff&g,const Aff&f){
    Aff r; r.A=mul2(g.A,f.A);
    r.o0=(g.A.a*f.o0 + g.A.b*f.o1 + g.o0)%MODP;
    r.o1=(g.A.c*f.o0 + g.A.d*f.o1 + g.o1)%MODP;
    return r;
}
static Aff affPow(Aff b, ll e){
    Aff res=idAff();
    while(e>0){ if(e&1) res=compose(b,res); b=compose(b,b); e>>=1; }
    return res;
}

// extended gcd inverse of a mod m (a in [0,m)); returns -1 if not invertible
static ll invMod(ll a, ll m){
    if(m==1) return 0;
    ll g0=a,g1=m,x0=1,x1=0;
    while(g1){ ll q=g0/g1; ll t=g0-q*g1; g0=g1; g1=t; t=x0-q*x1; x0=x1; x1=t; }
    if(g0!=1) return -1;
    x0%=m; if(x0<0) x0+=m; return x0;
}
static ll gcd_ll(ll a,ll b){ while(b){ ll t=a%b; a=b; b=t; } return a; }

// Solve one query
ll solve(ll n, ll k, ll p){
    MODP=p;
    // --- build Fibonacci mod k over one Pisano period ---
    // fibArr[i] = Fib(i) mod k for i=0..P
    // firstOcc[r] = min index j in [1,P] with Fib(j)==r (mod k), else -1
    // firstIdxGE3_of1 = min index j in [3,P] with Fib(j)==1 (mod k), else -1
    ll kk=k;
    // compute Pisano period P
    ll prev=0%kk, cur=1%kk, P=0;
    do { ll nx=(prev+cur)%kk; prev=cur; cur=nx; P++; } while(!(prev==0%kk && cur==1%kk));
    // build fibArr[0..P]
    vector<int> fibArr(P+1);
    fibArr[0]=0; if(P>=1) fibArr[1]=1%kk;
    for(ll i=2;i<=P;i++) fibArr[i]=(int)((fibArr[i-1]+fibArr[i-2])%kk);
    vector<int> firstOcc(kk,-1);
    ll firstIdxGE3_of1=-1;
    for(ll j=1;j<=P;j++){
        int r=fibArr[j];
        if(firstOcc[r]==-1) firstOcc[r]=(int)j;
        if(r==(int)(1%kk) && j>=3 && firstIdxGE3_of1==-1) firstIdxGE3_of1=j;
    }
    // first death index: min index>=3 with Fib==1
    // candidate from within period, plus wrap P + firstOcc[1]
    ll cand2 = P + firstOcc[1%kk]; // firstOcc[1] always exists
    ll firstDeath;
    if(firstIdxGE3_of1!=-1) firstDeath = std::min(firstIdxGE3_of1, cand2);
    else firstDeath = cand2;
    // c0 = Fib(firstDeath-1) mod k
    ll fdm1 = firstDeath-1;
    ll c0;
    if(fdm1<=P) c0 = fibArr[fdm1];
    else c0 = fibArr[fdm1-P]; // shouldn't happen normally
    c0 %= kk;

    // --- generate death sequence with cycle detection on c-state ---
    vector<int> sVec; vector<ll> dPos; vector<ll> seg;
    vector<int> visited(kk,-1);
    sVec.push_back((int)c0); dPos.push_back(firstDeath); seg.push_back(firstDeath);
    visited[c0]=0;
    bool cyclePresent=false, finite=false;
    ll cs=-1, M=0;
    ll i=0;
    while(true){
        int c=sVec[i];
        // step(c): find gap, newc
        bool ok=false; ll gap=0, newc=0;
        if(gcd_ll(c,kk)==1){
            ll t=invMod(c,kk);
            if(t>=0 && firstOcc[t]!=-1){
                ll j=firstOcc[t];
                gap=j;
                newc=( (ll)c * fibArr[j-1] )%kk;
                ok=true;
            }
        }
        if(!ok){ finite=true; M=i; break; }
        if(visited[newc]!=-1){
            dPos.push_back(dPos[i]+gap); seg.push_back(gap); sVec.push_back((int)newc);
            cs=visited[newc]; M=i+1; cyclePresent=true; break;
        }
        dPos.push_back(dPos[i]+gap); seg.push_back(gap); sVec.push_back((int)newc);
        visited[newc]=(int)(i+1); i++;
    }

    // helper: apply operator O_m to V (V=(v0,v1)): V=F^{seg[m]}*V; v0-=1
    auto applyOp=[&](ll &v0, ll &v1, ll m){
        Mat2 Fm=fibPow(seg[m]);
        ll n0=(Fm.a*v0+Fm.b*v1)%MODP;
        ll n1=(Fm.c*v0+Fm.d*v1)%MODP;
        n0=(n0-1+MODP)%MODP;
        v0=n0; v1=n1;
    };
    auto advanceF=[&](ll &v0,ll &v1,ll steps){
        Mat2 Fm=fibPow(steps);
        ll n0=(Fm.a*v0+Fm.b*v1)%MODP;
        ll n1=(Fm.c*v0+Fm.d*v1)%MODP;
        v0=n0; v1=n1;
    };

    ll v0=0%MODP, v1=1%MODP; // start at position 0: (b0,b_{-1})=(0,1)
    ll lastPos;
    bool anyDeath;

    if(n < dPos[0]){
        anyDeath=false;
    } else {
        anyDeath=true;
        if(!cyclePresent){
            // explicit deaths 0..M
            ll hi=std::upper_bound(dPos.begin(), dPos.begin()+(M+1), n) - dPos.begin();
            ll idx=hi-1;
            lastPos=dPos[idx];
            for(ll m=0;m<=idx;m++) applyOp(v0,v1,m);
        } else {
            if(n < dPos[cs]){
                ll hi=std::upper_bound(dPos.begin(), dPos.begin()+cs, n) - dPos.begin();
                ll idx=hi-1;
                lastPos=dPos[idx];
                for(ll m=0;m<=idx;m++) applyOp(v0,v1,m);
            } else {
                ll C=M-cs;
                ll L=dPos[M]-dPos[cs];
                ll a=(n-dPos[cs])/L;
                ll base=dPos[cs]+a*L;
                // find largest r in [0,C-1] with dPos[cs+r] + a*L <= n  <=> dPos[cs+r] <= n - a*L
                ll target=n - a*L;
                ll hi=std::upper_bound(dPos.begin()+cs, dPos.begin()+M, target) - dPos.begin();
                ll r=(hi-1)-cs;
                lastPos = a*L + dPos[cs+r];
                // build V: O_0..O_cs
                for(ll m=0;m<=cs;m++) applyOp(v0,v1,m);
                if(a>0){
                    // block B = O_{cs+1} .. O_M composed
                    Aff acc=idAff();
                    ll negOne=(MODP-1)%MODP;
                    for(ll m=cs+1;m<=M;m++){
                        Aff g; g.A=fibPow(seg[m]); g.o0=negOne; g.o1=0;
                        acc=compose(g,acc);
                    }
                    Aff Ba=affPow(acc,a);
                    ll n0=(Ba.A.a*v0+Ba.A.b*v1+Ba.o0)%MODP;
                    ll n1=(Ba.A.c*v0+Ba.A.d*v1+Ba.o1)%MODP;
                    v0=n0; v1=n1;
                }
                for(ll t=1;t<=r;t++) applyOp(v0,v1,cs+t);
            }
        }
    }

    if(!anyDeath){
        // b_n = Fib(n) mod p ; advance F^n from (0,1)
        advanceF(v0,v1,n);
        return v0%MODP;
    } else {
        advanceF(v0,v1, n-lastPos);
        return v0%MODP;
    }
}

} // namespace a318

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while(getline(cin, line)){
        // strip trailing CR / whitespace
        while(!line.empty() && (line.back()=='\r' || line.back()=='\n' || line.back()==' ' || line.back()=='\t'))
            line.pop_back();
        if(line.empty()){ cout << "\n"; continue; }
        long long n,k,p;
        stringstream ss(line);
        if(!(ss>>n>>k>>p)){ cout << "\n"; continue; }
        cout << a318::solve(n,k,p) << "\n";
    }
    return 0;
}
