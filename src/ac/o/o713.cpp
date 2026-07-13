#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cstring>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int M, N, q;
    while (cin >> M >> N >> q) {
        vector<vector<int>> grid(M, vector<int>(N));
        int sr = -1, sc = -1;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> grid[i][j];
                if (grid[i][j] == -2) {
                    sr = i; sc = j;
                }
            }
        }
        
        // Collect positive-radius bombs
        vector<tuple<int,int,int>> bombs; // r, c, radius
        vector<vector<int>> bomb_id(M, vector<int>(N, -1));
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] > 0) {
                    bomb_id[i][j] = bombs.size();
                    bombs.emplace_back(i, j, grid[i][j]);
                }
            }
        }
        int B = bombs.size();
        
        // Precompute bomb blast areas and adjacency
        vector<vector<int>> bomb_blast(B);
        vector<vector<int>> bomb_adj(B);
        vector<int> vis_pre(M*N, 0);
        int pre_token = 0;
        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};
        
        for (int u = 0; u < B; ++u) {
            int r, c, rad;
            tie(r, c, rad) = bombs[u];
            pre_token++;
            queue<tuple<int,int,int>> qq;
            qq.emplace(r, c, 0);
            vis_pre[r*N+c] = pre_token;
            while (!qq.empty()) {
                int cr, cc, cd;
                tie(cr, cc, cd) = qq.front(); qq.pop();
                int cell_idx = cr*N+cc;
                bomb_blast[u].push_back(cell_idx);
                int v = bomb_id[cr][cc];
                if (v != -1 && v != u) {
                    bomb_adj[u].push_back(v);
                }
                if (cd == rad) continue;
                for (int d = 0; d < 4; ++d) {
                    int nr = cr + dr[d];
                    int nc = cc + dc[d];
                    if (nr < 0 || nr >= M || nc < 0 || nc >= N) continue;
                    if (grid[nr][nc] == -1) continue;
                    int nidx = nr*N+nc;
                    if (vis_pre[nidx] == pre_token) continue;
                    vis_pre[nidx] = pre_token;
                    qq.emplace(nr, nc, cd+1);
                }
            }
        }
        
        // Binary search for minimal R
        int low = 0, high = M*N;
        vector<int> vis_init(M*N, 0);
        int init_token = 0;
        vector<char> exploded(M*N, 0);
        vector<int> bomb_vis(B, 0);
        int bomb_token = 0;
        
        auto check = [&](int R) -> bool {
            fill(exploded.begin(), exploded.end(), 0);
            int count = 0;
            
            init_token++;
            queue<tuple<int,int,int>> qq;
            qq.emplace(sr, sc, 0);
            vis_init[sr*N+sc] = init_token;
            exploded[sr*N+sc] = 1;
            count++;
            vector<int> init_triggered;
            
            while (!qq.empty()) {
                int r, c, d;
                tie(r, c, d) = qq.front(); qq.pop();
                if (d == R) continue;
                for (int dir = 0; dir < 4; ++dir) {
                    int nr = r + dr[dir];
                    int nc = c + dc[dir];
                    if (nr < 0 || nr >= M || nc < 0 || nc >= N) continue;
                    if (grid[nr][nc] == -1) continue;
                    int nidx = nr*N+nc;
                    if (vis_init[nidx] == init_token) continue;
                    vis_init[nidx] = init_token;
                    exploded[nidx] = 1;
                    count++;
                    int bid = bomb_id[nr][nc];
                    if (bid != -1) {
                        init_triggered.push_back(bid);
                    }
                    qq.emplace(nr, nc, d+1);
                }
            }
            
            bomb_token++;
            queue<int> qb;
            for (int bid : init_triggered) {
                if (bomb_vis[bid] != bomb_token) {
                    bomb_vis[bid] = bomb_token;
                    qb.push(bid);
                }
            }
            vector<int> triggered_bombs;
            while (!qb.empty()) {
                int u = qb.front(); qb.pop();
                triggered_bombs.push_back(u);
                for (int v : bomb_adj[u]) {
                    if (bomb_vis[v] != bomb_token) {
                        bomb_vis[v] = bomb_token;
                        qb.push(v);
                    }
                }
            }
            
            for (int u : triggered_bombs) {
                for (int cell : bomb_blast[u]) {
                    if (!exploded[cell]) {
                        exploded[cell] = 1;
                        count++;
                    }
                }
            }
            
            return count >= q;
        };
        
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (check(mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        cout << low << '\n';
    }
    return 0;
}
