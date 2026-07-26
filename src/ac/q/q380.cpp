#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int H, W;
    while (cin >> H >> W) {
        vector<vector<char>> grid(H, vector<char>(W));
        for (int i = 0; i < H; ++i)
            for (int j = 0; j < W; ++j) {
                int v; cin >> v;
                grid[i][j] = static_cast<char>(v);
            }

        // ---------- 1. label the two islands ----------
        vector<vector<int>> comp(H, vector<int>(W, -1));
        int compCnt = 0;
        const int dx[4] = {-1, 1, 0, 0};
        const int dy[4] = {0, 0, -1, 1};

        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                if (grid[i][j] == 1 && comp[i][j] == -1) {
                    queue<pair<int,int>> q;
                    q.emplace(i, j);
                    comp[i][j] = compCnt;
                    while (!q.empty()) {
                        auto [x, y] = q.front(); q.pop();
                        for (int d = 0; d < 4; ++d) {
                            int nx = x + dx[d], ny = y + dy[d];
                            if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
                            if (grid[nx][ny] == 1 && comp[nx][ny] == -1) {
                                comp[nx][ny] = compCnt;
                                q.emplace(nx, ny);
                            }
                        }
                    }
                    ++compCnt;
                }
            }
        }

        // there must be exactly two islands
        if (compCnt != 2) {
            cout << -1 << '\n';
            continue;
        }

        // ---------- 2. 0‑1 BFS from island 0 ----------
        vector<vector<int>> dist(H, vector<int>(W, INF));
        deque<pair<int,int>> dq;

        for (int i = 0; i < H; ++i)
            for (int j = 0; j < W; ++j)
                if (comp[i][j] == 0) {
                    dist[i][j] = 0;
                    dq.emplace_front(i, j);
                }

        int answer = -1;
        while (!dq.empty()) {
            auto [x, y] = dq.front(); dq.pop_front();

            if (comp[x][y] == 1) {          // reached island 1
                answer = dist[x][y];
                break;
            }

            for (int d = 0; d < 4; ++d) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
                if (grid[nx][ny] == 2) continue;          // rock

                int w = (grid[nx][ny] == 0) ? 1 : 0;      // sea costs 1
                if (dist[nx][ny] > dist[x][y] + w) {
                    dist[nx][ny] = dist[x][y] + w;
                    if (w == 0) dq.emplace_front(nx, ny);
                    else        dq.emplace_back (nx, ny);
                }
            }
        }

        cout << answer << '\n';
    }
    return 0;
}
