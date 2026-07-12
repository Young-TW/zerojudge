#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

struct State {
    long long d;
    int x, y;
    bool operator>(const State& o) const {
        return d > o.d;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> a(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> a[i][j];
            }
        }

        if (a[0][0] > 0) {
            cout << -1 << "\n";
            continue;
        }

        vector<vector<long long>> dist(n, vector<long long>(m, -1));
        priority_queue<State, vector<State>, greater<State>> pq;

        dist[0][0] = 0;
        pq.push({0, 0, 0});

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        bool found = false;
        while (!pq.empty()) {
            State curr = pq.top();
            pq.pop();

            if (curr.d > dist[curr.x][curr.y]) continue;

            if (curr.x == n - 1 && curr.y == m - 1) {
                cout << curr.d << "\n";
                found = true;
                break;
            }

            for (int i = 0; i < 4; ++i) {
                int nx = curr.x + dx[i];
                int ny = curr.y + dy[i];

                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    long long nd = max(curr.d + 1, (long long)a[nx][ny]);
                    if (dist[nx][ny] == -1 || nd < dist[nx][ny]) {
                        dist[nx][ny] = nd;
                        pq.push({nd, nx, ny});
                    }
                }
            }
        }

        if (!found) {
            cout << -1 << "\n";
        }
    }

    return 0;
}
