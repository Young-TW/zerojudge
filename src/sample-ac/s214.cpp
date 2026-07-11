#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

struct Node {
    int time;
    int species;
    int x;
    int y;
    bool operator>(const Node& other) const {
        if (time != other.time) return time > other.time;
        if (species != other.species) return species > other.species;
        if (x != other.x) return x > other.x;
        return y > other.y;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M, K, T;
    while (cin >> N >> M >> K >> T) {
        const int INF = 1e9;
        vector<vector<int>> dist(N, vector<int>(M, INF));
        vector<vector<int>> species(N, vector<int>(M, 0));
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                int v;
                cin >> v;
                if (v == -1) {
                    dist[i][j] = -1; // obstacle
                } else if (v > 0) {
                    dist[i][j] = 0;
                    species[i][j] = v;
                    pq.push({0, v, i, j});
                }
            }
        }
        
        const int dx[4] = {-1, 1, 0, 0};
        const int dy[4] = {0, 0, -1, 1};
        
        while (!pq.empty()) {
            Node cur = pq.top();
            pq.pop();
            int t = cur.time;
            int sp = cur.species;
            int x = cur.x;
            int y = cur.y;
            
            // Outdated entry
            if (t > dist[x][y]) continue;
            if (t == dist[x][y] && sp > species[x][y]) continue;
            
            for (int dir = 0; dir < 4; ++dir) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
                if (dist[nx][ny] == -1) continue; // obstacle
                
                int nt = t + 1;
                if (nt > T) continue; // no need to expand beyond T
                
                if (nt < dist[nx][ny] || (nt == dist[nx][ny] && sp < species[nx][ny])) {
                    dist[nx][ny] = nt;
                    species[nx][ny] = sp;
                    pq.push({nt, sp, nx, ny});
                }
            }
        }
        
        vector<int> count(K + 1, 0);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (dist[i][j] != -1 && dist[i][j] <= T && species[i][j] > 0) {
                    count[species[i][j]]++;
                }
            }
        }
        
        for (int i = 1; i <= K; ++i) {
            if (i > 1) cout << ' ';
            cout << count[i];
        }
        cout << '\n';
    }
    
    return 0;
}
