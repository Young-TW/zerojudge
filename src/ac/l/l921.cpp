#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int R;
    while (cin >> R) {
        int N;
        if (!(cin >> N)) break;
        vector<vector<char>> given(R, vector<char>(R, 0));
        for (int i = 0; i < N; ++i) {
            int x, y;
            cin >> x >> y;
            if (0 <= x && x < R && 0 <= y && y < R)
                given[x][y] = 1;
        }

        int H = 2 * R - 1;
        vector<string> pic(H, string(H, '#'));

        // points
        for (int x = 0; x < R; ++x)
            for (int y = 0; y < R; ++y)
                if (given[x][y])
                    pic[2 * x][2 * y] = '&';

        // directions to process (avoid duplicates)
        const int dx[4] = {0, 1, 1, 1};
        const int dy[4] = {1, 0, 1, -1};

        for (int x = 0; x < R; ++x) {
            for (int y = 0; y < R; ++y) if (given[x][y]) {
                for (int dir = 0; dir < 4; ++dir) {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];
                    if (nx < 0 || nx >= R || ny < 0 || ny >= R) continue;
                    if (!given[nx][ny]) continue;

                    char ch;
                    if (dx[dir] == 0 && dy[dir] == 1) ch = '-';
                    else if (dx[dir] == 1 && dy[dir] == 0) ch = '|';
                    else if (dx[dir] == 1 && dy[dir] == 1) ch = '\\';
                    else /* (1,-1) */ ch = '/';

                    int cx = 2 * x + (dx[dir] == 0 ? 0 : 1);
                    int cy = 2 * y + (dy[dir] == 0 ? 0 : (dy[dir] > 0 ? 1 : -1));

                    if (pic[cx][cy] == '#') {
                        pic[cx][cy] = ch;
                    } else if ((ch == '/' && pic[cx][cy] == '\\') ||
                               (ch == '\\' && pic[cx][cy] == '/')) {
                        pic[cx][cy] = 'X';
                    }
                    // otherwise the same character is already there – nothing to do
                }
            }
        }

        for (int i = 0; i < H; ++i) {
            cout << pic[i] << '\n';
        }
    }
    return 0;
}
