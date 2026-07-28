#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // edge list: (u,v) for edges 1..30
    const pair<int,int> e[30] = {
        {1,2},{1,3},{1,4},{1,5},{1,6},
        {2,3},{3,4},{4,5},{5,6},{6,2},
        {2,9},{2,8},{3,8},{3,7},
        {7,4},{11,4},
        {5,11},{5,10},{6,10},{6,9},
        {7,8},{8,9},{9,10},{10,11},
        {11,7},
        {7,12},{8,12},{9,12},{10,12},{11,12}
    };
    int S,T;
    while (cin>>S>>T){
        long long w[30];
        for(int i=0;i<30;i++) cin>>w[i];
        vector<pair<int,long long>> g[13];
        for(int i=0;i<30;i++){
            int u=e[i].first, v=e[i].second;
            g[u].push_back({v,w[i]});
            g[v].push_back({u,w[i]});
        }
        const long long INF = (1LL<<60);
        long long dist[13];
        fill(dist,dist+13,INF);
        dist[S]=0;
        using P=pair<long long,int>;
        priority_queue<P,vector<P>,greater<P>> pq;
        pq.push({0,S});
        while(!pq.empty()){
            auto [d,u]=pq.top(); pq.pop();
            if(d!=dist[u]) continue;
            if(u==T) break;
            for(auto [v,c]:g[u]){
                if(dist[v]>d+c){
                    dist[v]=d+c;
                    pq.push({dist[v],v});
                }
            }
        }
        cout<<dist[T]<<"\n";
    }
    return 0;
}
