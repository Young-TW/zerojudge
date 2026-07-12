#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
int dist[201][201];
int ans[201];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        
        int cap[3] = {a, b, c};
        memset(dist, 0x3f, sizeof(dist));
        memset(ans, 0x3f, sizeof(ans));
        
        priority_queue<pair<int, pair<int, int>>, 
                       vector<pair<int, pair<int, int>>>, 
                       greater<pair<int, pair<int, int>>>> pq;
        
        dist[0][0] = 0;
        pq.push({0, {0, 0}});
        
        while (!pq.empty()) {
            auto curr = pq.top();
            pq.pop();
            
            int cost = curr.first;
            int x = curr.second.first;
            int y = curr.second.second;
            int z = c - x - y;
            
            if (cost > dist[x][y]) continue;
            
            if (cost < ans[x]) ans[x] = cost;
            if (cost < ans[y]) ans[y] = cost;
            if (cost < ans[z]) ans[z] = cost;
            
            int w[3] = {x, y, z};
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (i == j) continue;
                    int pour = min(w[i], cap[j] - w[j]);
                    if (pour > 0) {
                        int nw[3] = {w[0], w[1], w[2]};
                        nw[i] -= pour;
                        nw[j] += pour;
                        int ncost = cost + pour;
                        if (ncost < dist[nw[0]][nw[1]]) {
                            dist[nw[0]][nw[1]] = ncost;
                            pq.push({ncost, {nw[0], nw[1]}});
                        }
                    }
                }
            }
        }
        
        for (int i = d; i >= 0; --i) {
            if (ans[i] != INF) {
                cout << ans[i] << " " << i << "\n";
                break;
            }
        }
    }
    
    return 0;
}
