#include <iostream>
#include <string>

using namespace std;

int l, n, m;
char maze[205][205][205];

int dx[] = {1, -1, 0, 0, 0, 0};
int dy[] = {0, 0, 1, -1, 0, 0};
int dz[] = {0, 0, 0, 0, 1, -1};

const int MAX_NODES = 205 * 205 * 205 + 10;
int q[MAX_NODES];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> l >> n >> m)) return 0;
    string dummy;
    getline(cin, dummy);

    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < n; ++j) {
            string s;
            while (getline(cin, s)) {
                if (!s.empty() && s.back() == '\r') {
                    s.pop_back();
                }
                if (!s.empty()) {
                    break;
                }
            }
            if (s.empty()) {
                s = string(m, ' ');
            }
            while (s.length() < m) {
                s += ' ';
            }
            for (int k = 0; k < m; ++k) {
                maze[i][j][k] = s[k];
            }
        }
    }

    if (maze[1][1][1] == '#') {
        cout << 0 << "\n";
        return 0;
    }

    int head = 0, tail = 0;
    maze[1][1][1] = 'O';
    q[tail++] = (1 << 16) | (1 << 8) | 1;

    int dist = 0;
    int q_size = 1;

    while (head < tail) {
        if (q_size == 0) {
            dist++;
            q_size = tail - head;
        }
        q_size--;

        int code = q[head++];
        int x = code >> 16;
        int y = (code >> 8) & 0xFF;
        int z = code & 0xFF;

        if (x == l - 2 && y == n - 2 && z == m - 2) {
            cout << dist << "\n";
            return 0;
        }

        for (int i = 0; i < 6; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nz = z + dz[i];

            if (nx >= 0 && nx < l && ny >= 0 && ny < n && nz >= 0 && nz < m) {
                if (maze[nx][ny][nz] == ' ') {
                    maze[nx][ny][nz] = 'O';
                    q[tail++] = (nx << 16) | (ny << 8) | nz;
                }
            }
        }
    }

    cout << 0 << "\n";
    return 0;
}
