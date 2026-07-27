// ZeroJudge a547 - Driving Directions
// Shortest path of a disk (radius R) center among axis-aligned rectangles.
// Forbidden region for the center = union of Minkowski(rect, disk_R)
// = rounded rectangles (edges offset by R, quarter-circle corners of radius R).
// Tangent visibility graph + Dijkstra.
//
// Optimizations vs naive:
//  - Arc edges only between angularly-ADJACENT contacts on each circle
//    (arcs are additive along the boundary => O(C) arcs, not O(C^2)).
//  - Per-circle candidate blocker rects: a rect can block an arc only if the
//    corner is within 2R of it (triangle inequality) => arc checks touch few rects.
//  - segFree uses bounding-box pruning + squared distances (early-out).
//  - Contact nodes created only for tangents that survive the collision test.
#include <bits/stdc++.h>
using namespace std;

static const double PI = acos(-1.0);
static const double EPSD = 1e-9;

double R, R2; // radius and radius^2
struct Rect { double x1,y1,x2,y2; };
vector<Rect> rects;

// squared distance from point to rectangle
inline double pointRectDist2(double px,double py,const Rect&r){
    double dx = max(max(r.x1-px, 0.0), px-r.x2);
    double dy = max(max(r.y1-py, 0.0), py-r.y2);
    return dx*dx+dy*dy;
}
inline double pointSegDist2(double px,double py,double ax,double ay,double bx,double by){
    double vx=bx-ax, vy=by-ay, wx=px-ax, wy=py-ay;
    double c1=vx*wx+vy*wy; if(c1<=0) return (px-ax)*(px-ax)+(py-ay)*(py-ay);
    double c2=vx*vx+vy*vy; if(c2<=c1) return (px-bx)*(px-bx)+(py-by)*(py-by);
    double t=c1/c2, dx=px-(ax+t*vx), dy=py-(ay+t*vy); return dx*dx+dy*dy;
}
inline double cross(double ox,double oy,double ax,double ay,double bx,double by){
    return (ax-ox)*(by-oy)-(ay-oy)*(bx-ox);
}
inline int sgn(double v){ return (v>1e-12)-(v<-1e-12); }
bool segSegIntersect(double ax,double ay,double bx,double by,
                     double cx,double cy,double dx,double dy){
    double d1=cross(cx,cy,dx,dy,ax,ay), d2=cross(cx,cy,dx,dy,bx,by);
    double d3=cross(ax,ay,bx,by,cx,cy), d4=cross(ax,ay,bx,by,dx,dy);
    if(((sgn(d1)*sgn(d2))<0) && ((sgn(d3)*sgn(d4))<0)) return true;
    auto onseg=[&](double px,double py,double qx,double qy,double rx,double ry){
        return min(px,qx)-1e-9<=rx && rx<=max(px,qx)+1e-9 &&
               min(py,qy)-1e-9<=ry && ry<=max(py,qy)+1e-9;
    };
    if(sgn(d1)==0 && onseg(cx,cy,dx,dy,ax,ay)) return true;
    if(sgn(d2)==0 && onseg(cx,cy,dx,dy,bx,by)) return true;
    if(sgn(d3)==0 && onseg(ax,ay,bx,by,cx,cy)) return true;
    if(sgn(d4)==0 && onseg(ax,ay,bx,by,dx,dy)) return true;
    return false;
}
// squared min distance between segment PQ and rectangle
double segRectMinDist2(double px,double py,double qx,double qy,const Rect&r){
    if(segSegIntersect(px,py,qx,qy,r.x1,r.y1,r.x2,r.y1)) return 0.0;
    if(segSegIntersect(px,py,qx,qy,r.x2,r.y1,r.x2,r.y2)) return 0.0;
    if(segSegIntersect(px,py,qx,qy,r.x2,r.y2,r.x1,r.y2)) return 0.0;
    if(segSegIntersect(px,py,qx,qy,r.x1,r.y2,r.x1,r.y1)) return 0.0;
    double m=min(pointRectDist2(px,py,r), pointRectDist2(qx,qy,r));
    double X[5]={r.x1,r.x2,r.x2,r.x1,r.x1};
    double Y[5]={r.y1,r.y1,r.y2,r.y2,r.y1};
    for(int e=0;e<4;e++){
        m=min(m, pointSegDist2(X[e],Y[e],px,py,qx,qy));
        m=min(m, pointSegDist2(X[e+1],Y[e+1],px,py,qx,qy));
    }
    return m;
}
// segment collision-free: min dist to every rect >= R (touching allowed)
bool segFree(double px,double py,double qx,double qy){
    double sminx=min(px,qx), smaxx=max(px,qx);
    double sminy=min(py,qy), smaxy=max(py,qy);
    double thr = R - 1e-7; double thr2 = thr*thr;
    for(auto&r:rects){
        // bbox prune: rect expanded by R vs segment bbox
        if(smaxx < r.x1-R || sminx > r.x2+R || smaxy < r.y1-R || sminy > r.y2+R) continue;
        if(segRectMinDist2(px,py,qx,qy,r) < thr2) return false;
    }
    return true;
}

struct Circle { double cx,cy; double lo,hi; int ownRect; vector<int> cand; };
vector<Circle> circles;
struct Obj { double cx,cy,rad; int circleIdx; };
vector<Obj> objs;

// normalize contact angle into circle quarter; NAN if outside valid arc
inline double contactAngle(double px,double py,const Circle&c){
    double ang = atan2(py-c.cy, px-c.cx)*180.0/PI;
    while(ang<c.lo-1e-9) ang+=360.0;
    while(ang>=c.lo+360.0) ang-=360.0;
    if(ang <= c.hi+1e-6) return ang;
    return NAN;
}
// arc (a1..a2 degrees) collision-free wrt other rects (own excluded from cand)
bool arcFree(const Circle&c,double a1,double a2){
    if(c.cand.empty()) return true;
    double spanRad = fabs(a2-a1)*PI/180.0;
    int N = (int)ceil(R*spanRad/0.25);
    if(N<8) N=8; if(N>256) N=256;
    double thr = R - 1e-7; double thr2 = thr*thr;
    for(int i=0;i<=N;i++){
        double ang=(a1+(a2-a1)*i/N)*PI/180.0;
        double px=c.cx+R*cos(ang), py=c.cy+R*sin(ang);
        for(int k : c.cand){
            if(pointRectDist2(px,py,rects[k]) < thr2) return false;
        }
    }
    return true;
}

int main(){
    int n;
    while(scanf("%lf %d",&R,&n)==2){
        double xA,yA,xB,yB;
        if(scanf("%lf %lf %lf %lf",&xA,&yA,&xB,&yB)!=4) break;
        R2=R*R;
        rects.assign(n,{}); circles.clear(); objs.clear();
        for(int i=0;i<n;i++)
            scanf("%lf %lf %lf %lf",&rects[i].x1,&rects[i].y1,&rects[i].x2,&rects[i].y2);

        for(int i=0;i<n;i++){
            Rect&r=rects[i];
            circles.push_back({r.x1,r.y1,180,270,i,{}}); // LL
            circles.push_back({r.x2,r.y1,270,360,i,{}}); // LR
            circles.push_back({r.x2,r.y2,0,90,i,{}});    // UR
            circles.push_back({r.x1,r.y2,90,180,i,{}});  // UL
        }
        // per-circle candidate blocker rects (corner within 2R)
        double twoR2 = (2.0*R)*(2.0*R) + 1e-6;
        for(auto&c:circles)
            for(int k=0;k<n;k++)
                if(k!=c.ownRect && pointRectDist2(c.cx,c.cy,rects[k]) < twoR2)
                    c.cand.push_back(k);

        objs.push_back({xA,yA,0.0,-1}); // node 0 = A
        objs.push_back({xB,yB,0.0,-1}); // node 1 = B
        for(int i=0;i<(int)circles.size();i++)
            objs.push_back({circles[i].cx,circles[i].cy,R,i});

        vector<vector<pair<int,double>>> adj(2);
        vector<unordered_map<long long,int>> angMap(circles.size());
        vector<vector<pair<double,int>>> circContacts(circles.size());

        auto getContactNode=[&](int ci,double ang)->int{
            long long key=(long long)llround(ang*1e6);
            auto it=angMap[ci].find(key);
            if(it!=angMap[ci].end()) return it->second;
            int id=adj.size(); adj.push_back({});
            angMap[ci][key]=id;
            circContacts[ci].push_back({ang,id});
            return id;
        };
        auto addEdge=[&](int u,int v,double w){
            adj[u].push_back({v,w}); adj[v].push_back({u,w});
        };

        int M=objs.size();
        for(int i=0;i<M;i++) for(int j=i+1;j<M;j++){
            double c1x=objs[i].cx,c1y=objs[i].cy,r1=objs[i].rad;
            double c2x=objs[j].cx,c2y=objs[j].cy,r2=objs[j].rad;
            double D=hypot(c2x-c1x,c2y-c1y);
            if(D<EPSD) continue;
            double ux=(c2x-c1x)/D, uy=(c2y-c1y)/D;
            double wx=-uy, wy=ux;
            double ks[2]; double s2s[2]; int nt=0;
            { double ke=(r2-r1)/D; if(fabs(ke)<=1.0+1e-12){ ks[nt]=ke; s2s[nt]=+1.0; nt++; } }
            { double ki=-(r1+r2)/D; if(fabs(ki)<=1.0+1e-12){ ks[nt]=ki; s2s[nt]=-1.0; nt++; } }
            for(int ti=0;ti<nt;ti++){
                double k=ks[ti]; if(k>1)k=1; if(k<-1)k=-1;
                double s=sqrt(max(0.0,1.0-k*k)); double s2=s2s[ti];
                for(int sign=-1;sign<=1;sign+=2){
                    double nx=k*ux+sign*s*wx;
                    double ny=k*uy+sign*s*wy;
                    // contact = center - offset*n (sign loop covers both normals)
                    double p1x=c1x-r1*nx, p1y=c1y-r1*ny;
                    double p2x=c2x-s2*r2*nx, p2y=c2y-s2*r2*ny;
                    double angI=0, angJ=0;
                    if(objs[i].circleIdx>=0){
                        angI=contactAngle(p1x,p1y,circles[objs[i].circleIdx]);
                        if(std::isnan(angI)) continue;
                    }
                    if(objs[j].circleIdx>=0){
                        angJ=contactAngle(p2x,p2y,circles[objs[j].circleIdx]);
                        if(std::isnan(angJ)) continue;
                    }
                    if(!segFree(p1x,p1y,p2x,p2y)) continue;
                    int nodeI = (objs[i].circleIdx<0) ? i : getContactNode(objs[i].circleIdx,angI);
                    int nodeJ = (objs[j].circleIdx<0) ? j : getContactNode(objs[j].circleIdx,angJ);
                    addEdge(nodeI,nodeJ,hypot(p2x-p1x,p2y-p1y));
                }
            }
        }

        // arc edges: only between angularly-adjacent contacts on each circle
        for(int ci=0;ci<(int)circles.size();ci++){
            auto&cs=circContacts[ci];
            if(cs.size()<2) continue;
            sort(cs.begin(),cs.end());
            for(int a=0;a+1<(int)cs.size();a++){
                double a1=cs[a].first, a2=cs[a+1].first;
                if(arcFree(circles[ci],a1,a2))
                    addEdge(cs[a].second, cs[a+1].second, R*fabs(a1-a2)*PI/180.0);
            }
        }

        int V=adj.size();
        vector<double> dist(V,1e18);
        priority_queue<pair<double,int>,vector<pair<double,int>>,greater<>> pq;
        dist[0]=0; pq.push({0,0});
        while(!pq.empty()){
            double d=pq.top().first; int u=pq.top().second; pq.pop();
            if(d>dist[u]+1e-12) continue;
            if(u==1) break;
            for(auto&e:adj[u])
                if(dist[u]+e.second < dist[e.first]-1e-12){
                    dist[e.first]=dist[u]+e.second;
                    pq.push({dist[e.first],e.first});
                }
        }
        if(dist[1]>1e17) printf("no solution\n");
        else printf("%.6f\n",dist[1]);
    }
    return 0;
}
