#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

ll extgcd(ll a, ll b, ll &x, ll &y){
    if(!b){ x=1; y=0; return a; }
    ll x1,y1; ll g=extgcd(b,a%b,x1,y1);
    x=y1; y=x1-(a/b)*y1; return g;
}

// smallest non-negative x with a*x ≡ b (mod m), or -1 if no solution
ll solve(ll a, ll b, ll m){
    a=((a%m)+m)%m; b=((b%m)+m)%m;
    ll x,y;
    ll g=extgcd(a,m,x,y);
    if(b%g!=0) return -1;
    ll m2=m/g;
    ll t0=(( (b/g)%m2 ) * ((x%m2+m2)%m2)) % m2;
    return t0;
}

int main(){
    int n;
    while(cin>>n){
        vector<ll> C(n),P(n),L(n);
        ll maxC=0;
        for(int i=0;i<n;i++){ cin>>C[i]>>P[i]>>L[i]; if(C[i]>maxC) maxC=C[i]; }
        for(ll M=maxC;;M++){
            bool ok=true;
            for(int i=0;i<n&&ok;i++)
                for(int j=i+1;j<n&&ok;j++){
                    ll lim=min(L[i],L[j]);
                    ll t=solve(P[i]-P[j], C[j]-C[i], M);
                    if(t!=-1 && t<=lim){ ok=false; }
                }
            if(ok){ cout<<M<<"\n"; break; }
        }
    }
    return 0;
}
