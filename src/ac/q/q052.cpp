#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    cin.ignore();

    vector<string> maze(n);
    for (int i = 0; i < n; ++i) {
        if (!getline(cin, maze[i])) {
            maze[i] = string(m, '#');
        }
        while (maze[i].length() < m) {
            maze[i] += ' ';
        }
    }

    int sr = 1, sc = 1;
    int tr = n - 2, tc = m - 2;

    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> q;

    q.push({sr, sc});
    dist[sr][sc] = 0;

    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();

        int r = curr.first;
        int c = curr.second;

        if (r == tr && c == tc) {
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < n && nc >= 0 && nc < m && maze[nr][nc] != '#' && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    cout << dist[tr][tc] << "\n";

    return 0;
}
