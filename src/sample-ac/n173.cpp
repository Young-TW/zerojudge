#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

int right_map[7][7];
int dp[105][105][7][7];

struct State {
    int top, front, right;
};

void build_right_map(int a, int b, int c) {
    memset(right_map, -1, sizeof(right_map));
    queue<State> q;
    q.push({a, b, c});
    right_map[a][b] = c;
    while (!q.empty()) {
        State cur = q.front();
        q.pop();
        int top = cur.top;
        int front = cur.front;
        int right = cur.right;
        
        // right
        int nt = 7 - right;
        int nf = front;
        int nr = top;
        if (right_map[nt][nf] == -1) {
            right_map[nt][nf] = nr;
            q.push({nt, nf, nr});
        }
        
        // left
        nt = right;
        nf = front;
        nr = 7 - top;
        if (right_map[nt][nf] == -1) {
            right_map[nt][nf] = nr;
            q.push({nt, nf, nr});
        }
        
        // down
        nt = 7 - front;
        nf = top;
        nr = right;
        if (right_map[nt][nf] == -1) {
            right_map[nt][nf] = nr;
            q.push({nt, nf, nr});
        }
        
        // up
        nt = front;
        nf = 7 - top;
        nr = right;
        if (right_map[nt][nf] == -1) {
            right_map[nt][nf] = nr;
            q.push({nt, nf, nr});
        }
        
        // forward
        nt = top;
        nf = 7 - right;
        nr = front;
        if (right_map[nt][nf] == -1) {
            right_map[nt][nf] = nr;
            q.push({nt, nf, nr});
        }
        
        // backward
        nt = top;
        nf = right;
        nr = 7 - front;
        if (right_map[nt][nf] == -1) {
            right_map[nt][nf] = nr;
            q.push({nt, nf, nr});
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, a, b, c;
    while (cin >> n >> a >> b >> c) {
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
        }
        
        build_right_map(a, b, c);
        
        memset(dp, -1, sizeof(dp));
        if (grid[0][0] == 'o') {
            dp[0][0][a][b] = a;
        }
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 'x') continue;
                for (int top = 1; top <= 6; ++top) {
                    for (int front = 1; front <= 6; ++front) {
                        if (dp[i][j][top][front] == -1) continue;
                        int right = right_map[top][front];
                        if (right == -1) continue;
                        
                        // move right
                        if (j + 1 < n && grid[i][j+1] == 'o') {
                            int nt = 7 - right;
                            int nf = front;
                            int nr = top;
                            if (dp[i][j+1][nt][nf] < dp[i][j][top][front] + nt) {
                                dp[i][j+1][nt][nf] = dp[i][j][top][front] + nt;
                            }
                        }
                        
                        // move down
                        if (i + 1 < n && grid[i+1][j] == 'o') {
                            int nt = 7 - front;
                            int nf = top;
                            int nr = right;
                            if (dp[i+1][j][nt][nf] < dp[i][j][top][front] + nt) {
                                dp[i+1][j][nt][nf] = dp[i][j][top][front] + nt;
                            }
                        }
                    }
                }
            }
        }
        
        int ans = 0;
        for (int top = 1; top <= 6; ++top) {
            for (int front = 1; front <= 6; ++front) {
                if (dp[n-1][n-1][top][front] > ans) {
                    ans = dp[n-1][n-1][top][front];
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
