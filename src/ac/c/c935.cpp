#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
typedef __uint128_t u128;
struct U{u64 v[4];
U(){v[0]=v[1]=v[2]=v[3]=0;}
U(u64 x){v[0]=x;v[1]=v[2]=v[3]=0;}
U(const string&s){v[0]=v[1]=v[2]=v[3]=0;for(char c:s){if(c<'0'||c>'9')continue;ms(10);as(c-'0');}}
void ms(u64 m){u128 c=0;for(int i=0;i<4;i++){c+=(u128)v[i]*m;v[i]=(u64)c;c>>=64;}}
void as(u64 a){u128 c=a;for(int i=0;i<4&&c;i++){c+=v[i];v[i]=(u64)c;c>>=64;}}
u64 ds(u64 d){u128 r=0;for(int i=3;i>=0;i--){r=(r<<64)|v[i];v[i]=(u64)(r/d);r%=d;}return(u64)r;}
string str()const{if(iz())return"0";U t=*this;string s;while(!t.iz()){u64 r=t.ds(10);s.push_back('0'+(char)r);}reverse(s.begin(),s.end());return s;}
bool iz()const{return(v[0]|v[1]|v[2]|v[3])==0;}
bool io()const{return v[0]&1ULL;}
bool ie()const{return!(v[0]&1ULL);}
int bl()const{for(int i=3;i>=0;i--)if(v[i])return i*64+64-__builtin_clzll(v[i]);return 0;}
bool operator==(const U&o)const{return v[0]==o.v[0]&&v[1]==o.v[1]&&v[2]==o.v[2]&&v[3]==o.v[3];}
bool operator!=(const U&o)const{return!(*this==o);}
bool operator<(const U&o)const{for(int i=3;i>=0;i--)if(v[i]!=o.v[i])return v[i]<o.v[i];return false;}
bool operator>=(const U&o)const{return!(*this<o);}
U s1()const{U r;u64 c=0;for(int i=0;i<4;i++){r.v[i]=(v[i]<<1)|c;c=v[i]>>63;}return r;}
U r1()const{U r;u64 c=0;for(int i=3;i>=0;i--){r.v[i]=(v[i]>>1)|c;c=v[i]<<63;}return r;}
U sl(int k)const{if(k==0)return*this;if(k>=256)return U(0);U r;int lm=k/64,bt=k%64;for(int i=3;i>=lm;i--){r.v[i]=v[i-lm]<<bt;if(bt&&i-lm-1>=0)r.v[i]|=v[i-lm-1]>>(64-bt);}return r;}
static U add(const U&a,const U&b){U r;u128 c=0;for(int i=0;i<4;i++){c+=(u128)a.v[i]+b.v[i];r.v[i]=(u64)c;c>>=64;}return r;}
static U sub(const U&a,const U&b){U r;u128 br=0;for(int i=0;i<4;i++){u128 d=(u128)a.v[i]-b.v[i]-br;br=(d>>64)&1;r.v[i]=(u64)d;}return r;}
static void dm(const U&a,const U&b,U&q,U&r){if(b.iz())return;if(a<b){q=U(0);r=a;return;}q=U(0);r=a;int sh=a.bl()-b.bl();U d=b.sl(sh);for(int i=0;i<=sh;i++){q=q.s1();if(r>=d){r=sub(r,d);q.v[0]|=1;}d=d.r1();}}
static U dvd(const U&a,const U&b){U q,r;dm(a,b,q,r);return q;}
static U mod(const U&a,const U&m){U q,r;dm(a,m,q,r);return r;}
static U gcd(U a,U b){if(a.iz())return b;if(b.iz())return a;int sh=0;while(a.ie()&&b.ie()){a=a.r1();b=b.r1();sh++;}while(a.ie())a=a.r1();while(!b.iz()){while(b.ie())b=b.r1();if(b<a)swap(a,b);b=sub(b,a);}while(sh--)a=a.s1();return a;}
};
U MN,MR2;u64 MNP;
void setmod(const U&n){MN=n;u64 x=n.v[0],inv=x;for(int i=0;i<5;i++)inv*=2-x*inv;MNP=(u64)(0-inv);
U r(1);for(int i=0;i<384;i++){r=r.s1();if(r>=MN)r=U::sub(r,MN);}MR2=r;}
U mmul(const U&a,const U&b){u64 t[5]={0,0,0,0,0};
for(int i=0;i<3;i++){u128 c=0;for(int j=0;j<3;j++){u128 p=(u128)a.v[j]*b.v[i]+t[j]+c;t[j]=(u64)p;c=p>>64;}
u128 s=(u128)t[3]+c;t[3]=(u64)s;t[4]=(u64)(s>>64);
u64 m=(u64)((u128)t[0]*MNP);u128 p=(u128)m*MN.v[0]+t[0];c=p>>64;
for(int j=1;j<3;j++){u128 q=(u128)m*MN.v[j]+t[j]+c;t[j-1]=(u64)q;c=q>>64;}
u128 s2=(u128)t[3]+c;t[2]=(u64)s2;c=s2>>64;t[3]=t[4]+(u64)c;t[4]=0;}
U r;r.v[0]=t[0];r.v[1]=t[1];r.v[2]=t[2];r.v[3]=0;if(r>=MN)r=U::sub(r,MN);return r;}
U madd(const U&a,const U&b){U r=U::add(a,b);if(r>=MN)r=U::sub(r,MN);return r;}
U tom(const U&a){return mmul(a,MR2);}
U mpow(U a,U e){U r=tom(U(1));while(!e.iz()){if(e.io())r=mmul(r,a);a=mmul(a,a);e=e.r1();}return r;}
u64 rs[2];
void ir(){rs[0]=(u64)time(0)^0x9e3779b97f4a7c15ULL;rs[1]=(u64)clock()^(u64)&rs;}
u64 xr(){u64 x=rs[0],y=rs[1];rs[0]=y;x^=x<<23;rs[1]=x^y^(x>>17)^(y>>26);return rs[1]+y;}
U randU(const U&n){U r;r.v[0]=xr();r.v[1]=xr();r.v[2]=xr();r.v[3]=0;r=U::mod(r,n);if(r.iz())r=U(1);return r;}
u64 SP[]={2,3,5,7,11,13,17,19,23,29,31,37};
bool ip(const U&n){if(n<U(2))return false;for(u64 sp:SP){if(n==U(sp))return true;if(U::mod(n,U(sp)).iz())return false;}
setmod(n);U d=U::sub(n,U(1));int s=0;while(d.ie()){d=d.r1();s++;}
U one=tom(U(1)),nm1=tom(U::sub(n,U(1)));
for(u64 a:SP){U x=mpow(tom(U(a)),d);if(x==one||x==nm1)continue;bool cp=true;for(int r=0;r<s-1;r++){x=mmul(x,x);if(x==nm1){cp=false;break;}}if(cp)return false;}
return true;}
U diff(const U&x,const U&y){return x>=y?U::sub(x,y):U::sub(MN,U::sub(y,x));}
U pr(const U&n){if(n.ie())return U(2);if(ip(n))return n;setmod(n);
while(true){U c=tom(randU(n)),y=tom(randU(n)),g(1),q=tom(U(1)),x,ys;long long r=1,m=128;
auto f=[&](const U&u){U t=mmul(u,u);return madd(t,c);};
do{x=y;for(long long i=0;i<r;i++)y=f(y);long long k=0;
do{ys=y;long long lim=min(m,r-k);for(long long i=0;i<lim;i++){y=f(y);q=mmul(q,diff(x,y));}g=U::gcd(q,n);k+=m;}while(k<r&&g==U(1));
r*=2;}while(g==U(1));
if(g==n){do{ys=f(ys);g=U::gcd(diff(x,ys),n);}while(g==U(1));}
if(g!=n)return g;}}
void fac(const U&n,vector<U>&fs){if(!(U(1)<n))return;if(ip(n)){fs.push_back(n);return;}U d=pr(n);fac(d,fs);fac(U::dvd(n,d),fs);}
int main(){ios::sync_with_stdio(false);cin.tie(0);ir();string ln;while(cin>>ln){U n(ln);vector<U>fs;fac(n,fs);sort(fs.begin(),fs.end());for(size_t i=0;i<fs.size();i++){if(i)cout<<' ';cout<<fs[i].str();}cout<<'\n';}return 0;}
