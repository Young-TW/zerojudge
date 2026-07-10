#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Dinic {
    struct Edge { int to, rev; long long cap; };
    int n;
    vector<vector<Edge>> g;
    vector<int> level, it;
    Dinic(int n): n(n), g(n), level(n), it(n) {}
    void addEdge(int from, int to, long long cap) {
        g[from].push_back({to, (int)g[to].size(), cap});
        g[to].push_back({from, (int)g[from].size()-1, 0});
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q; level[s]=0; q.push(s);
        while(!q.empty()) {
            int v=q.front(); q.pop();
            for(auto&e:g[v]) if(e.cap>0 && level[e.to]<0) {
                level[e.to]=level[v]+1; q.push(e.to);
            }
        }
        return level[t]>=0;
    }
    long long dfs(int v, int t, long long f) {
        if(v==t) return f;
        for(int&i=it[v]; i<(int)g[v].size(); i++) {
            Edge&e=g[v][i];
            if(e.cap>0 && level[v]<level[e.to]) {
                long long d=dfs(e.to, t, min(f, e.cap));
                if(d>0) { e.cap-=d; g[e.to][e.rev].cap+=d; return d; }
            }
        }
        return 0;
    }
    long long maxflow(int s, int t) {
        long long flow=0;
        while(bfs(s,t)) {
            fill(it.begin(), it.end(), 0);
            long long f;
            while((f=dfs(s,t,LLONG_MAX))>0) flow+=f;
        }
        return flow;
    }
};

int N, M, V;
vector<vector<int>> dep;
vector<int> sccid, low, idx_;
vector<int> stk;
vector<char> onstk;
int timer_, sccnt;

void tarjan(int start) {
    struct Frame { int u, ci; };
    vector<Frame> callstk;
    idx_[start]=low[start]=timer_++;
    stk.push_back(start); onstk[start]=1;
    callstk.push_back({start,0});
    while(!callstk.empty()) {
        int u = callstk.back().u;
        int& ci = callstk.back().ci;
        if(ci < (int)dep[u].size()) {
            int v = dep[u][ci++];
            if(idx_[v]==-1) {
                idx_[v]=low[v]=timer_++;
                stk.push_back(v); onstk[v]=1;
                callstk.push_back({v,0});
            } else if(onstk[v]) {
                low[u]=min(low[u], idx_[v]);
            }
        } else {
            if(low[u]==idx_[u]) {
                while(true) {
                    int w=stk.back(); stk.pop_back(); onstk[w]=0;
                    sccid[w]=sccnt;
                    if(w==u) break;
                }
                sccnt++;
            }
            int finishedLow = low[u];
            callstk.pop_back();
            if(!callstk.empty()) {
                int p = callstk.back().u;
                low[p]=min(low[p], finishedLow);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while(cin >> N >> M) {
        V = N*M;
        dep.assign(V, {});
        vector<long long> score(V);
        for(int r=0;r<N;r++) for(int c=0;c<M;c++) {
            int id=r*M+c;
            cin >> score[id];
            int w; cin >> w;
            for(int k=0;k<w;k++) {
                int rr,cc; cin >> rr >> cc;
                dep[rr*M+cc].push_back(id);
            }
        }
        for(int r=0;r<N;r++) for(int c=0;c<M-1;c++) dep[r*M+c].push_back(r*M+c+1);
        sccid.assign(V,-1); low.assign(V,0); idx_.assign(V,-1);
        stk.clear(); onstk.assign(V,0); timer_=0; sccnt=0;
        for(int i=0;i<V;i++) if(idx_[i]==-1) tarjan(i);
        vector<int> compSize(sccnt,0);
        vector<bool> compCyclic(sccnt,false);
        for(int u=0;u<V;u++){
            compSize[sccid[u]]++;
            for(int v:dep[u]) if(v==u){ compCyclic[sccid[u]]=true; break; }
        }
        for(int c=0;c<sccnt;c++) if(compSize[c]>1) compCyclic[c]=true;
        vector<vector<int>> cadj(sccnt);
        for(int u=0;u<V;u++) for(int v:dep[u]) if(sccid[u]!=sccid[v]) cadj[sccid[u]].push_back(sccid[v]);
        vector<bool> compDead(sccnt,false);
        for(int c=0;c<sccnt;c++) compDead[c]=compCyclic[c];
        for(int c=0;c<sccnt;c++) for(int d:cadj[c]) if(compDead[d]) compDead[c]=true;
        vector<bool> dead(V,false);
        for(int u=0;u<V;u++) dead[u]=compDead[sccid[u]];
        int S=V, T=V+1;
        Dinic dinic(V+2);
        const long long INF = (long long)1e18;
        long long sumPos=0;
        for(int u=0;u<V;u++){
            if(dead[u]) continue;
            if(score[u]>0){ dinic.addEdge(S,u,score[u]); sumPos+=score[u]; }
            else if(score[u]<0){ dinic.addEdge(u,T,-score[u]); }
        }
        for(int u=0;u<V;u++){
            if(dead[u]) continue;
            for(int v:dep[u]){
                if(dead[v]) continue;
                dinic.addEdge(u,v,INF);
            }
        }
        long long mf = dinic.maxflow(S,T);
        cout << (sumPos - mf) << "\n";
    }
    return 0;
}
