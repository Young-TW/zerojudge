#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point {
    long long x, y;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<Point> points(N);
        for (int i = 0; i < N; ++i) {
            cin >> points[i].x >> points[i].y;
        }
        
        vector<vector<double>> dist(N, vector<double>(N, 0.0));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                long long dx = points[i].x - points[j].x;
                long long dy = points[i].y - points[j].y;
                dist[i][j] = sqrt(dx * dx + dy * dy);
            }
        }
        
        int M;
        cin >> M;
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            --u; --v;
            dist[u][v] = 0.0;
            dist[v][u] = 0.0;
        }
        
        vector<double> min_dist(N, 1e18);
        vector<bool> visited(N, false);
        
        double total_length = 0.0;
        min_dist[0] = 0.0;
        
        for (int i = 0; i < N; ++i) {
            int u = -1;
            for (int j = 0; j < N; ++j) {
                if (!visited[j] && (u == -1 || min_dist[j] < min_dist[u])) {
                    u = j;
                }
            }
            
            visited[u] = true;
            total_length += min_dist[u];
            
            for (int v = 0; v < N; ++v) {
                if (!visited[v]) {
                    if (dist[u][v] < min_dist[v]) {
                        min_dist[v] = dist[u][v];
                    }
                }
            }
        }
        
        cout << fixed << setprecision(2) << total_length << "\n";
    }
    return 0;
}
