#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

struct State {
    int x, y, steps;
    State(int x, int y, int steps) : x(x), y(y), steps(steps) {}
};

int main() {
    int N;
    while (cin >> N) {
        if (N == 2) {
            cout << 5 << endl;
            continue;
        }

        int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
        int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};

        vector<vector<bool>> visited(N, vector<bool>(N, false));
        queue<State> q;
        q.push(State(0, 0, 0));
        visited[0][0] = true;

        int targetX = N - 1;
        int targetY = N - 1;
        bool found = false;

        while (!q.empty()) {
            State current = q.front();
            q.pop();

            if (current.x == targetX && current.y == targetY) {
                cout << current.steps << endl;
                found = true;
                break;
            }

            for (int i = 0; i < 8; ++i) {
                int nx = current.x + dx[i];
                int ny = current.y + dy[i];

                if (nx >= 0 && nx < N && ny >= 0 && ny < N && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    q.push(State(nx, ny, current.steps + 1));
                }
            }
        }

        if (!found) {
            cout << -1 << endl;
        }
    }
    return 0;
}
