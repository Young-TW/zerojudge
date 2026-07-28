#include <bits/stdc++.h>
using namespace std;
int main(){
    int N,M,T;
    scanf("%d%d%d",&N,&M,&T);
    vector<int> c(N+1);
    for(int i=1;i<=N;i++) scanf("%d",&c[i]);
    vector<vector<pair<int,int>>> adj(N+1);
    for(int i=0;i<M;i++){
        int a,b,t;
        scanf("%d%d%d",&a,&b,&t);
        adj[a].push_back(make_pair(b,t));
        adj[b].push_back(make_pair(a,t));
    }
    const long long INF=LLONG_MAX;
    vector<long long> dist(N+1,INF);
    dist[1]=0;
    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> pq;
    pq.push(make_pair(0LL,1));
    while(!pq.empty()){
        pair<long long,int> tp=pq.top(); pq.pop();
        long long d=tp.first; int u=tp.second;
        if(d>dist[u]) continue;
        for(size_t i=0;i<adj[u].size();i++){
            int v=adj[u][i].first,w=adj[u][i].second;
            if(dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
                pq.push(make_pair(dist[v],v));
            }
        }
    }
    // Lex-smallest path: next-hop is smallest-id valid neighbor.
    // (path(u1) vs path(u2) differ first at u1 vs u2, so min id wins)
    vector<int> nh(N+1,0);
    for(int v=2;v<=N;v++){
        int best=INT_MAX;
        for(size_t i=0;i<adj[v].size();i++){
            int u=adj[v][i].first,w=adj[v][i].second;
            if(dist[u]+w==dist[v]&&u<best) best=u;
        }
        nh[v]=best;
    }
    // Count cows passing through each node (process far-to-near).
    vector<int> ord(N-1);
    iota(ord.begin(),ord.end(),2);
    sort(ord.begin(),ord.end(),[&](int a,int b){return dist[a]>dist[b];});
    vector<long long> cnt(N+1);
    for(int i=1;i<=N;i++) cnt[i]=c[i];
    for(size_t i=0;i<ord.size();i++){
        int v=ord[i];
        if(nh[v]>0) cnt[nh[v]]+=cnt[v];
    }
    long long ans=0;
    for(int X=2;X<=N;X++){
        if(dist[X]>T) ans=max(ans,cnt[X]*(dist[X]-T));
    }
    printf("%lld\n",ans);
    return 0;
}
