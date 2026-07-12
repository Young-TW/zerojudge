#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if(!(cin>>n)) return 0;
    vector<vector<int>> g(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    if(n<=1){
        cout<<0<<"\n";
        return 0;
    }
    auto bfs=[&](int s)->pair<int,int>{
        vector<int> dist(n,-1);
        queue<int> q;
        q.push(s);
        dist[s]=0;
        int far=s, fd=0;
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(size_t i=0;i<g[u].size();i++){
                int v=g[u][i];
                if(dist[v]==-1){
                    dist[v]=dist[u]+1;
                    if(dist[v]>fd){ fd=dist[v]; far=v; }
                    q.push(v);
                }
            }
        }
        return make_pair(far,fd);
    };
    pair<int,int> p=bfs(0);
    pair<int,int> r=bfs(p.first);
    cout<<r.second<<"\n";
    return 0;
}
