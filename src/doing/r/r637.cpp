#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <cstring>
using namespace std;

struct State {
    int r, c, hp, steps, jumps;
    bool operator<(const State& other) const {
        if (steps != other.steps) return steps > other.steps;
        return hp < other.hp;
    }
};

int main() {
    int R, C, H0, K;
    while (cin >> R >> C >> H0 >> K) {
        vector<string> grid(R);
        for (int i = 0; i < R; ++i) {
            cin >> grid[i];
        }
        vector<vector<int>> w(R, vector<int>(C));
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                cin >> w[i][j];
            }
        }

        int sr = -1, sc = -1, er = -1, ec = -1;
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (grid[i][j] == 'S') {
                    sr = i;
                    sc = j;
                } else if (grid[i][j] == 'E') {
                    er = i;
                    ec = j;
                }
            }
        }

        const int H = 200;
        vector<vector<vector<vector<int>>>> dp(R, vector<vector<vector<int>>>(C, vector<vector<int>>(H + 1, vector<int>(K + 1, INT_MAX))));
        priority_queue<State> pq;
        int initial_hp = min(H0 + w[sr][sc], H);
        if (initial_hp < 0) initial_hp = 0;
        dp[sr][sc][initial_hp][0] = 0;
        pq.push({sr, sc, initial_hp, 0, 0});

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        int ans_steps = INT_MAX;
        int ans_hp = -1;

        while (!pq.empty()) {
            State cur = pq.top();
            pq.pop();

            if (cur.r == er && cur.c == ec) {
                if (cur.steps < ans_steps) {
                    ans_steps = cur.steps;
                    ans_hp = cur.hp;
                } else if (cur.steps == ans_steps && cur.hp > ans_hp) {
                    ans_hp = cur.hp;
                }
                continue;
            }

            if (cur.steps > dp[cur.r][cur.c][cur.hp][cur.jumps]) {
                continue;
            }

            for (int d = 0; d < 4; ++d) {
                int nr = cur.r + dr[d];
                int nc = cur.c + dc[d];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C || grid[nr][nc] == '#') continue;
                int new_hp = cur.hp + w[nr][nc];
                if (new_hp > H) new_hp = H;
                if (new_hp < 0) new_hp = 0;
                if (cur.steps + 1 < dp[nr][nc][new_hp][cur.jumps]) {
                    dp[nr][nc][new_hp][cur.jumps] = cur.steps + 1;
                    pq.push({nr, nc, new_hp, cur.steps + 1, cur.jumps});
                }
            }

            if (cur.jumps < K) {
                for (int nr = 0; nr < R; ++nr) {
                    for (int nc = 0; nc < C; ++nc) {
                        if (grid[nr][nc] == '#') continue;
                        int dist = abs(nr - cur.r) + abs(nc - cur.c);
                        if (dist <= 2 && dist > 0) {
                            int new_hp = cur.hp + w[nr][nc];
                            if (new_hp > H) new_hp = H;
                            if (new_hp < 0) new_hp = 0;
                            if (cur.steps + 1 < dp[nr][nc][new_hp][cur.jumps + 1]) {
                                dp[nr][nc][new_hp][cur.jumps + 1] = cur.steps + 1;
                                pq.push({nr, nc, new_hp, cur.steps + 1, cur.jumps + 1});
                            }
                        }
                    }
                }
            }
        }

        if (ans_steps != INT_MAX) {
            cout << ans_steps << " " << ans_hp << endl;
        } else {
            cout << -1 << endl;
        }
    }
    return 0;
}
