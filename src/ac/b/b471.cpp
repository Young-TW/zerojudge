#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, q;
    while (cin >> n >> m >> q) {
        vector<vector<int>> grid(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> grid[i][j];
            }
        }
        
        vector<vector<int>> id(n, vector<int>(m, -1));
        vector<pair<int, int>> cells;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) {
                    id[i][j] = cells.size();
                    cells.emplace_back(i, j);
                }
            }
        }
        int K = cells.size();
        
        vector<vector<int>> adj(K);
        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};
        for (int idx = 0; idx < K; ++idx) {
            int r = cells[idx].first;
            int c = cells[idx].second;
            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && id[nr][nc] != -1) {
                    adj[idx].push_back(id[nr][nc]);
                }
            }
        }
        
        vector<int> dist(K * K);
        for (int i = 0; i < q; ++i) {
            int EX, EY, SX, SY, TX, TY;
            cin >> EX >> EY >> SX >> SY >> TX >> TY;
            --EX; --EY; --SX; --SY; --TX; --TY;
            
            if (EX < 0 || EX >= n || EY < 0 || EY >= m ||
                SX < 0 || SX >= n || SY < 0 || SY >= m ||
                TX < 0 || TX >= n || TY < 0 || TY >= m ||
                id[EX][EY] == -1 || id[SX][SY] == -1 || id[TX][TY] == -1) {
                cout << -1 << '\n';
                continue;
            }
            
            int e_start = id[EX][EY];
            int s_start = id[SX][SY];
            int t_goal = id[TX][TY];
            
            if (s_start == t_goal) {
                cout << 0 << '\n';
                continue;
            }
            
            fill(dist.begin(), dist.end(), -1);
            auto encode = [K](int e, int t) { return e * K + t; };
            
            queue<pair<int, int>> que;
            dist[encode(e_start, s_start)] = 0;
            que.emplace(e_start, s_start);
            
            int ans = -1;
            while (!que.empty()) {
                auto [e, t] = que.front();
                que.pop();
                int d = dist[encode(e, t)];
                if (t == t_goal) {
                    ans = d;
                    break;
                }
                for (int ne : adj[e]) {
                    if (ne == t) {
                        int new_e = t;
                        int new_t = e;
                        int code = encode(new_e, new_t);
                        if (dist[code] == -1) {
                            dist[code] = d + 1;
                            que.emplace(new_e, new_t);
                        }
                    } else {
                        int new_e = ne;
                        int new_t = t;
                        int code = encode(new_e, new_t);
                        if (dist[code] == -1) {
                            dist[code] = d + 1;
                            que.emplace(new_e, new_t);
                        }
                    }
                }
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
