#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1005;
const int MAXM = 105;

int dist[MAXN][MAXM][3];
bool obstacle[MAXN][MAXM];

struct State {
    int x, y, d;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        int b, e;
        cin >> b >> e;
        int k;
        cin >> k;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                obstacle[i][j] = false;
                for (int d = 0; d < 3; ++d) {
                    dist[i][j][d] = 1e9;
                }
            }
        }

        for (int i = 0; i < k; ++i) {
            int x, y;
            cin >> x >> y;
            if (x >= 0 && x < n && y >= 0 && y < m) {
                obstacle[x][y] = true;
            }
        }

        deque<State> dq;

        dist[0][b][0] = 0;
        dq.push_back({0, b, 0});

        int dx[] = {1, 0, 0};
        int dy[] = {0, -1, 1};

        while (!dq.empty()) {
            State s = dq.front();
            dq.pop_front();

            int x = s.x, y = s.y, d = s.d;
            int current_dist = dist[x][y][d];

            // 1. 直走
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !obstacle[nx][ny]) {
                if (current_dist < dist[nx][ny][d]) {
                    dist[nx][ny][d] = current_dist;
                    dq.push_front({nx, ny, d});
                }
            }

            // 2. 轉彎
            if (d == 0) {
                if (current_dist + 1 < dist[x][y][1]) {
                    dist[x][y][1] = current_dist + 1;
                    dq.push_back({x, y, 1});
                }
                if (current_dist + 1 < dist[x][y][2]) {
                    dist[x][y][2] = current_dist + 1;
                    dq.push_back({x, y, 2});
                }
            } else if (d == 1) {
                if (current_dist + 1 < dist[x][y][0]) {
                    dist[x][y][0] = current_dist + 1;
                    dq.push_back({x, y, 0});
                }
            } else if (d == 2) {
                if (current_dist + 1 < dist[x][y][0]) {
                    dist[x][y][0] = current_dist + 1;
                    dq.push_back({x, y, 0});
                }
            }
        }

        int ans = dist[n - 1][e][0];
        if (dist[n - 1][e][1] < ans) ans = dist[n - 1][e][1];
        if (dist[n - 1][e][2] < ans) ans = dist[n - 1][e][2];
        
        cout << ans << "\n";
    }

    return 0;
}
