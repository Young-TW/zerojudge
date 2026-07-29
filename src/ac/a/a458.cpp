#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = (ll)4e18;

struct SegTree { // range chmin, point query
    int n; vector<ll> t;
    void init(int n_){ n=n_; t.assign(4*n, INF); }
    void upd(int node,int l,int r,int ql,int qr,ll v){
        if(qr<l||r<ql) return;
        if(ql<=l&&r<=qr){ if(v<t[node]) t[node]=v; return; }
        int mid=(l+r)/2;
        upd(2*node,l,mid,ql,qr,v); upd(2*node+1,mid+1,r,ql,qr,v);
    }
    ll qry(int node,int l,int r,int p,ll acc){
        acc=min(acc,t[node]);
        if(l==r) return acc;
        int mid=(l+r)/2;
        if(p<=mid) return qry(2*node,l,mid,p,acc);
        else return qry(2*node+1,mid+1,r,p,acc);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,M;
    while(cin>>N>>M){
        vector<array<ll,3>> edges(M); // a,b,w
        vector<vector<pair<int,int>>> adj(N+1); // (to, edgeIndex)
        for(int i=0;i<M;i++){
            ll a,b,w; cin>>a>>b>>w;
            edges[i]={a,b,w};
            adj[a].push_back({(int)b,i});
            adj[b].push_back({(int)a,i});
        }
        int S,T; cin>>S>>T;
        auto dijkstra=[&](int src, vector<ll>&dist, vector<int>&par, vector<int>&peIdx){
            dist.assign(N+1, INF); par.assign(N+1,-1); peIdx.assign(N+1,-1);
            priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
            dist[src]=0; pq.push({0,src});
            while(!pq.empty()){
                auto [du,u]=pq.top(); pq.pop();
                if(du>dist[u]) continue;
                for(auto [v,ei]:adj[u]){
                    ll nd=du+edges[ei][2];
                    if(nd<dist[v]){ dist[v]=nd; par[v]=u; peIdx[v]=ei; pq.push({nd,v}); }
                }
            }
        };
        vector<ll> dS,dT; vector<int> parS,peS,parT,peT;
        dijkstra(S,dS,parS,peS);
        dijkstra(T,dT,parT,peT);
        ll d = dS[T];
        if(d>=INF){ cout<<0<<"\n"; continue; }
        // recover path S..T via parS
        vector<int> path;
        for(int v=T; v!=-1; v=parS[v]) path.push_back(v);
        reverse(path.begin(), path.end()); // v0=S ... vL=T
        int L = (int)path.size()-1; // number of path edges
        vector<int> pos(N+1,-1);
        vector<char> onPath(N+1,0);
        for(int i=0;i<(int)path.size();i++){ pos[path[i]]=i; onPath[path[i]]=1; }
        // mark path edges (parent edge of each path vertex i>=1)
        vector<char> isPathEdge(M,0);
        for(int i=1;i<(int)path.size();i++){ int ei=peS[path[i]]; if(ei>=0) isPathEdge[ei]=1; }
        // build tree children from parS, BFS to compute anc[]
        vector<vector<int>> children(N+1);
        for(int v=1;v<=N;v++) if(v!=S && parS[v]!=-1) children[parS[v]].push_back(v);
        vector<int> anc(N+1,-1);
        // BFS from S
        {
            vector<int> q; q.reserve(N); q.push_back(S); anc[S]=0; // S is v0
            for(size_t h=0; h<q.size(); h++){
                int u=q[h];
                for(int c: children[u]){
                    anc[c] = onPath[c] ? pos[c] : anc[u];
                    q.push_back(c);
                }
            }
        }
        // segment tree over path edges 1..L
        if(L==0){ cout<<0<<"\n"; continue; }
        SegTree seg; seg.init(L);
        auto addCand=[&](int x,int y,ll c){
            if(dS[x]>=INF||dT[y]>=INF) return;
            int ax=anc[x], ay=anc[y];
            if(ax<0||ay<0) return;
            int lo=ax+1, hi=ay;
            if(lo>hi) return;
            ll val=dS[x]+c+dT[y];
            seg.upd(1,1,L,lo,hi,val);
        };
        for(int i=0;i<M;i++){
            if(isPathEdge[i]) continue;
            ll a=edges[i][0], b=edges[i][1], w=edges[i][2];
            addCand((int)a,(int)b,w);
            addCand((int)b,(int)a,w);
        }
        ll ans=0;
        for(int i=1;i<=L;i++){
            int vi=path[i];
            ll wi = edges[peS[vi]][2]; // weight of path edge i
            ll repl = seg.qry(1,1,L,i,INF); // shortest avoiding edge i (>=d) or INF
            ll increase;
            if(repl>=INF) increase = wi; // no bypass -> newDist=d+wi
            else increase = min(wi, repl - d);
            ans=max(ans, increase);
        }
        cout<<ans<<"\n";
    }
    return 0;
}
