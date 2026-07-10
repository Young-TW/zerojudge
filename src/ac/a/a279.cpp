#include <cstdio>
#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;
typedef long long ll;

ll modpow(ll base, ll exp, ll mod){
    ll r=1%mod; base%=mod; if(base<0)base+=mod;
    while(exp>0){ if(exp&1) r=(__int128)r*base%mod; base=(__int128)base*base%mod; exp>>=1;}
    return r;
}
ll gcd(ll a, ll b){ while(b){ a%=b; swap(a,b);} return a; }
void extgcd(ll a, ll b, ll &x, ll &y){
    if(b==0){ x=1; y=0; return; }
    ll x1,y1; extgcd(b,a%b,x1,y1);
    x=y1; y=x1-(a/b)*y1;
}
ll modinv(ll a, ll m){
    ll x,y; extgcd(((a%m)+m)%m, m, x, y);
    return ((x%m)+m)%m;
}
void factorize(ll n, vector<ll>&pr){
    for(ll p=2;p*p<=n;p++){ if(n%p==0){ pr.push_back(p); while(n%p==0)n/=p; } }
    if(n>1) pr.push_back(n);
}
ll phi(ll n){
    ll res=n;
    for(ll p=2;p*p<=n;p++){ if(n%p==0){ while(n%p==0)n/=p; res-=res/p; } }
    if(n>1) res-=res/n;
    return res;
}
ll ord_m(ll a, ll m){
    ll p=phi(m);
    vector<ll> pr; factorize(p, pr);
    ll ord=p;
    for(ll q:pr){ while(ord%q==0 && modpow(a, ord/q, m)==1) ord/=q; }
    return ord;
}
// smallest t in [0,ord) with 2^t == B mod m, or -1
ll dlog(ll B, ll m, ll ord){
    if(ord==0) return -1;
    ll n=(ll)ceil(sqrt((double)ord)); if(n<1)n=1;
    unordered_map<ll,ll> table; table.reserve(n*2+4);
    ll cur=1%m;
    for(ll j=0;j<n;j++){ if(!table.count(cur)) table[cur]=j; cur=(__int128)cur*2%m; }
    ll invn=modinv(modpow(2,n,m),m);
    ll c=((B%m)+m)%m;
    for(ll i=0;i<n;i++){
        auto it=table.find(c);
        if(it!=table.end()){ ll t=i*n+it->second; if(t<ord) return t; }
        c=(__int128)c*invn%m;
    }
    return -1;
}
int main(){
    ll n,m,e;
    while(scanf("%lld %lld %lld",&n,&m,&e)==3){
        if(m==1){ printf("0\n"); continue; }
        if(n%m==0){ printf("0\n"); continue; }
        if(m%2==0){ printf("-1\n"); continue; }
        ll A=((n+1)%m+m)%m;
        if(gcd(A,m)!=1){ printf("-1\n"); continue; }
        ll B=modinv(A,m);
        ll ord=ord_m(2,m);
        ll t0=dlog(B,m,ord);
        if(t0<0){ printf("-1\n"); continue; }
        ll tstar;
        if(t0==1) tstar=t0+ord;
        else tstar=t0;
        ll k=(tstar+2)/3;
        if(k<=e) printf("%lld\n",k);
        else printf("-1\n");
    }
    return 0;
}
