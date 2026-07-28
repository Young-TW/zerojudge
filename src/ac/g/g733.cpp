#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll INF = (ll)4e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M, K;
    while (cin >> N >> M >> K) {
        vector<vector<pair<int,ll>>> road(N);
        vector<vector<pair<int,ll>>> rail(N);
        
        for (int i = 0; i < M; ++i) {
            int a, b; ll c;
            cin >> a >> b >> c;
            road[a].push_back(make_pair(b, c));
            road[b].push_back(make_pair(a, c));
        }
        for (int i = 0; i < K; ++i) {
            int a, b; ll c;
            cin >> a >> b >> c;
            rail[a].push_back(make_pair(b, c));
            rail[b].push_back(make_pair(a, c));
        }
        
        int s, t;
        cin >> s >> t;
        
        // mode 0: road, not switched
        // mode 1: rail, not switched
        // mode 2: road, already switched (from rail)
        // mode 3: rail, already switched (from road)
        vector<vector<ll>> dist(N, vector<ll>(4, INF));
        priority_queue<pair<ll, pair<int,int>>, vector<pair<ll, pair<int,int>>>, greater<pair<ll, pair<int,int>>>> pq;
        
        dist[s][0] = 0;
        dist[s][1] = 0;
        pq.push(make_pair(0LL, make_pair(s, 0)));
        pq.push(make_pair(0LL, make_pair(s, 1)));
        
        while (!pq.empty()) {
            pair<ll, pair<int,int>> top = pq.top(); pq.pop();
            ll d = top.first;
            int u = top.second.first;
            int mode = top.second.second;
            
            if (d != dist[u][mode]) continue;
            
            // Road edges
            for (size_t i = 0; i < road[u].size(); ++i) {
                int v = road[u][i].first;
                ll w = road[u][i].second;
                int newMode;
                if (mode == 0) newMode = 0;      // road -> road
                else if (mode == 1) newMode = 2;  // rail -> road (switch)
                else if (mode == 2) newMode = 2;  // road(switched) -> road
                else continue;                     // mode == 3: can't use road
                
                if (dist[v][newMode] > d + w) {
                    dist[v][newMode] = d + w;
                    pq.push(make_pair(dist[v][newMode], make_pair(v, newMode)));
                }
            }
            
            // Rail edges
            for (size_t i = 0; i < rail[u].size(); ++i) {
                int v = rail[u][i].first;
                ll w = rail[u][i].second;
                int newMode;
                if (mode == 0) newMode = 3;      // road -> rail (switch)
                else if (mode == 1) newMode = 1;  // rail -> rail
                else if (mode == 3) newMode = 3;  // rail(switched) -> rail
                else continue;                     // mode == 2: can't use rail
                
                if (dist[v][newMode] > d + w) {
                    dist[v][newMode] = d + w;
                    pq.push(make_pair(dist[v][newMode], make_pair(v, newMode)));
                }
            }
        }
        
        ll ans = min(min(dist[t][0], dist[t][1]), min(dist[t][2], dist[t][3]));
        cout << ans << "\n";
    }
    
    return 0;
}
