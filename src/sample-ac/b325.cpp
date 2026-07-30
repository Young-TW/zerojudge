#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;

struct Seg { ll ax, ay, bx, by, num; }; // num = cross(A,B)
static vector<Seg> segs;
static ll curDx, curDy; // current sweep direction (integer)

// distance param t = num / den, den = cross(dir, B-A); t>0 while active
static inline ll denOf(int i){ const Seg&s=segs[i]; return curDx*(s.by-s.ay) - curDy*(s.bx-s.ax); }
struct Cmp {
    bool operator()(int i, int j) const {
        if(i==j) return false;
        ll di=denOf(i), dj=denOf(j);
        lll ni=segs[i].num, nj=segs[j].num;
        if(ni<0) ni=-ni; if(nj<0) nj=-nj;
        lll ad=di<0?-(lll)di:(lll)di, bd=dj<0?-(lll)dj:(lll)dj;
        lll L = ni*bd, R = nj*ad; // t_i<t_j  <=> ni/ad < nj/bd <=> ni*bd < nj*ad
        if(L!=R) return L<R;
        return i<j;
    }
};

static inline int half(ll x, ll y){ return (y>0 || (y==0 && x>0)) ? 0 : 1; }
static inline bool angLess(ll ux, ll uy, ll vx, ll vy){ // angle(u) < angle(v), CCW from +x
    int hu=half(ux,uy), hv=half(vx,vy);
    if(hu!=hv) return hu<hv;
    lll cr = (lll)ux*vy - (lll)uy*vx; // >0 : v is CCW of u
    return cr>0;
}
static inline bool angEq(ll ux, ll uy, ll vx, ll vy){
    return half(ux,uy)==half(vx,vy) && (lll)ux*vy-(lll)uy*vx==0;
}

struct Ev { ll dx, dy; int ins; int seg; };

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll n;
    string out;
    while(cin>>n){
        segs.assign(n, Seg{});
        vector<char> vis(n,0);
        vector<Ev> evs;
        vector<int> wrapSegs;
        for(int i=0;i<n;i++){
            ll ax,ay,bx,by; cin>>ax>>ay>>bx>>by;
            segs[i] = {ax,ay,bx,by, ax*by-ay*bx};
            ll cr = ax*by - ay*bx; // cross(A,B)
            if(cr==0){ vis[i]=0; continue; } // radial/degenerate -> not visible
            ll sx,sy,ex,ey; // arc CCW from start to end (<pi)
            if(cr>0){ sx=ax; sy=ay; ex=bx; ey=by; }
            else    { sx=bx; sy=by; ex=ax; ey=ay; }
            bool wrap = angLess(ex,ey,sx,sy); // end angle < start angle -> crosses +x axis
            if(wrap) wrapSegs.push_back(i);
            evs.push_back({sx,sy,1,i});
            evs.push_back({ex,ey,0,i});
        }
        sort(evs.begin(), evs.end(), [](const Ev&a, const Ev&b){
            return angLess(a.dx,a.dy,b.dx,b.dy);
        });
        multiset<int,Cmp> active;
        vector<multiset<int,Cmp>::iterator> pos(n);
        // initial active = wrap segments, direction +x (angle 0)
        curDx=1; curDy=0;
        for(int s: wrapSegs) pos[s]=active.insert(s);
        if(!active.empty()) vis[*active.begin()]=1; // arc across angle 0
        size_t i=0, m=evs.size();
        while(i<m){
            size_t j=i;
            ll gx=evs[i].dx, gy=evs[i].dy;
            curDx=gx; curDy=gy;
            while(j<m && angEq(evs[j].dx,evs[j].dy,gx,gy)) j++;
            for(size_t k=i;k<j;k++) if(!evs[k].ins) active.erase(pos[evs[k].seg]); // removes first
            for(size_t k=i;k<j;k++) if(evs[k].ins) pos[evs[k].seg]=active.insert(evs[k].seg);
            if(!active.empty()) vis[*active.begin()]=1;
            i=j;
        }
        string line;
        for(int k=0;k<n;k++){ if(k) line+=' '; line+=(vis[k]?'1':'0'); }
        line+='\n';
        out+=line;
    }
    cout<<out;
    return 0;
}
