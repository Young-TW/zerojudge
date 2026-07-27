#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=65521;
ll pw(ll a,ll b){a%=MOD;if(a<0)a+=MOD;ll r=1;while(b){if(b&1)r=r*a%MOD;a=a*a%MOD;b>>=1;}return r;}
ll inv(ll a){return pw(a,MOD-2);}

ll countT(int k,int n){
    if(n==1)return 1%MOD;
    int s=n-1;
    vector<vector<ll>> M(s, vector<ll>(s,0));
    for(int i=1;i<=s;i++){
        int deg=0;
        for(int j=1;j<=n;j++) if(j!=i && abs(j-i)<=k) deg++;
        M[i-1][i-1]=deg%MOD;
    }
    for(int i=1;i<=s;i++)for(int j=1;j<=s;j++) if(i!=j && abs(i-j)<=k) M[i-1][j-1]=MOD-1;
    ll det=1;
    for(int c=0;c<s;c++){
        int piv=-1;
        for(int r=c;r<s;r++) if(M[r][c]!=0){piv=r;break;}
        if(piv<0) return 0;
        if(piv!=c){swap(M[piv],M[c]);det=(MOD-det)%MOD;}
        det=det*M[c][c]%MOD;
        ll iv=inv(M[c][c]);
        for(int r=c+1;r<s;r++){
            if(M[r][c]==0)continue;
            ll f=M[r][c]*iv%MOD;
            for(int cc=c;cc<s;cc++){ M[r][cc]=(M[r][cc]-f*M[c][cc])%MOD; if(M[r][cc]<0)M[r][cc]+=MOD;}
        }
    }
    det%=MOD; if(det<0)det+=MOD;
    return det;
}

vector<ll> BM(vector<ll> s){
    vector<ll> ls,cur; ll ld=0; int lf=0;
    for(int i=0;i<(int)s.size();i++){
        ll t=0; for(int j=0;j<(int)cur.size();j++) t=(t+cur[j]*s[i-1-j])%MOD;
        ll d=((s[i]-t)%MOD+MOD)%MOD;
        if(d==0) continue;
        if(cur.empty()){cur.resize(i+1); lf=i; ld=d; continue;}
        ll coef=d*inv(ld)%MOD;
        vector<ll> c(i-lf-1); c.push_back(coef);
        for(ll x:ls) c.push_back((MOD-x*coef%MOD)%MOD);
        if(c.size()<cur.size())c.resize(cur.size());
        for(int j=0;j<(int)cur.size();j++) c[j]=(c[j]+cur[j])%MOD;
        if(i-(int)cur.size() >= lf-(int)ls.size()){ls=cur;lf=i;ld=d;}
        cur=c;
    }
    for(auto&x:cur){x%=MOD;if(x<0)x+=MOD;}
    return cur;
}

// Kitamasa: given rec (t[i]=sum rec[j]*t[i-1-j]) and initial seq, compute seq[idx]
ll kitamasa(vector<ll>& rec, vector<ll>& init, ll idx){
    int L=rec.size();
    if(idx < (ll)init.size()) return init[idx];
    // characteristic poly modulus: x^L - rec[0]x^{L-1}-...-rec[L-1]
    // reduce mod: we keep vector of length L (poly of deg<L)
    auto mulmod=[&](vector<ll> a, vector<ll> b)->vector<ll>{
        vector<ll> res(a.size()+b.size()-1,0);
        for(int i=0;i<(int)a.size();i++) if(a[i]) for(int j=0;j<(int)b.size();j++) res[i+j]=(res[i+j]+a[i]*b[j])%MOD;
        // reduce from high degree down to L using recurrence: x^L = sum rec[j] x^{L-1-j}
        for(int d=res.size()-1; d>=L; d--){
            ll c=res[d]; if(c){ res[d]=0; for(int j=0;j<L;j++) res[d-1-j]=(res[d-1-j]+c*rec[j])%MOD; }
        }
        res.resize(L);
        return res;
    };
    vector<ll> result(L,0); result[0]=1; // = x^0
    vector<ll> base(L,0);
    if(L>=2) base[1]=1; else { base[0]=rec.empty()?0:rec[0]; } // x mod C
    ll e=idx;
    while(e){
        if(e&1) result=mulmod(result,base);
        base=mulmod(base,base);
        e>>=1;
    }
    ll ans=0;
    for(int i=0;i<L;i++) ans=(ans+result[i]*init[i])%MOD;
    return ans%MOD;
}

int main(){
    ll k,n;
    if(!(cin>>k>>n)) return 0;
    int M=150;
    vector<ll> seq;
    for(int nn=1;nn<=M;nn++) seq.push_back(countT((int)k,nn));
    ll idx=n-1; // seq index (0-based) for n nodes
    if(idx < M){ cout<<((seq[idx]%MOD)+MOD)%MOD<<"\n"; return 0; }
    vector<ll> rec=BM(seq);
    ll ans=kitamasa(rec, seq, idx);
    cout<<((ans%MOD)+MOD)%MOD<<"\n";
    return 0;
}
