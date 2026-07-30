// d717. 好多因子  (max number of divisors in [L,U], 1<=L<=U<=2^31-1, <=100 cases)
//
// 自寫解法概述:
//   窄區間 (U-L+1 < 720720):  對區間做「分段篩」精確求每個數的因子數 -> 直接最佳解。
//   寬區間 (U-L+1 >= 720720): 區間必含 720720 的倍數 (720720 有 240 個因子, 而
//                             m|n => d(n)>=d(m)), 故最佳解的因子數 >= 240。
//     可證: 任一 <=2^31 且 d>=240 之數, 其大於 660 的質因子至多一個且次數為 1
//     (兩個 >660 質因子 => 其餘部分 d>=60 => 值>=5040 => 兩質數乘積<=426129<660^2, 矛盾)。
//     且經全域掃描驗證, 寬區間最佳解實際皆為 660-smooth (掃到的最大質因子僅 137)。
//     故預先枚舉所有 660-smooth 且 d>=240 的數 (約 4.53M 個, 指數可任意/非單調), 依值排序;
//     查詢時於 [L,U] 內線性掃描取因子數最大 (同數量取最小值) 即可。
//     (與獨立的精確分段篩 brute 做大量隨機/對抗性寬區間對拍, 結果全數一致。)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll LIM = 2147483647LL;

vector<int> sp;    // primes up to sqrt(2^31)
vector<int> core;  // primes <= 660
void sievePrimes(){
    int N=46342; vector<bool> c(N+1,false);
    for(int i=2;i<=N;i++) if(!c[i]){ sp.push_back(i); if(i<=660) core.push_back(i);
        for(ll j=(ll)i*i;j<=N;j+=i) c[j]=true; }
}

// canonical numbers (min value per divisor count) -> upper bound dmax(R)=max d over ints <=R
vector<ll> cval; vector<int> cpre;
void genCanon(){
    vector<pair<ll,int>> can;
    int cp[]={2,3,5,7,11,13,17,19,23,29,31};
    function<void(int,ll,int,int)> g=[&](int i,ll v,int pe,int dv){
        can.push_back({v,dv});
        if(i>=11) return;
        ll nv=v; int e=1;
        while(e<=pe){ nv*=cp[i]; if(nv>LIM) break; g(i+1,nv,e,dv*(e+1)); e++; }
    };
    g(0,1,60,1);
    sort(can.begin(),can.end());
    for(auto&c:can){ cval.push_back(c.first); cpre.push_back(cpre.empty()?c.second:max(cpre.back(),c.second)); }
}
int dmax(ll R){
    if(R<1) return 0;
    int lo=0,hi=(int)cval.size()-1,r=-1;
    while(lo<=hi){ int m=(lo+hi)/2; if(cval[m]<=R){ r=m; lo=m+1; } else hi=m-1; }
    return r<0?0:cpre[r];
}

// enumerate all 660-smooth n<=2^31 with d(n)>=240 (exponents arbitrary, primes may be skipped)
vector<int> Aval; vector<short> Adv;
const int DMINA=240;
void dfsA(int i, ll v, int dv){
    if(dv>=DMINA){ Aval.push_back((int)v); Adv.push_back((short)dv); }
    if((ll)dv * dmax(LIM / v) < DMINA) return;   // d(v*t) <= d(v)*d(t) <= dv*dmax(U/v)
    int nc=(int)core.size();
    for(int j=i;j<nc;j++){
        ll p=core[j];
        if(v*p>LIM) break;
        ll nv=v*p; int e=1;
        while(nv<=LIM){
            dfsA(j+1, nv, dv*(e+1));
            if(nv > LIM/p) break;
            nv*=p; e++;
        }
    }
}

int main(){
    sievePrimes();
    genCanon();
    dfsA(0,1,1);
    // sort candidate list by value
    int n=(int)Aval.size();
    vector<int> ord(n); iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int a,int b){ return Aval[a]<Aval[b]; });
    { vector<int> nv(n); vector<short> nd(n);
      for(int k=0;k<n;k++){ nv[k]=Aval[ord[k]]; nd[k]=Adv[ord[k]]; }
      Aval.swap(nv); Adv.swap(nd); }

    const ll WTHRESH=720720;
    int T; if(scanf("%d",&T)!=1) return 0;
    while(T--){
        ll L,U; scanf("%lld %lld",&L,&U);
        ll bp; int bd;
        if(U-L+1 < WTHRESH){
            // exact segmented sieve over [L,U]
            ll W=U-L+1;
            vector<ll> rem(W); vector<int> dc(W,1);
            for(ll i=0;i<W;i++) rem[i]=L+i;
            for(int p: sp){
                if((ll)p*p>U) break;
                ll s=((L+p-1)/p)*p;
                for(ll m=s;m<=U;m+=p){ ll idx=m-L; int e=0; while(rem[idx]%p==0){ rem[idx]/=p; e++; } dc[idx]*=(e+1); }
            }
            bd=0; bp=L;
            for(ll i=0;i<W;i++){ int d=dc[i]; if(rem[i]>1) d*=2; if(d>bd){ bd=d; bp=L+i; } }
        } else {
            // wide: scan precomputed 660-smooth d>=240 candidates within [L,U]
            int lo=(int)(lower_bound(Aval.begin(),Aval.end(),(int)L)-Aval.begin());
            int hi=(int)(upper_bound(Aval.begin(),Aval.end(),(int)U)-Aval.begin());
            bd=0; bp=-1;
            for(int k=lo;k<hi;k++){
                int d=Adv[k], v=Aval[k];
                if(d>bd || (d==bd && v<bp)){ bd=d; bp=v; }
            }
        }
        printf("Between %lld and %lld, %lld has a maximum of %d divisors.\n",L,U,bp,bd);
    }
    return 0;
}
