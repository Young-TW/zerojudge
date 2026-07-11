#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
using namespace std;

struct State {
    int x, y, phase, steps;
    State(int x, int y, int phase, int steps) : x(x), y(y), phase(phase), steps(steps) {}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        vector<string> grid(n);
        int start_x = -1, start_y = -1;
        int end_x = -1, end_y = -1;

        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 'S') {
                    start_x = i;
                    start_y = j;
                } else if (grid[i][j] == 'E') {
                    end_x = i;
                    end_y = j;
                }
            }
        }

        if (start_x == -1 || start_y == -1 || end_x == -1 || end_y == -1) {
            cout << "-1\n";
            continue;
        }

        vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int>(2, INT_MAX)));
        queue<State> q;
        q.emplace(start_x, start_y, 0, 0);
        dist[start_x][start_y][0] = 0;

        const int dx[] = {-1, 1, 0, 0};
        const int dy[] = {0, 0, -1, 1};

        bool found = false;
        while (!q.empty()) {
            State current = q.front();
            q.pop();

            if (current.x == end_x && current.y == end_y) {
                cout << current.steps << '\n';
                found = true;
                break;
            }

            for (int i = 0; i < 4; ++i) {
                int nx = current.x + dx[i];
                int ny = current.y + dy[i];
                int nphase = current.phase;
                int nsteps = current.steps + 1;

                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (grid[nx][ny] == '#') continue;

                if (grid[nx][ny] == 'P') {
                    nphase = 1 - nphase;
                }

                if (dist[nx][ny][nphase] > nsteps) {
                    dist[nx][ny][nphase] = nsteps;
                    q.emplace(nx, ny, nphase, nsteps);
                }
            }
        }

        if (!found) {
            cout << "-1\n";
        }
    }

    return 0;
}
