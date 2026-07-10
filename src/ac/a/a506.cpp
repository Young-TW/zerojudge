#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

// Standard Edmonds blossom (BFS + union-find-style blossom contraction).
struct Blossom {
    int n;
    vector<vector<int>> adj;
    Blossom(int n): n(n), adj(n) {}
    void add_edge(int u, int v){
        if(u==v) return;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> p, mate, base;
    vector<bool> used, blossom;

    void mark_path(int v, int b, int child){
        for(; base[v]!=b; ){
            blossom[base[v]] = blossom[base[p[v]]] = true;
            p[v] = child;
            child = mate[v];
            v = base[p[v]];
        }
    }
    int lca(int a, int b){
        vector<bool> mark(n, false);
        for(;;){
            a = base[a]; mark[a]=true;
            if(mate[a]==-1) break;
            a = base[p[mate[a]]];
        }
        for(;;){
            b = base[b];
            if(mark[b]) return b;
            b = base[p[mate[b]]];
        }
    }
    int find_path(int root){
        p.assign(n,-1); used.assign(n,false);
        base.resize(n);
        for(int i=0;i<n;i++) base[i]=i;
        queue<int> q; q.push(root); used[root]=true;
        while(!q.empty()){
            int v=q.front(); q.pop();
            for(int to: adj[v]){
                if(base[v]==base[to] || mate[v]==to) continue;
                if(to==root || (mate[to]!=-1 && p[mate[to]]!=-1)){
                    int curbase = lca(v,to);
                    blossom.assign(n,false);
                    mark_path(v,curbase,to);
                    mark_path(to,curbase,v);
                    for(int i=0;i<n;i++){
                        if(blossom[base[i]]){
                            base[i]=curbase;
                            if(!used[i]){ used[i]=true; q.push(i); }
                        }
                    }
                } else if(p[to]==-1){
                    p[to]=v;
                    if(mate[to]==-1) return to;
                    to = mate[to]; used[to]=true; q.push(to);
                }
            }
        }
        return -1;
    }
    vector<int> max_matching(){
        mate.assign(n,-1);
        for(int i=0;i<n;i++){
            if(mate[i]==-1){
                int v=find_path(i);
                while(v!=-1){
                    int u=p[v]; int pp=mate[u];
                    mate[v]=u; mate[u]=v; v=pp;
                }
            }
        }
        return mate;
    }
};

int main(){
    int T;
    if(!(cin>>T)) return 0;
    while(T--){
        int N,M; cin>>N>>M;
        vector<string> grid(N);
        for(int i=0;i<N;i++) cin>>grid[i];
        vector<vector<int>> id(N, vector<int>(M,-1));
        int K=-1, cnt=0;
        for(int i=0;i<N;i++) for(int j=0;j<M;j++){
            if(grid[i][j]=='K'){ id[i][j]=cnt; K=cnt; cnt++; }
            else if(grid[i][j]=='.'){ id[i][j]=cnt; cnt++; }
        }
        int di[8]={-1,-1,-1,0,0,1,1,1};
        int dj[8]={-1,0,1,-1,1,-1,0,1};
        Blossom b(cnt);
        for(int i=0;i<N;i++) for(int j=0;j<M;j++){
            if(id[i][j]<0) continue;
            for(int d=0;d<8;d++){
                int ni=i+di[d], nj=j+dj[d];
                if(ni<0||ni>=N||nj<0||nj>=M) continue;
                if(id[ni][nj]<0) continue;
                if(id[i][j]<id[ni][nj]) b.add_edge(id[i][j],id[ni][nj]);
            }
        }
        vector<int> mate = b.max_matching();
        int mg=0; for(int i=0;i<cnt;i++) if(mate[i]!=-1 && i<mate[i]) mg++;
        Blossom bk(cnt);
        for(int i=0;i<N;i++) for(int j=0;j<M;j++){
            if(id[i][j]<0 || id[i][j]==K) continue;
            for(int d=0;d<8;d++){
                int ni=i+di[d], nj=j+dj[d];
                if(ni<0||ni>=N||nj<0||nj>=M) continue;
                if(id[ni][nj]<0 || id[ni][nj]==K) continue;
                if(id[i][j]<id[ni][nj]) bk.add_edge(id[i][j],id[ni][nj]);
            }
        }
        vector<int> matek = bk.max_matching();
        int mgk=0; for(int i=0;i<cnt;i++) if(matek[i]!=-1 && i<matek[i]) mgk++;
        if(mg > mgk) cout<<"Ting\n";
        else cout<<"Wen\n";
    }
    return 0;
}
