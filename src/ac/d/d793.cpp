#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N, M;
            cin >> N >> M;
            int total = N * M;
            vector<int> cost(total);
            for (int i = 0; i < total; ++i) {
                cin >> cost[i];
            }
            
            vector<int> dist(total, 1e9);
            dist[0] = cost[0];
            
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
            pq.push({dist[0], 0});
            
            const int dr[] = {-1, 1, 0, 0};
            const int dc[] = {0, 0, -1, 1};
            
            int ans = -1;
            while (!pq.empty()) {
                int d = pq.top().first;
                int u = pq.top().second;
                pq.pop();
                
                if (d > dist[u]) continue;
                if (u == total - 1) {
                    ans = d;
                    break;
                }
                
                int r = u / M;
                int c = u % M;
                
                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                        int v = nr * M + nc;
                        int new_dist = d + cost[v];
                        if (new_dist < dist[v]) {
                            dist[v] = new_dist;
                            pq.emplace(new_dist, v);
                        }
                    }
                }
            }
            
            if (ans != -1) {
                cout << ans << "\n";
            } else {
                cout << dist[total - 1] << "\n";
            }
        }
    }
    
    return 0;
}
