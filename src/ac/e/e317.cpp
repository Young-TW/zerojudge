#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <string>
#include <functional>

using namespace std;

int main() {
    int m, n;
    vector<string> results;
    while (cin >> m >> n) {
        vector<vector<int>> grid(m + 1, vector<int>(m + 1, -1));
        for (int i = 0; i < n; i++) {
            int x, y, c;
            cin >> x >> y >> c;
            grid[x][y] = c;
        }

        const int INF = 1000000000;
        // dist[x][y][s]: s=0 natural, s=1 magic color 0, s=2 magic color 1
        vector<vector<vector<int>>> dist(m + 1, vector<vector<int>>(m + 1, vector<int>(3, INF)));

        priority_queue<tuple<int, int, int, int>,
                       vector<tuple<int, int, int, int>>,
                       greater<tuple<int, int, int, int>>> pq;

        dist[1][1][0] = 0;
        pq.push(make_tuple(0, 1, 1, 0));

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        while (!pq.empty()) {
            tuple<int, int, int, int> top = pq.top();
            pq.pop();
            int d = get<0>(top), x = get<1>(top), y = get<2>(top), s = get<3>(top);

            if (d > dist[x][y][s]) continue;

            int curColor;
            if (s == 0) curColor = grid[x][y];
            else if (s == 1) curColor = 0;
            else curColor = 1;

            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                if (nx < 1 || nx > m || ny < 1 || ny > m) continue;

                if (grid[nx][ny] != -1) {
                    int cost = (curColor != grid[nx][ny]) ? 1 : 0;
                    if (dist[x][y][s] + cost < dist[nx][ny][0]) {
                        dist[nx][ny][0] = dist[x][y][s] + cost;
                        pq.push(make_tuple(dist[nx][ny][0], nx, ny, 0));
                    }
                } else {
                    if (s == 0) {
                        for (int nc = 0; nc <= 1; nc++) {
                            int cost = 2 + ((curColor != nc) ? 1 : 0);
                            int ns = (nc == 0) ? 1 : 2;
                            if (dist[x][y][s] + cost < dist[nx][ny][ns]) {
                                dist[nx][ny][ns] = dist[x][y][s] + cost;
                                pq.push(make_tuple(dist[nx][ny][ns], nx, ny, ns));
                            }
                        }
                    }
                }
            }
        }

        int ans = min(dist[m][m][0], min(dist[m][m][1], dist[m][m][2]));
        if (ans >= INF) results.push_back("-1");
        else results.push_back(to_string(ans));
    }

    for (size_t i = 0; i < results.size(); i++) {
        cout << results[i];
        if (i < results.size() - 1) cout << "\n\n";
        else cout << "\n";
    }

    return 0;
}
