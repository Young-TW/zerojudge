#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
const ld BIG = 1e30L;
const ld PI = acosl(-1.0L);

struct Box{ ld x1,x2,y1,y2; };

int N;
vector<Box> B;   // barriers translated so source at origin
ld R;

struct Res{ ld d; bool vert; ld c; };

// nearest of {square boundary, first barrier entry} along direction theta
Res evalMin(ld th){
    ld ct=cosl(th), st=sinl(th);
    Res best;
    if(fabsl(ct) >= fabsl(st)){ best.d=R/fabsl(ct); best.vert=true;  best.c=(ct>0? R:-R); }
    else                      { best.d=R/fabsl(st); best.vert=false; best.c=(st>0? R:-R); }
    for(auto&b:B){
        ld txlow,txhigh,xc;
        if(fabsl(ct)<1e-18L){ if(b.x1>0||b.x2<0) continue; txlow=-BIG; txhigh=BIG; xc=0; }
        else if(ct>0){ txlow=b.x1/ct; txhigh=b.x2/ct; xc=b.x1; }
        else         { txlow=b.x2/ct; txhigh=b.x1/ct; xc=b.x2; }
        ld tylow,tyhigh,yc;
        if(fabsl(st)<1e-18L){ if(b.y1>0||b.y2<0) continue; tylow=-BIG; tyhigh=BIG; yc=0; }
        else if(st>0){ tylow=b.y1/st; tyhigh=b.y2/st; yc=b.y1; }
        else         { tylow=b.y2/st; tyhigh=b.y1/st; yc=b.y2; }
        ld tentry=max(txlow,tylow), texit=min(txhigh,tyhigh);
        if(tentry>texit) continue;
        if(texit<=0) continue;
        ld dist; bool vert; ld c;
        if(tentry<=0){ dist=0; vert=true; c=0; }
        else { dist=tentry; if(txlow>tylow){vert=true;c=xc;} else {vert=false;c=yc;} }
        if(dist<best.d){ best.d=dist; best.vert=vert; best.c=c; }
    }
    return best;
}

// antiderivative of 0.5*(c/cos)^2 = 0.5 c^2 tan ; of 0.5*(c/sin)^2 = -0.5 c^2 cot
ld pieceIntegral(ld th1, ld th2){
    ld tm=(th1+th2)/2;
    Res r=evalMin(tm);
    ld c2=r.c*r.c;
    if(r.vert){ return 0.5L*c2*(tanl(th2)-tanl(th1)); }
    else{ ld cot2=cosl(th2)/sinl(th2), cot1=cosl(th1)/sinl(th1); return -0.5L*c2*(cot2-cot1); }
}

ld unionArea(){ // barriers clipped to square, inclusion-exclusion
    vector<Box> C;
    for(auto&b:B){
        ld x1=max(b.x1,-R),x2=min(b.x2,R),y1=max(b.y1,-R),y2=min(b.y2,R);
        if(x1<x2 && y1<y2) C.push_back({x1,x2,y1,y2});
    }
    int n=C.size(); ld area=0;
    for(int m=1;m<(1<<n);m++){
        ld xl=-BIG,xr=BIG,yb=-BIG,yt=BIG; int bits=0;
        for(int i=0;i<n;i++) if(m>>i&1){ xl=max(xl,C[i].x1);xr=min(xr,C[i].x2);yb=max(yb,C[i].y1);yt=min(yt,C[i].y2); bits++; }
        if(xl<xr&&yb<yt){ ld a=(xr-xl)*(yt-yb); area += (bits&1)? a : -a; }
    }
    return area;
}

int main(){
    int T;
    while(scanf("%d",&T)==1)
    while(T--){
        long long Rl,px,py; int n;
        scanf("%lld %lld %lld %d",&Rl,&px,&py,&n);
        R=(ld)Rl; N=n; B.clear();
        for(int i=0;i<n;i++){
            long long x,y,X,Y; scanf("%lld %lld %lld %lld",&x,&y,&X,&Y);
            Box b; b.x1=(ld)min(x,X)-px; b.x2=(ld)max(x,X)-px; b.y1=(ld)min(y,Y)-py; b.y2=(ld)max(y,Y)-py;
            B.push_back(b);
        }
        // critical angles
        vector<ld> V,H;
        V.push_back(R); V.push_back(-R); H.push_back(R); H.push_back(-R);
        for(auto&b:B){ V.push_back(b.x1);V.push_back(b.x2);H.push_back(b.y1);H.push_back(b.y2); }
        vector<ld> ev;
        for(ld vx:V) for(ld hy:H){ ld a=atan2l(hy,vx); if(a<0)a+=2*PI; ev.push_back(a); }
        for(ld a: {0.0L, PI/2, PI, 3*PI/2}) ev.push_back(a);
        ev.push_back(0.0L); ev.push_back(2*PI);
        sort(ev.begin(),ev.end());
        vector<ld> u;
        for(ld a:ev){ if(a<-1e-12L||a>2*PI+1e-12L) continue; if(u.empty()||a-u.back()>1e-13L) u.push_back(a); }
        if(u.front()>1e-13L) u.insert(u.begin(),0.0L);
        if(2*PI-u.back()>1e-13L) u.push_back(2*PI);
        ld visible=0;
        for(size_t i=0;i+1<u.size();i++){ if(u[i+1]-u[i]<1e-15L) continue; visible+=pieceIntegral(u[i],u[i+1]); }
        ld occluded = 4*R*R - visible;
        ld ans = occluded - unionArea();
        if(ans<0) ans=0;
        printf("%.2f\n",(double)ans);
    }
    return 0;
}
