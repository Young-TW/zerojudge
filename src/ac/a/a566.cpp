// ZeroJudge a566 - IOI2007 flood
// Algorithm:
//   Build the rectilinear planar graph. Trace all faces via angular (4-dir)
//   half-edge next. A wall separates two faces. Merge boundary cycles that
//   bound the same physical region (holes / disconnected / nested components)
//   using an upward-ray sweepline. BFS distances of faces from the outer face.
//   A wall stays standing iff its two faces have equal flood distance.
#include <bits/stdc++.h>
using namespace std;

// directions: 0=+x(right) 1=+y(up) 2=-x(left) 3=-y(down)
static const int DX[4]={1,0,-1,0};
static const int DY[4]={0,1,0,-1};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while(cin>>N){
        vector<long long> X(N+1), Y(N+1);
        for(int i=1;i<=N;i++) cin>>X[i]>>Y[i];
        int W; cin>>W;
        vector<int> WA(W+1), WB(W+1);
        // nbr[v][dir] = neighbor, wallId[v][dir] = wall index
        vector<array<int,4>> nbr(N+1), wid(N+1);
        for(int v=1;v<=N;v++){ nbr[v].fill(0); wid[v].fill(-1); }
        for(int i=1;i<=W;i++){
            int a,b; cin>>a>>b; WA[i]=a; WB[i]=b;
            int dir;
            if(X[a]==X[b]){ dir = (Y[a]<Y[b])?1:3; }
            else          { dir = (X[a]<X[b])?0:2; }
            nbr[a][dir]=b; wid[a][dir]=i;
            int rdir=(dir+2)&3;
            nbr[b][rdir]=a; wid[b][rdir]=i;
        }
        // half-edge id = v*4+dir. Trace faces (interior on left).
        int M=(N+1)*4;
        vector<int> cyc(M,-1);
        vector<double> area2; // signed area*2 per cycle
        vector<int> repV;     // representative topmost(tie leftmost) vertex per cycle
        auto nextEdge=[&](int v,int dir)->pair<int,int>{
            // move along (v -> to) dir, arrive at 'to', pick next outgoing dir
            int to=nbr[v][dir];
            int rdir=(dir+2)&3;
            // rotate clockwise from rdir: offsets +3,+2,+1,+0
            for(int k=3;k>=0;k--){
                int nd=(rdir+k)&3;
                if(nbr[to][nd]) return {to,nd};
            }
            return {to,rdir};
        };
        int nc=0;
        for(int v=1;v<=N;v++) for(int d=0;d<4;d++){
            if(!nbr[v][d]) continue;
            int id=v*4+d;
            if(cyc[id]!=-1) continue;
            int cid=nc++;
            area2.push_back(0.0);
            int bestV=v;
            int cv=v, cd=d;
            while(true){
                int cid_edge=cv*4+cd;
                if(cyc[cid_edge]!=-1) break;
                cyc[cid_edge]=cid;
                int to=nbr[cv][cd];
                area2[cid]+= (double)X[cv]*Y[to]-(double)X[to]*Y[cv];
                // track representative among cycle vertices (use cv)
                if(Y[cv]>Y[bestV] || (Y[cv]==Y[bestV] && X[cv]<X[bestV])) bestV=cv;
                auto nx=nextEdge(cv,cd);
                cv=nx.first; cd=nx.second;
            }
            repV.push_back(bestV);
        }
        // DSU over cycles + OUTER node (index nc)
        int OUT=nc;
        vector<int> dsu(nc+1);
        iota(dsu.begin(),dsu.end(),0);
        function<int(int)> find=[&](int x){ while(dsu[x]!=x){ dsu[x]=dsu[dsu[x]]; x=dsu[x]; } return x; };
        auto uni=[&](int a,int b){ a=find(a); b=find(b); if(a!=b) dsu[a]=b; };

        // horizontal edges: canonical via dir 0 (right). lowerCycle = cycle of -x half-edge.
        struct HE{ long long xl2,xr2,yc; int lowerCyc; };
        vector<HE> hes;
        for(int v=1;v<=N;v++){
            if(nbr[v][0]){
                int to=nbr[v][0];
                HE h;
                h.xl2=2*X[v]; h.xr2=2*X[to]; h.yc=Y[v];
                // -x half-edge starts at 'to' with dir 2
                h.lowerCyc=cyc[to*4+2];
                hes.push_back(h);
            }
        }
        // Sweepline: for each negative cycle, query nearest horizontal edge strictly above
        // its representative vertex; qx = 2*repX-1 (odd => no endpoint ties).
        // Events sorted by x-coordinate.
        struct Ev{ long long x; int type; int idx; }; // type:0 del,1 add,2 query
        vector<Ev> evs;
        for(int e=0;e<(int)hes.size();e++){
            evs.push_back({hes[e].xl2,1,e});
            evs.push_back({hes[e].xr2,0,e});
        }
        vector<int> qCyc; vector<long long> qY;
        for(int c=0;c<nc;c++){
            if(area2[c]<=0){ // non-positive cycle => hole/outer/degenerate boundary needing an owner
                int rv=repV[c];
                long long qx=2*X[rv]-1;
                evs.push_back({qx,2,(int)qCyc.size()});
                qCyc.push_back(c);
                qY.push_back(Y[rv]);
            }
        }
        sort(evs.begin(),evs.end(),[](const Ev&a,const Ev&b){
            if(a.x!=b.x) return a.x<b.x;
            return a.type<b.type; // del(0) < add(1) < query(2)
        });
        map<long long,int> active; // yc -> edge index
        for(auto&ev:evs){
            if(ev.type==0){ // del
                auto it=active.find(hes[ev.idx].yc);
                if(it!=active.end() && it->second==ev.idx) active.erase(it);
            } else if(ev.type==1){ // add
                active[hes[ev.idx].yc]=ev.idx;
            } else { // query
                int c=qCyc[ev.idx];
                long long yq=qY[ev.idx];
                auto it=active.upper_bound(yq);
                if(it==active.end()){ uni(c,OUT); }
                else{ uni(c, hes[it->second].lowerCyc); }
            }
        }
        // Build face graph (faces = DSU roots, ids in [0,nc]). Adjacency across walls.
        vector<int> wFaceA(W+1), wFaceB(W+1);
        vector<vector<int>> adj(nc+1);
        for(int i=1;i<=W;i++){
            int a=WA[i], b=WB[i];
            int dir;
            if(X[a]==X[b]) dir=(Y[a]<Y[b])?1:3; else dir=(X[a]<X[b])?0:2;
            int f1=find(cyc[a*4+dir]);
            int f2=find(cyc[b*4+((dir+2)&3)]);
            wFaceA[i]=f1; wFaceB[i]=f2;
            if(f1!=f2){ adj[f1].push_back(f2); adj[f2].push_back(f1); }
        }
        // BFS distance from OUTER face.
        vector<int> dist(nc+1,-1);
        int outRoot=find(OUT);
        deque<int> bfs; bfs.push_back(outRoot); dist[outRoot]=0;
        while(!bfs.empty()){
            int u=bfs.front(); bfs.pop_front();
            for(int w:adj[u]) if(dist[w]<0){ dist[w]=dist[u]+1; bfs.push_back(w); }
        }
        vector<int> ans;
        for(int i=1;i<=W;i++){
            int f1=wFaceA[i], f2=wFaceB[i];
            if(f1==f2 || dist[f1]==dist[f2]) ans.push_back(i);
        }
        cout<<ans.size()<<"\n";
        for(int x:ans) cout<<x<<"\n";
    }
    return 0;
}
