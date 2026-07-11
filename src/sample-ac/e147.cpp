#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, k;
    while(cin >> n >> m >> k){
        // node index: city*2 + parity (parity = number of magic edges traversed mod 2)
        // state 0: magic edges in original direction
        // state 1: magic edges reversed
        vector<vector<pair<int,long long>>> adj(2*n);
        for(int i=0;i<m;i++){
            int u,v; long long w;
            cin >> u >> v >> w;
            u--; v--;
            adj[u*2+0].push_back(make_pair(v*2+0, w));
            adj[u*2+1].push_back(make_pair(v*2+1, w));
        }
        for(int i=0;i<k;i++){
            int u,v; long long w;
            cin >> u >> v >> w;
            u--; v--;
            // state 0: original direction u->v, flip to state 1
            adj[u*2+0].push_back(make_pair(v*2+1, w));
            // state 1: reversed direction v->u, flip to state 0
            adj[v*2+1].push_back(make_pair(u*2+0, w));
        }
        int s,t;
        cin >> s >> t;
        s--; t--;
        vector<long long> dist(2*n, LLONG_MAX);
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
        dist[s*2+0] = 0;
        pq.push(make_pair(0LL, s*2+0));
        while(!pq.empty()){
            pair<long long,int> top = pq.top(); pq.pop();
            long long d = top.first;
            int u = top.second;
            if(d > dist[u]) continue;
            for(size_t i=0;i<adj[u].size();i++){
                int to = adj[u][i].first;
                long long w = adj[u][i].second;
                if(dist[u] + w < dist[to]){
                    dist[to] = dist[u] + w;
                    pq.push(make_pair(dist[to], to));
                }
            }
        }
        long long ans = min(dist[t*2+0], dist[t*2+1]);
        if(ans == LLONG_MAX) cout << "QAQ" << "\n";
        else cout << ans << "\n";
    }
    return 0;
}
