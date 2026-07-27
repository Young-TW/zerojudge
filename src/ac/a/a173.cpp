#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = (ll)1e18;

int N, n;
vector<vector<int>> pre; // prefix sums per row: pre[i][r] = sum F[i][0..r-1]
vector<int> init_, C;
vector<ll> feeA, feeB;

inline int rowsum(int i, int l, int r){ return pre[i][r]-pre[i][l]; }

vector<ll> solve(int lo, int sz){
    if(sz==1){
        int leaf=lo;
        vector<ll> r(2);
        r[0]=(init_[leaf]==1? (ll)C[leaf]:0)+feeA[leaf]; // choose A (0 B's)
        r[1]=(init_[leaf]==0? (ll)C[leaf]:0)+feeB[leaf]; // choose B (1 B)
        return r;
    }
    int h=sz/2, mid=lo+h, hi=lo+sz;
    vector<ll> res(sz+1, INF);
    // maj(free)=A  <=>  nA>=nB  <=>  totalB <= sz/2 ; charged side = B => feeB += w
    for(int i=lo;i<mid;i++) feeB[i]+=rowsum(i,mid,hi);
    for(int i=mid;i<hi;i++) feeB[i]+=rowsum(i,lo,mid);
    {
        vector<ll> L=solve(lo,h), R=solve(mid,h);
        int lim=sz/2;
        for(int a=0;a<=h;a++){ if(a>lim) break; ll la=L[a];
            for(int b=0;b<=h && a+b<=lim;b++){ ll v=la+R[b]; if(v<res[a+b]) res[a+b]=v; } }
    }
    for(int i=lo;i<mid;i++) feeB[i]-=rowsum(i,mid,hi);
    for(int i=mid;i<hi;i++) feeB[i]-=rowsum(i,lo,mid);
    // maj(free)=B  <=>  nA<nB  <=>  totalB >= sz/2+1 ; charged side = A => feeA += w
    for(int i=lo;i<mid;i++) feeA[i]+=rowsum(i,mid,hi);
    for(int i=mid;i<hi;i++) feeA[i]+=rowsum(i,lo,mid);
    {
        vector<ll> L=solve(lo,h), R=solve(mid,h);
        int lo2=sz/2+1;
        for(int a=0;a<=h;a++){ ll la=L[a];
            for(int b=0;b<=h;b++){ if(a+b<lo2) continue; ll v=la+R[b]; if(v<res[a+b]) res[a+b]=v; } }
    }
    for(int i=lo;i<mid;i++) feeA[i]-=rowsum(i,mid,hi);
    for(int i=mid;i<hi;i++) feeA[i]-=rowsum(i,lo,mid);
    return res;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    if(!(cin>>N)) return 0;
    n=1<<N;
    init_.assign(n,0); C.assign(n,0);
    for(int i=0;i<n;i++) cin>>init_[i];
    for(int i=0;i<n;i++) cin>>C[i];
    vector<vector<int>> F(n, vector<int>(n,0));
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){ int x; cin>>x; F[i][j]=x; F[j][i]=x; }
    }
    pre.assign(n, vector<int>(n+1,0));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) pre[i][j+1]=pre[i][j]+F[i][j];
    feeA.assign(n,0); feeB.assign(n,0);
    vector<ll> r=solve(0,n);
    ll ans=INF; for(ll v:r) ans=min(ans,v);
    cout<<ans<<"\n";
    return 0;
}
