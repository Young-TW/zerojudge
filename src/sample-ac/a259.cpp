#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <iostream>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while(cin >> N){
        if(N==0) break;
        int M;
        cin >> M;
        vector<vector<pair<int,long long>>> adj(N+1);
        for(int i=0;i<M;i++){
            int a,b; long long d;
            cin >> a >> b >> d;
            adj[a].push_back({b,d});
            adj[b].push_back({a,d});
        }
        const long long INF = LLONG_MAX;
        vector<long long> dist(N+1, INF);
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
        dist[2]=0;
        pq.push({0,2});
        while(!pq.empty()){
            auto [d,u]=pq.top(); pq.pop();
            if(d>dist[u]) continue;
            for(auto &e:adj[u]){
                int v=e.first; long long w=e.second;
                if(dist[v]>d+w){
                    dist[v]=d+w;
                    pq.push({dist[v],v});
                }
            }
        }
        vector<pair<long long,int>> order;
        for(int i=1;i<=N;i++) if(dist[i]<INF) order.push_back({dist[i],i});
        sort(order.begin(),order.end());
        vector<long long> cnt(N+1,0);
        cnt[2]=1;
        for(auto &pr:order){
            long long du=pr.first; int u=pr.second;
            for(auto &e:adj[u]){
                int v=e.first;
                if(dist[v]<du){
                    cnt[u]+=cnt[v];
                }
            }
        }
        cout << cnt[1] << "\n";
    }
    return 0;
}
