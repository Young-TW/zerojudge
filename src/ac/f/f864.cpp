#include<bits/stdc++.h>
using namespace std;
struct C{int r,s;bool operator<(const C&o)const{return r!=o.r?r<o.r:s<o.s;}bool operator==(const C&o)const{return r==o.r&&s==o.s;}};
struct V{int t,a,b,d;bool operator<(const V&o)const{if(t!=o.t)return t<o.t;if(a!=o.a)return a<o.a;if(b!=o.b)return b<o.b;return d<o.d;}};
bool ig(const V&a,const V&b){if(a.t>b.t)return 1;if(a.t<b.t)return 0;return b<a;}
C pc(const string&s){C c;char r=s[0],su;if(s.size()==3){c.r=10;su=s[2];}else{su=s[1];if(r=='2')c.r=15;else if(r=='A')c.r=14;else if(r=='K')c.r=13;else if(r=='Q')c.r=12;else if(r=='J')c.r=11;else c.r=r-'0';}c.s=su=='+'?3:su=='-'?2:su=='*'?1:0;return c;}
V hv(const vector<C>&cd){int n=cd.size();if(n==1)return{1,cd[0].r,cd[0].s,0};if(n==2){if(cd[0].r==cd[1].r)return{2,cd[0].r,0,0};return{0,0,0,0};}if(n==5){map<int,int>c;for(auto&x:cd)c[x.r]++;bool ss=1;for(int i=1;i<5;i++)if(cd[i].s!=cd[0].s)ss=0;bool st=0;int mx=cd[4].r,mn=cd[0].r;if((int)c.size()==5&&mx-mn==4&&mx<=14)st=1;if(ss&&st)return{6,mx,cd[0].s,0};for(auto&p:c)if(p.second==4){int fr=p.first,sr=0,su=0;for(auto&x:cd)if(x.r!=fr){sr=x.r;su=x.s;break;}return{5,fr,sr,su};}if((int)c.size()==2){int tr=0,pr=0;for(auto&p:c){if(p.second==3)tr=p.first;else if(p.second==2)pr=p.first;}if(tr&&pr)return{4,tr,pr,0};}if(st)return{3,mx,0,0};return{0,0,0,0};}return{0,0,0,0};}
vector<vector<C>> pairs(const vector<C>&h){map<int,vector<C>>br;for(auto&c:h)br[c.r].push_back(c);vector<vector<C>>r;for(auto&p:br)if(p.second.size()>=2)r.push_back({p.second[0],p.second[1]});return r;}
vector<vector<C>> fives(const vector<C>&h){vector<vector<C>>r;if(h.size()<5)return r;map<int,vector<C>>br,bs;for(auto&c:h){br[c.r].push_back(c);bs[c.s].push_back(c);}for(auto&p:bs)sort(p.second.begin(),p.second.end());
for(auto&p:bs){auto&su=p.second;for(size_t i=0;i+4<su.size();i++)if(su[i+4].r-su[i].r==4&&su[i+4].r<=14)r.push_back({su[i],su[i+1],su[i+2],su[i+3],su[i+4]});}
for(auto&p:br)if(p.second.size()==4){int fr=p.first;for(auto&c:h)if(c.r!=fr){auto fk=p.second;fk.push_back(c);sort(fk.begin(),fk.end());r.push_back(fk);break;}}
for(auto&p1:br)if(p1.second.size()>=3){int tr=p1.first;vector<C>th(p1.second.begin(),p1.second.begin()+3);for(auto&p2:br)if(p2.first!=tr&&p2.second.size()>=2){auto fh=th;fh.push_back(p2.second[0]);fh.push_back(p2.second[1]);sort(fh.begin(),fh.end());r.push_back(fh);}}
for(int s=3;s<=10;s++){bool ok=1;vector<C>st;for(int rr=s;rr<=s+4;rr++){auto it=br.find(rr);if(it==br.end()||it->second.empty()){ok=0;break;}st.push_back(it->second[0]);}if(ok){sort(st.begin(),st.end());r.push_back(st);}}
return r;}
bool drg(const vector<C>&h){if(h.size()!=13)return 0;int s=h[0].s;vector<int>rk;for(auto&c:h){if(c.s!=s)return 0;rk.push_back(c.r);}sort(rk.begin(),rk.end());for(int i=0;i<13;i++)if(rk[i]!=i+3)return 0;return 1;}
void rmv(vector<C>&h,const vector<C>&rm){for(auto&c:rm){auto it=find(h.begin(),h.end(),c);if(it!=h.end())h.erase(it);}sort(h.begin(),h.end());}
bool cl(const vector<C>&a,const vector<C>&b){int n=min(a.size(),b.size());for(int i=0;i<n;i++){if(a[i]<b[i])return 1;if(b[i]<a[i])return 0;}return a.size()<b.size();}
vector<C> best(vector<vector<C>>&cs){int bi=0;for(int i=1;i<(int)cs.size();i++){V vi=hv(cs[i]),vb=hv(cs[bi]);if(vi<vb||(!(vb<vi)&&cl(cs[i],cs[bi])))bi=i;}return cs[bi];}
int main(){int N;cin>>N;while(N--){int x[4],G;cin>>x[0]>>x[1]>>x[2]>>x[3]>>G;vector<C>hd[4];for(int i=0;i<4;i++){for(int j=0;j<x[i];j++){string s;cin>>s;hd[i].push_back(pc(s));}sort(hd[i].begin(),hd[i].end());}
vector<int>win;bool fin[4]={0,0,0,0};int fc=0,cur=G-1;vector<C>last;int lp=-1;V lv={0,0,0,0};
while(fc<4){
if(last.empty()){
while(fin[cur])cur=(cur+1)%4;
auto&h=hd[cur];
if(drg(h)){win.push_back(cur+1);fin[cur]=1;fc++;h.clear();last.clear();cur=(cur+1)%4;continue;}
auto fv=fives(h);auto pr=pairs(h);vector<C>ch;
if(!fv.empty())ch=best(fv);
else if(!pr.empty())ch=best(pr);
else ch={h[0]};
rmv(h,ch);last=ch;lv=hv(ch);lp=cur;
if(h.empty()){win.push_back(cur+1);fin[cur]=1;fc++;last.clear();}
cur=(cur+1)%4;
}else{
int pl=cur;
while(1){
if(pl==lp){last.clear();cur=lp;break;}
if(!fin[pl]){
auto&h=hd[pl];vector<vector<C>>cand;
if(lv.t==1){for(auto&c:h){V v=hv({c});if(ig(v,lv))cand.push_back({c});}}
else if(lv.t==2){auto ap=pairs(h);for(auto&p:ap){V v=hv(p);if(ig(v,lv))cand.push_back(p);}}
else if(lv.t>=3){auto af=fives(h);for(auto&f:af){V v=hv(f);if(ig(v,lv))cand.push_back(f);}}
if(!cand.empty()){vector<C>ch=best(cand);rmv(h,ch);last=ch;lv=hv(ch);lp=pl;
if(h.empty()){win.push_back(pl+1);fin[pl]=1;fc++;last.clear();cur=(pl+1)%4;}else cur=(pl+1)%4;
break;}
}
pl=(pl+1)%4;
}
}
}
for(size_t i=0;i<win.size();i++){if(i)cout<<" ";cout<<win[i];}cout<<"\n";
}return 0;}
