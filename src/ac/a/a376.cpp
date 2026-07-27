#include <bits/stdc++.h>
using namespace std;

/*
 NOI2011 "Tutu and Dandan" game (ZeroJudge a376)

 Model: empty cell is a token. Tutu (first) slides an adjacent WHITE 'O' into
 empty; Dandan slides an adjacent BLACK 'X'. Loser cannot move.

 Checkerboard-color cells by (i+j)&1. Let q0 = parity of INITIAL empty (parity
 at which Tutu always moves). A piece cell is "traversable" iff
    (parity == 1-q0 and color=='O')  or  (parity == q0 and color=='X').
 Non-traversable pieces can never move -> walls (excluded from graph H).
 H = traversable cells + the current empty cell (as a token vertex), grid edges.

 Theorem (token game <-> matching): the player to move wins iff the empty
 (token) vertex is essential (contained in every maximum matching of H), i.e.
 removing it decreases the maximum matching size.

 Key invariant: each move freezes the vacated-into cell (former empty becomes a
 wall) and the current empty walks to the source cell (already a traversable
 vertex). So H only ever loses the previous empty vertex:  H_t = H_0 - {E_0..E_{t-1}}.
 Maintain one maximum matching incrementally under vertex deletions.
*/

static int n, m, N;
static vector<vector<int>> adj;
static vector<int> matchOf;      // matched partner id or -1
static vector<char> deleted;     // vertex removed from H
static vector<int> vis;          // timestamp
static int visTok = 0;
static int excludeV = -1;        // vertex to treat as removed during a test

// generic augment (mutating): find augmenting path from free vertex a
bool augment(int a){
    for(int b: adj[a]){
        if(deleted[b] || b==excludeV) continue;
        if(vis[b]==visTok) continue;
        vis[b]=visTok;
        if(matchOf[b]==-1 || augment(matchOf[b])){
            matchOf[a]=b; matchOf[b]=a; return true;
        }
    }
    return false;
}

// read-only existence of augmenting path from free vertex a
bool augmentRead(int a){
    for(int b: adj[a]){
        if(deleted[b] || b==excludeV) continue;
        if(vis[b]==visTok) continue;
        vis[b]=visTok;
        if(matchOf[b]==-1) return true;
        if(augmentRead(matchOf[b])) return true;
    }
    return false;
}

// is vertex v essential (in every maximum matching)?
bool essential(int v){
    if(matchOf[v]==-1) return false;           // avoidable -> mover loses
    int u = matchOf[v];
    matchOf[v]=-1; matchOf[u]=-1;               // temporarily free v and u
    excludeV = v;
    visTok++;
    vis[v]=visTok;                              // never enter v
    bool aug = augmentRead(u);                  // can u be rematched avoiding v?
    excludeV = -1;
    matchOf[v]=u; matchOf[u]=v;                 // restore matching
    return !aug;                                // essential iff cannot avoid v
}

// permanently delete vertex x, keep matching maximum
void deleteVertex(int x){
    deleted[x]=true;
    int y = matchOf[x];
    if(y!=-1){
        matchOf[x]=-1; matchOf[y]=-1;
        visTok++;
        augment(y);   // repair with one augmenting path if possible
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> outBlocks;
    while(cin >> n >> m){
        N = n*m;
        vector<string> g(n);
        for(int i=0;i<n;i++) cin >> g[i];
        int k; cin >> k;
        vector<pair<int,int>> ops(2*k);
        for(int i=0;i<2*k;i++){ int x,y; cin>>x>>y; ops[i]={x-1,y-1}; }

        // initial empty
        int er=-1,ec=-1;
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) if(g[i][j]=='.'){er=i;ec=j;}
        int q0 = (er+ec)&1;

        auto id=[&](int i,int j){return i*m+j;};
        adj.assign(N,{});
        matchOf.assign(N,-1);
        deleted.assign(N,true);   // default: not in H
        vis.assign(N,0);
        visTok=0; excludeV=-1;

        // determine inH: traversable pieces + the initial empty
        vector<char> inH(N,false);
        for(int i=0;i<n;i++) for(int j=0;j<m;j++){
            int p=(i+j)&1; char c=g[i][j];
            bool trav=false;
            if(c=='.') trav = (i==er && j==ec); // only initial empty
            else if(p==(1-q0) && c=='O') trav=true;
            else if(p==q0 && c=='X') trav=true;
            inH[id(i,j)] = trav;
        }
        for(int i=0;i<N;i++) deleted[i] = !inH[i];

        // build adjacency among inH cells
        int dx[4]={-1,1,0,0}, dy[4]={0,0,-1,1};
        for(int i=0;i<n;i++) for(int j=0;j<m;j++){
            int u=id(i,j); if(!inH[u]) continue;
            for(int d=0;d<4;d++){
                int ni=i+dx[d], nj=j+dy[d];
                if(ni<0||ni>=n||nj<0||nj>=m) continue;
                int v=id(ni,nj); if(inH[v]) adj[u].push_back(v);
            }
        }

        // initial maximum matching (Kuhn over left = parity 0)
        for(int i=0;i<n;i++) for(int j=0;j<m;j++){
            int u=id(i,j);
            if(inH[u] && ((i+j)&1)==0 && matchOf[u]==-1){
                visTok++;
                augment(u);
            }
        }

        // walk the game. token E_0 = initial empty. E_i = source of op i.
        vector<int> emptySeq; emptySeq.push_back(id(er,ec));
        for(int i=0;i<2*k;i++) emptySeq.push_back(id(ops[i].first,ops[i].second));

        // ess[t] = essential(E_t) tested before move t+1
        vector<char> ess(2*k, 0);
        for(int i=1;i<=2*k;i++){
            int token = emptySeq[i-1];
            ess[i-1] = essential(token) ? 1 : 0;
            deleteVertex(token);
        }

        // Tutu op j (game move 2j-1): before=ess[2j-2], after=ess[2j-1]
        vector<int> mistakes;
        for(int j=1;j<=k;j++){
            bool before = ess[2*j-2];
            bool after  = ess[2*j-1];
            if(before && after) mistakes.push_back(j);
        }

        string blk = to_string((int)mistakes.size());
        for(int v: mistakes){ blk.push_back('\n'); blk += to_string(v); }
        outBlocks.push_back(blk);
    }
    for(size_t i=0;i<outBlocks.size();i++){
        if(i) cout << "\n\n";
        cout << outBlocks[i];
    }
    cout << "\n";
    return 0;
}
