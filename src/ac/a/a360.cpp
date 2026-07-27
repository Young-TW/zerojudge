#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, M;
vector<int> treeAdj[1005];
int par[1005], depthv[1005], myIdx[1005]; // myIdx: index among parent's children
vector<int> childList[1005];
ll best_full[1005], dpv[1005];
vector<ll> best_excl[1005]; // per child position

struct Extra { int a, b, c; };

int lca(int u, int v){
    while(depthv[u] > depthv[v]) u = par[u];
    while(depthv[v] > depthv[u]) v = par[v];
    while(u != v){ u = par[u]; v = par[v]; }
    return u;
}

int main(){
    while(scanf("%d %d", &N, &M) == 2){
        for(int i=1;i<=N;i++){ treeAdj[i].clear(); childList[i].clear(); best_excl[i].clear(); }
        vector<Extra> extras;
        ll totalC = 0;
        vector<array<int,3>> edges(M);
        for(int i=0;i<M;i++){
            int a,b,c; scanf("%d %d %d",&a,&b,&c);
            edges[i]={a,b,c};
            if(c==0){ treeAdj[a].push_back(b); treeAdj[b].push_back(a); }
            else { extras.push_back({a,b,c}); totalC += c; }
        }
        // root at 1, BFS
        vector<int> order; order.reserve(N);
        vector<char> vis(N+1,0);
        queue<int>q; q.push(1); vis[1]=1; par[1]=0; depthv[1]=0;
        while(!q.empty()){
            int u=q.front(); q.pop(); order.push_back(u);
            for(int w: treeAdj[u]) if(!vis[w]){ vis[w]=1; par[w]=u; depthv[w]=depthv[u]+1; q.push(w); }
        }
        // build children lists
        for(int u=1;u<=N;u++){
            for(int w: treeAdj[u]) if(w!=par[u]){ myIdx[w]=childList[u].size(); childList[u].push_back(w); }
        }
        // candidate paths bucketed by LCA
        vector<vector<int>> bucket(N+1); // indices into cand
        struct Cand{ int a,b,c,l; };
        vector<Cand> cand;
        for(auto&e:extras){
            int l=lca(e.a,e.b);
            int dist=depthv[e.a]+depthv[e.b]-2*depthv[l];
            if(dist%2==0){ // even tree path -> odd cycle -> keepable candidate
                bucket[l].push_back(cand.size());
                cand.push_back({e.a,e.b,e.c,l});
            }
        }
        // process in reverse BFS order (descendants before ancestors)
        for(int oi=(int)order.size()-1; oi>=0; oi--){
            int v=order[oi];
            int k=childList[v].size();
            int full=(1<<k)-1;
            // build items: best profit per child-mask (size 1 or 2)
            // legDelta lambda: returns pair(childPos or -1, delta)
            auto legDelta=[&](int endpoint)->pair<int,ll>{
                if(endpoint==v) return {-1, 0LL};
                int cur=endpoint; ll delta=0;
                while(par[cur]!=v){ int p=par[cur]; delta += best_excl[p][myIdx[cur]] - best_full[p]; cur=p; }
                return { myIdx[cur], delta };
            };
            // map mask -> best weight
            unordered_map<int,ll> maskBest;
            for(int idx: bucket[v]){
                Cand&cd=cand[idx];
                auto pa=legDelta(cd.a);
                auto pb=legDelta(cd.b);
                int mask=0; ll prof=cd.c;
                if(pa.first>=0){ mask|=(1<<pa.first); prof+=pa.second; }
                if(pb.first>=0){ mask|=(1<<pb.first); prof+=pb.second; }
                // if both endpoints resolve to same child pos -> invalid (would be same edge) shouldn't happen for valid path
                if(mask==0) continue; // degenerate, skip
                auto it=maskBest.find(mask);
                if(it==maskBest.end()||it->second<prof) maskBest[mask]=prof;
            }
            vector<pair<int,ll>> items(maskBest.begin(), maskBest.end());
            // bitmask DP
            vector<ll> dpm(full+1, 0);
            for(int mask=1; mask<=full; mask++){
                int b = mask & (-mask);
                int bl = __builtin_ctz(b);
                ll best = dpm[mask ^ b]; // child bl unused
                for(auto&it: items){
                    int im=it.first;
                    if((im & (1<<bl)) && (im & mask)==im){
                        ll cand2 = it.second + dpm[mask ^ im];
                        if(cand2>best) best=cand2;
                    }
                }
                dpm[mask]=best;
            }
            best_full[v]=dpm[full];
            best_excl[v].assign(k,0);
            for(int p=0;p<k;p++) best_excl[v][p]=dpm[full ^ (1<<p)];
            ll s=best_full[v];
            for(int cpos=0;cpos<k;cpos++) s+=dpv[childList[v][cpos]];
            dpv[v]=s;
        }
        printf("%lld\n", totalC - dpv[1]);
    }
    return 0;
}
