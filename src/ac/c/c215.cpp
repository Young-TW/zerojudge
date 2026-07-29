#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// c215 kevin 愛反轉
// S(n) = sum_{x=1..n} popcount(x + reverse(x)); reverse = reverse of x's binary
// using x's natural bit length. n up to 1e15.
//
// For a fixed bit length L, reverse pairs bit i with bit L-1-i, so column sums
// c_i = b_i + b_{L-1-i} form a palindrome. x+reverse(x) is added with a two-carry
// DP over symmetric position pairs (outer -> inner): lo_carry flows LSB->MSB on
// the low half; the high-half carry flows MSB->LSB (guessed then matched at the
// centre). Full-length blocks and the partial top block (x in [2^{L-1}, n],
// expanded by the position where x first drops below n) use the same per-config
// DP. Verified against brute force for all n up to 30000.

int pc(ll x){ int c=0; while(x){c+=x&1;x>>=1;} return c;}
ll rev(ll x){ int L=0; ll t=x; while(t){L++;t>>=1;} ll r=0; for(int i=0;i<L;i++) if(x>>i&1) r|=1LL<<(L-1-i); return r;}

struct St{ ll ways, pop; };

// mode[i]: 0 fixed0, 1 fixed1, 2 free.  L>=2. returns sum of popcount over config.
ll DPconfig(int L, const vector<int>& mode){
    bool even = (L%2==0);
    int P = even ? L/2 : (L-1)/2;
    int mid = even ? -1 : (L-1)/2;
    auto pairVals=[&](int lp,int hp){
        int lo0=(mode[lp]==2)?-1:mode[lp];
        int hi0=(mode[hp]==2)?-1:mode[hp];
        ll cnt[3]={0,0,0};
        for(int bl=0;bl<2;bl++){ if(lo0!=-1&&bl!=lo0) continue;
          for(int bh=0;bh<2;bh++){ if(hi0!=-1&&bh!=hi0) continue; cnt[bl+bh]++; } }
        vector<pair<int,ll>> res;
        for(int v=0;v<3;v++) if(cnt[v]) res.push_back({v,cnt[v]});
        return res;
    };
    St dp[2][2];
    for(int a=0;a<2;a++)for(int b=0;b<2;b++) dp[a][b]={0,0};
    // pair 0 : positions 0 (low) and L-1 (high). hi_out here = final top carry[L].
    for(auto&pr:pairVals(0,L-1)){ int v=pr.first; ll cnt=pr.second;
        for(int hi_in=0;hi_in<2;hi_in++){
            int s_lo=v, out_lo=s_lo&1, lo_out=s_lo>>1;
            int s_hi=v+hi_in, out_hi=s_hi&1, hi_out=s_hi>>1;
            int bits=out_lo+out_hi+hi_out;
            dp[lo_out][hi_in].ways+=cnt;
            dp[lo_out][hi_in].pop +=cnt*bits;
        }
    }
    for(int p=1;p<P;p++){
        St nd[2][2];
        for(int a=0;a<2;a++)for(int b=0;b<2;b++) nd[a][b]={0,0};
        auto pv=pairVals(p,L-1-p);
        for(int lo=0;lo<2;lo++)for(int req=0;req<2;req++){
            St cur=dp[lo][req]; if(cur.ways==0) continue;
            for(auto&pr:pv){int v=pr.first; ll cnt=pr.second;
              for(int hi_in=0;hi_in<2;hi_in++){
                int s_lo=v+lo, out_lo=s_lo&1, lo_out=s_lo>>1;
                int s_hi=v+hi_in, out_hi=s_hi&1, hi_out=s_hi>>1;
                if(hi_out!=req) continue;
                int bits=out_lo+out_hi;
                nd[lo_out][hi_in].ways+=cur.ways*cnt;
                nd[lo_out][hi_in].pop +=cur.pop*cnt+cur.ways*cnt*bits;
              }
            }
        }
        for(int a=0;a<2;a++)for(int b=0;b<2;b++) dp[a][b]=nd[a][b];
    }
    ll ans=0;
    if(even){
        for(int a=0;a<2;a++) ans+=dp[a][a].pop; // closure hi_in==lo_out
    } else {
        int bm0=(mode[mid]==2)?-1:mode[mid];
        for(int lo=0;lo<2;lo++)for(int req=0;req<2;req++){
            St cur=dp[lo][req]; if(cur.ways==0) continue;
            for(int bm=0;bm<2;bm++){ if(bm0!=-1&&bm!=bm0) continue;
                int s=2*bm+lo, out=s&1, cout=s>>1;
                if(cout!=req) continue;
                ans+=cur.pop+cur.ways*out;
            }
        }
    }
    return ans;
}

ll fullblock(int L){
    if(L==1) return 1;
    vector<int> mode(L,2); mode[L-1]=1;
    return DPconfig(L,mode);
}

ll fastS(ll n){
    if(n<=0) return 0;
    int L=0; { ll t=n; while(t){L++;t>>=1;} }
    ll total=0;
    for(int l=1;l<L;l++) total+=fullblock(l);
    if(L==1){ total+=1; return total; } // n==1
    total += pc(n+rev(n)); // x=n
    for(int k=0;k<=L-2;k++){
        if(!((n>>k)&1)) continue;
        vector<int> mode(L,2);
        for(int j=k+1;j<L;j++) mode[j]=((n>>j)&1)?1:0;
        mode[k]=0;
        total += DPconfig(L,mode);
    }
    return total;
}

int main(){
    ll n;
    while(scanf("%lld",&n)==1) printf("%lld\n", fastS(n));
    return 0;
}
