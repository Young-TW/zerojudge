#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

struct State {
    int x, y, mask;
};

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    while (cin >> N) {
        vector<string> grid(N);
        for (int i = 0; i < N; ++i) {
            cin >> grid[i];
        }

        vector<vector<vector<int>>> vis(N, vector<vector<int>>(N));
        
        queue<State> q;
        
        int start_mask = 0;
        char start_char = grid[0][0];
        if (start_char >= 'A' && start_char <= 'J') {
            start_mask |= (1 << (start_char - 'A'));
        } else {
            start_mask |= (1 << (start_char - 'a' + 10));
        }
        
        q.push({0, 0, start_mask});
        vis[0][0].push_back(start_mask);
        
        int ans = -1;
        int dist = 1;
        
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; ++i) {
                State cur = q.front();
                q.pop();
                int x = cur.x;
                int y = cur.y;
                int mask = cur.mask;
                
                if (x == N - 1 && y == N - 1) {
                    ans = dist;
                    break;
                }
                
                for (int j = 0; j < 4; ++j) {
                    int nx = x + dx[j];
                    int ny = y + dy[j];
                    
                    if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                        char c = grid[nx][ny];
                        int nmask = mask;
                        bool valid = true;
                        
                        if (c >= 'A' && c <= 'J') {
                            int idx = c - 'A';
                            if (mask & (1 << (idx + 10))) {
                                valid = false;
                            } else {
                                nmask |= (1 << idx);
                            }
                        } else {
                            int idx = c - 'a';
                            if (mask & (1 << idx)) {
                                valid = false;
                            } else {
                                nmask |= (1 << (idx + 10));
                            }
                        }
                        
                        if (!valid) continue;
                        
                        bool useful = true;
                        for (int m : vis[nx][ny]) {
                            if ((m & nmask) == m) {
                                useful = false;
                                break;
                            }
                        }
                        
                        if (useful) {
                            vis[nx][ny].erase(remove_if(vis[nx][ny].begin(), vis[nx][ny].end(), [&](int m) {
                                return (nmask & m) == nmask;
                            }), vis[nx][ny].end());
                            
                            vis[nx][ny].push_back(nmask);
                            q.push({nx, ny, nmask});
                        }
                    }
                }
            }
            if (ans != -1) break;
            dist++;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
