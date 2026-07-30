#include <bits/stdc++.h>
using namespace std;

// Maximum Independent Set (max coins, no two adjacent taken), N <= 255.
// Direct branch-and-reduce:
//   * remove degree-0 vertices (always taken)
//   * pendant rule: degree-1 vertex always taken, drop it and its neighbour
//   * connected-component decomposition (solve pieces independently)
//   * branch on a max-degree vertex, with a greedy clique-cover upper bound
//     to prune the "exclude" branch.
// Returns the exact size of the maximum independent set.

static int N;
static bitset<256> adj[256];   // original graph adjacency

// greedy clique partition -> #cliques is an upper bound on the MIS size
static int cliqueCoverUB(bitset<256> rem){
    int cnt=0;
    while(rem.any()){
        cnt++;
        int v=rem._Find_first();
        bitset<256> cand = rem & adj[v];
        rem[v]=0;
        while(cand.any()){
            int u=cand._Find_first();
            rem[u]=0;
            cand &= adj[u];   // stay adjacent to every clique member
        }
    }
    return cnt;
}

// ---- bipartite matching (Kuhn) for a connected alive component ----
static bitset<256> B_alive;
static int matchR[256];
static bool vis[256];
static bool tryKuhn(int u){
    bitset<256> nb = adj[u] & B_alive;
    for(int v=nb._Find_first(); v<256; v=nb._Find_next(v)){
        if(vis[v]) continue;
        vis[v]=true;
        if(matchR[v]==-1 || tryKuhn(matchR[v])){
            matchR[v]=u; return true;
        }
    }
    return false;
}
// If 'comp' (a connected subgraph) is bipartite, return its MIS size via
// König's theorem (|V| - max matching); otherwise return -1.
static int bipartiteMIS(const bitset<256>& comp){
    static int color[256];
    for(int i=comp._Find_first(); i<256; i=comp._Find_next(i)) color[i]=-1;
    // BFS 2-coloring
    for(int s=comp._Find_first(); s<256; s=comp._Find_next(s)){
        if(color[s]!=-1) continue;
        color[s]=0;
        vector<int> q={s};
        for(size_t h=0; h<q.size(); ++h){
            int u=q[h];
            bitset<256> nb = adj[u]&comp;
            for(int v=nb._Find_first(); v<256; v=nb._Find_next(v)){
                if(color[v]==-1){ color[v]=color[u]^1; q.push_back(v); }
                else if(color[v]==color[u]) return -1; // odd cycle
            }
        }
    }
    B_alive = comp;
    for(int i=0;i<256;i++) matchR[i]=-1;
    int matching=0;
    for(int u=comp._Find_first(); u<256; u=comp._Find_next(u)){
        if(color[u]==0){
            for(int i=0;i<256;i++) vis[i]=false;
            if(tryKuhn(u)) matching++;
        }
    }
    return (int)comp.count() - matching;
}

static int solve(bitset<256> alive){
    int gained=0;
    // reduction loop
    for(;;){
        if(alive.none()) return gained;
        bool changed=false;
        int v1=-1; bitset<256> nb1;
        for(int i=alive._Find_first(); i<256; i=alive._Find_next(i)){
            bitset<256> nb = adj[i] & alive;
            size_t d = nb.count();
            if(d==0){ gained++; alive[i]=0; changed=true; break; }
            if(d==1 && v1==-1){ v1=i; nb1=nb; }
        }
        if(changed) continue;
        if(v1!=-1){ gained++; alive[v1]=0; alive &= ~nb1; continue; }
        break; // min degree >= 2
    }
    if(alive.none()) return gained;

    // connected component of the first alive vertex
    int seed=alive._Find_first();
    bitset<256> comp; comp[seed]=1;
    bitset<256> fr; fr[seed]=1;
    while(fr.any()){
        bitset<256> nx;
        for(int u=fr._Find_first(); u<256; u=fr._Find_next(u)) nx |= adj[u];
        nx &= alive; nx &= ~comp;
        comp |= nx; fr = nx;
    }
    if(comp != alive){
        bitset<256> rest = alive & ~comp;
        return gained + solve(comp) + solve(rest);
    }

    // connected, min degree >= 2: if bipartite, solve exactly via matching
    int bm = bipartiteMIS(alive);
    if(bm>=0) return gained + bm;

    // otherwise branch on max-degree vertex
    int v=-1; size_t md=0;
    for(int i=alive._Find_first(); i<256; i=alive._Find_next(i)){
        size_t d=(adj[i]&alive).count();
        if(d>md){ md=d; v=i; }
    }
    // include v
    bitset<256> a1 = alive; a1[v]=0; a1 &= ~adj[v];
    int best_local = 1 + solve(a1);
    // exclude v (with upper-bound pruning)
    bitset<256> a2 = alive; a2[v]=0;
    if(cliqueCoverUB(a2) > best_local){
        int exc = solve(a2);
        if(exc>best_local) best_local=exc;
    }
    return gained + best_local;
}

int main(){
    int n;
    while(scanf("%d",&n)==1){
        if(n<=0) break;
        N=n;
        for(int i=0;i<N;i++) adj[i].reset();
        int s,t;
        while(scanf("%d",&s)==1){
            if(s==0) break;
            if(scanf("%d",&t)!=1) break;
            if(t==0) break;
            int a=s-1,b=t-1;
            if(a>=0&&a<N&&b>=0&&b<N&&a!=b){ adj[a][b]=1; adj[b][a]=1; }
        }
        bitset<256> alive;
        for(int i=0;i<N;i++) alive[i]=1;
        printf("%d\n", solve(alive));
    }
    return 0;
}
