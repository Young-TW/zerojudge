#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <unordered_set>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int H, W, K;
        cin >> H >> W >> K;
        int Sx, Sy, Tx, Ty;
        cin >> Sx >> Sy;
        cin >> Tx >> Ty;
        
        vector<pair<int,int>> obstacles;
        obstacles.reserve(K);
        unordered_set<long long> obs_set;
        obs_set.reserve(K * 2);
        for (int i = 0; i < K; ++i) {
            int x, y;
            cin >> x >> y;
            obstacles.emplace_back(x, y);
            long long key = ((long long)x << 32) | (unsigned int)y;
            obs_set.insert(key);
        }
        
        // Check if target is adjacent to any obstacle
        bool target_adjacent = false;
        const int dx[4] = {-1, 1, 0, 0};
        const int dy[4] = {0, 0, -1, 1};
        for (int dir = 0; dir < 4; ++dir) {
            int nx = Tx + dx[dir];
            int ny = Ty + dy[dir];
            if (nx >= 1 && nx <= H && ny >= 1 && ny <= W) {
                long long key = ((long long)nx << 32) | (unsigned int)ny;
                if (obs_set.find(key) != obs_set.end()) {
                    target_adjacent = true;
                    break;
                }
            }
        }
        if (!target_adjacent) {
            cout << "Guan Hao Ni Zhi Ji.\n";
            continue;
        }
        
        // Build node coordinates
        vector<pair<int,int>> node_coords;
        node_coords.reserve(2 + 4 * K);
        node_coords.emplace_back(Sx, Sy);
        node_coords.emplace_back(Tx, Ty);
        for (const auto& ob : obstacles) {
            int ox = ob.first, oy = ob.second;
            for (int dir = 0; dir < 4; ++dir) {
                int nx = ox + dx[dir];
                int ny = oy + dy[dir];
                if (nx >= 1 && nx <= H && ny >= 1 && ny <= W) {
                    long long key = ((long long)nx << 32) | (unsigned int)ny;
                    if (obs_set.find(key) == obs_set.end()) {
                        node_coords.emplace_back(nx, ny);
                    }
                }
            }
        }
        sort(node_coords.begin(), node_coords.end());
        node_coords.erase(unique(node_coords.begin(), node_coords.end()), node_coords.end());
        int N = node_coords.size();
        
        // Helper to get index of a coordinate (must exist)
        auto get_idx = [&](int x, int y) -> int {
            auto it = lower_bound(node_coords.begin(), node_coords.end(), make_pair(x, y));
            return static_cast<int>(it - node_coords.begin());
        };
        int start_idx = get_idx(Sx, Sy);
        int target_idx = get_idx(Tx, Ty);
        
        // Build row_obs and col_obs
        map<int, vector<int>> row_obs, col_obs;
        for (const auto& ob : obstacles) {
            int x = ob.first, y = ob.second;
            row_obs[x].push_back(y);
            col_obs[y].push_back(x);
        }
        for (auto& p : row_obs) {
            sort(p.second.begin(), p.second.end());
        }
        for (auto& p : col_obs) {
            sort(p.second.begin(), p.second.end());
        }
        
        // Build graph
        vector<vector<int>> adj(N);
        for (int i = 0; i < N; ++i) {
            int x = node_coords[i].first;
            int y = node_coords[i].second;
            
            // Right
            auto it_row = row_obs.find(x);
            if (it_row != row_obs.end()) {
                const vector<int>& vec = it_row->second;
                auto it = upper_bound(vec.begin(), vec.end(), y);
                if (it != vec.end()) {
                    int c = *it;
                    int nx = x, ny = c - 1;
                    if (ny != y) {
                        int v = get_idx(nx, ny);
                        adj[i].push_back(v);
                    }
                }
            }
            // Left
            if (it_row != row_obs.end()) {
                const vector<int>& vec = it_row->second;
                auto it = lower_bound(vec.begin(), vec.end(), y);
                if (it != vec.begin()) {
                    --it;
                    int c = *it;
                    int nx = x, ny = c + 1;
                    if (ny != y) {
                        int v = get_idx(nx, ny);
                        adj[i].push_back(v);
                    }
                }
            }
            // Down
            auto it_col = col_obs.find(y);
            if (it_col != col_obs.end()) {
                const vector<int>& vec = it_col->second;
                auto it = upper_bound(vec.begin(), vec.end(), x);
                if (it != vec.end()) {
                    int r = *it;
                    int nx = r - 1, ny = y;
                    if (nx != x) {
                        int v = get_idx(nx, ny);
                        adj[i].push_back(v);
                    }
                }
            }
            // Up
            if (it_col != col_obs.end()) {
                const vector<int>& vec = it_col->second;
                auto it = lower_bound(vec.begin(), vec.end(), x);
                if (it != vec.begin()) {
                    --it;
                    int r = *it;
                    int nx = r + 1, ny = y;
                    if (nx != x) {
                        int v = get_idx(nx, ny);
                        adj[i].push_back(v);
                    }
                }
            }
        }
        
        // BFS
        vector<int> dist(N, -1);
        queue<int> q;
        dist[start_idx] = 0;
        q.push(start_idx);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == target_idx) break;
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        
        if (dist[target_idx] != -1) {
            cout << dist[target_idx] << '\n';
        } else {
            cout << "Guan Hao Ni Zhi Ji.\n";
        }
    }
    return 0;
}
