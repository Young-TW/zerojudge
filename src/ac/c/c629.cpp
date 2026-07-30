#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll P = 1000000007LL;

ll pw(ll a, ll b){ a%=P; if(a<0)a+=P; ll r=1; while(b){ if(b&1) r=r*a%P; a=a*a%P; b>>=1;} return r;}
ll inv(ll a){ return pw(((a%P)+P)%P, P-2); }
ll nm(ll x){ x%=P; if(x<0)x+=P; return x; }

ll N;              // n
ll nmod, Sk, Sk2;  // n mod P, sum k, sum k^2 over k=0..n-1
ll inv2, inv6;

ll geo(ll r){ // sum_{k=0}^{n-1} r^k
    r=nm(r);
    if(r==1) return nmod;
    return nm( (pw(r,N)-1) % P * inv(nm(r-1)) );
}
ll geoK(ll r){ // sum_{k=0}^{n-1} k*r^k
    r=nm(r);
    if(r==1) return Sk;
    // r*(1 - n*r^{n-1} + (n-1)*r^n) / (1-r)^2
    ll rn = pw(r,N), rn1 = pw(r,N-1);
    ll num = nm( 1 - nmod*rn1%P + nm(N-1)*rn%P );
    ll den = inv( nm( (1-r)*(1-r) ) );
    return nm( r * num %P * den );
}

int main(){
    // fast input
    static char buf[1<<25];
    int len = fread(buf,1,sizeof(buf),stdin);
    int pos=0;
    auto rd=[&]()->ll{
        while(pos<len && (buf[pos]<'0'||buf[pos]>'9') && buf[pos]!='-') pos++;
        bool neg=false; if(pos<len&&buf[pos]=='-'){neg=true;pos++;}
        ll x=0; while(pos<len && buf[pos]>='0'&&buf[pos]<='9'){ x=x*10+(buf[pos]-'0'); pos++; }
        return neg?-x:x;
    };
    N=rd(); ll q=rd();
    ll sA=nm(rd()),aA=nm(rd()),cA=nm(rd()),sB=nm(rd()),aB=nm(rd()),cB=nm(rd());

    nmod=nm(N);
    inv2=inv(2); inv6=inv(6);
    Sk = nmod*nm(N-1)%P*inv2%P;
    Sk2 = nm(N-1)*nmod%P*nm(2*nmod-1)%P*inv6%P;

    // classify A: geo iff aA!=1 ; linear iff aA==1
    bool Ageo = (aA!=1), Bgeo = (aB!=1);
    // A geo params
    ll XA=0,YA=0,rA=0;
    ll LA1=0; // linear slope (in k) for A = cA
    if(Ageo){ YA = cA*inv(nm(1-aA))%P; XA=nm(sA-YA); rA=aA; }
    else { LA1=cA; }
    // B geo params
    ll XB=0,YB=0,rB=0;
    ll LB1=0; // linear slope in k for B = cB*n
    if(Bgeo){ YB = cB*inv(nm(1-aB))%P; XB=nm(sB-YB); rB=pw(aB,N); }
    else { LB1=cB*nmod%P; }

    // precompute needed geometric sums
    ll geoRA=0,geoRB=0,geoRARB=0,geoKRA=0,geoKRB=0;
    if(Ageo&&Bgeo){ geoRARB=geo(nm(rA*rB)); geoRA=geo(rA); geoRB=geo(rB); }
    else if(Ageo&&!Bgeo){ geoRA=geo(rA); geoKRA=geoK(rA); }
    else if(!Ageo&&Bgeo){ geoRB=geo(rB); geoKRB=geoK(rB); }
    // LL uses only nmod,Sk,Sk2

    string out; out.reserve(q*11);
    char tmp[16];
    for(ll t=0;t<q;t++){
        ll i=rd(), j=rd();
        ll ans;
        if(Ageo&&Bgeo){
            ll PA = XA*pw(aA,(ll)i*N)%P;
            ll PB = XB*pw(aB,(ll)j)%P;
            ans = nm( PA*PB%P*geoRARB + PA*YB%P*geoRA + YA*PB%P*geoRB + YA*YB%P*nmod );
        } else if(Ageo&&!Bgeo){
            ll PA = XA*pw(aA,(ll)i*N)%P;
            ll LB0 = nm(sB + cB*nm(j)%P);
            ans = nm( PA*LB0%P*geoRA + PA*LB1%P*geoKRA + YA*LB0%P*nmod + YA*LB1%P*Sk );
        } else if(!Ageo&&Bgeo){
            ll LA0 = nm(sA + cA*nm((ll)i*N%P)%P);
            ll PB = XB*pw(aB,(ll)j)%P;
            ans = nm( LA0*PB%P*geoRB + LA1*PB%P*geoKRB + LA0*YB%P*nmod + LA1*YB%P*Sk );
        } else {
            ll LA0 = nm(sA + cA*nm((ll)i*N%P)%P);
            ll LB0 = nm(sB + cB*nm(j)%P);
            ans = nm( LA0*LB0%P*nmod + nm(LA0*LB1 + LA1*LB0)%P*Sk + LA1*LB1%P*Sk2 );
        }
        int l=0; if(ans==0) tmp[l++]='0'; else { char b[16]; int c=0; ll v=ans; while(v){b[c++]='0'+v%10;v/=10;} while(c)tmp[l++]=b[--c]; }
        tmp[l++]='\n';
        out.append(tmp,l);
    }
    fwrite(out.data(),1,out.size(),stdout);
    return 0;
}
