// c706. A = B Problem  -- self-written solution
//
// Output S pairs of distinct equal-length lowercase strings (len<=30) whose
// polynomial hash  h(s) = ((...*131 + c_i)...) mod M  collide.
//
// Idea:
//   1) Find ONE collision gadget: length-k strings X != Y with h(X)=h(Y).
//      h(X)-h(Y) = sum_e d_e * 131^e  (e=exponent from LSB, d_e = char diff).
//      Need small integer d_e (|d_e|<=25, realizable by two lowercase chars)
//      with  sum_e d_e * (131^e mod M) == 0 (mod M).  That is a short vector in
//          L = { d in Z^k : sum d_e * a_e == 0 (mod M) },  a_e = 131^e mod M,
//      basis  b0 = (M,0,..,0),  b_i = (-a_i, e_i)  (a_0 = 1 for M>1).
//      LLL yields a very short vector (norm ~ M^{1/k}, tiny for k up to 30).
//   2) Mass produce: h(X)=h(Y) => h(P+X)=h(P+Y) for any prefix P, since
//      h(P+X) = h(P)*131^k + h(X).  So A_i=P_i+X, B_i=P_i+Y over distinct P_i.
//
// The chosen vector is verified EXACTLY with integer arithmetic before use.

#include <bits/stdc++.h>
using namespace std;
using u64  = unsigned long long;
using i128 = __int128_t;
using u128 = __uint128_t;

static u64 MOD;
static inline u64 mulmod(u64 a, u64 b){ return (u64)((u128)a * b % MOD); }

static int N;
static vector<vector<i128>> B;
static long double G[35][35];
static long double mu[35][35];
static long double Bnorm[35];

static void gramSchmidt(){
    for(int i=0;i<N;i++){
        static long double bstar[35];
        for(int t=0;t<N;t++) bstar[t]=(long double)B[i][t];
        for(int j=0;j<i;j++){
            long double num=0; for(int t=0;t<N;t++) num += (long double)B[i][t]*G[j][t];
            mu[i][j] = (Bnorm[j]>0)? num/Bnorm[j] : 0;
            for(int t=0;t<N;t++) bstar[t]-= mu[i][j]*G[j][t];
        }
        long double nn=0; for(int t=0;t<N;t++){ G[i][t]=bstar[t]; nn+=bstar[t]*bstar[t]; }
        Bnorm[i]=nn;
    }
}
static void lll(){
    gramSchmidt();
    int k=1;
    while(k<N){
        for(int j=k-1;j>=0;j--){
            if(fabsl(mu[k][j])>0.5L){
                long long q=llroundl(mu[k][j]);
                if(q!=0){ for(int t=0;t<N;t++) B[k][t]-= (i128)q*B[j][t]; gramSchmidt(); }
            }
        }
        if(Bnorm[k] >= (0.75L - mu[k][k-1]*mu[k][k-1])*Bnorm[k-1]) k++;
        else { swap(B[k],B[k-1]); gramSchmidt(); k=max(k-1,1); }
    }
}

// short lattice vector d (dim k): sum d_e*(131^e mod M)==0 mod M, |d_e|<=25.
static vector<long long> findGadget(int k){
    N=k;
    vector<u64> a(k);
    a[0]=1%MOD;
    for(int e=1;e<k;e++) a[e]=mulmod(a[e-1],131%MOD);
    B.assign(k, vector<i128>(k,0));
    B[0][0]=(i128)MOD;
    for(int i=1;i<k;i++){ B[i][0]= -(i128)a[i]; B[i][i]=1; }
    lll();
    int best=-1; long long bestMax=LLONG_MAX; long double bestL2=1e300L;
    for(int i=0;i<k;i++){
        long long mx=0; bool nz=false; long double l2=0;
        for(int t=0;t<k;t++){ i128 v=B[i][t]; long long av=(long long)(v<0?-v:v); mx=max(mx,av); if(v!=0)nz=true; l2+=(long double)av*av; }
        if(!nz) continue;
        u64 acc=0;
        for(int e=0;e<k;e++){ long long d=(long long)B[i][e]; long long dm=((d%(long long)MOD)+(long long)MOD)%(long long)MOD;
            acc=(u64)(( (u128)acc + (u128)dm*a[e] )%MOD); }
        if(acc!=0) continue;
        if(mx<bestMax || (mx==bestMax && l2<bestL2)){ bestMax=mx; bestL2=l2; best=i; }
    }
    if(best<0 || bestMax>25) return {};
    vector<long long> d(k);
    for(int e=0;e<k;e++) d[e]=(long long)B[best][e];
    return d;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    u64 M; long long S;
    while(cin>>M>>S){
        MOD=M;
        int prefLen=0; { long long cap=1; while(cap<S){ cap*=26; prefLen++; } }
        if(prefLen>28) prefLen=28;
        int k=30-prefLen; if(k<2) k=2;

        vector<long long> d;
        for(int kk=k; kk>=8 && d.empty(); kk--){
            if(30-kk < prefLen) break;
            d=findGadget(kk);
            if(!d.empty()){ break; }
        }
        if(d.empty()){
            for(int kk=30; kk>=8 && d.empty(); kk--) d=findGadget(kk);
        }
        k=(int)d.size();
        // If prefix room shrank because gadget grew, recompute prefLen (still >=needed for S)
        prefLen=30-k;

        string X(k,'a'), Y(k,'a');
        for(int e=0;e<k;e++){
            long long v=d[e];
            int xoff=0,yoff=0;
            if(v>=0) xoff=(int)v; else yoff=(int)(-v);
            X[k-1-e]=(char)('a'+xoff);
            Y[k-1-e]=(char)('a'+yoff);
        }

        string out; out.reserve((size_t)S*(2*k+2*prefLen+2));
        for(long long i=0;i<S;i++){
            string pref(prefLen,'a');
            long long x=i;
            for(int t=prefLen-1;t>=0;t--){ pref[t]=(char)('a'+(int)(x%26)); x/=26; }
            out += pref; out += X; out += ' '; out += pref; out += Y; out += '\n';
        }
        cout<<out;
    }
    return 0;
}
