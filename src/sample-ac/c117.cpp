#include <iostream>
#include <string>
#include <queue>
#include <utility>
#include <cstring>

using namespace std;

int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, e;
    while (cin >> s >> e) {
        int sx = s[0] - 'a';
        int sy = s[1] - '1';
        int ex = e[0] - 'a';
        int ey = e[1] - '1';

        int dist[8][8];
        memset(dist, -1, sizeof(dist));

        queue<pair<int, int>> q;
        q.push({sx, sy});
        dist[sx][sy] = 0;

        while (!q.empty()) {
            pair<int, int> curr = q.front();
            q.pop();
            int cx = curr.first;
            int cy = curr.second;

            if (cx == ex && cy == ey) {
                break;
            }

            for (int i = 0; i < 8; i++) {
                int nx = cx + dx[i];
                int ny = cy + dy[i];
                if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[cx][cy] + 1;
                    q.push({nx, ny});
                }
            }
        }

        cout << "To get from " << s << " to " << e << " takes " << dist[ex][ey] << " knight moves.\n";
    }
    return 0;
}
