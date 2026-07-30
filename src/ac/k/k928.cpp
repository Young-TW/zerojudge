#include <iostream>
#include <vector>
#include <string>
using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int L, W;

bool inBlock(int r, int c, int x, int y) {
    return r >= x && r < x + W && c >= y && c < y + W;
}

bool canMove(int x, int y, int d, vector<string>& g) {
    int nx = x + dx[d], ny = y + dy[d];
    if (nx < 0 || ny < 0 || nx + W > L || ny + W > L) return false;
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < W; j++) {
            int r = nx + i, c = ny + j;
            if (inBlock(r, c, x, y)) continue;
            if (g[r][c] == '*') return false;
            for (int k = 0; k < 4; k++) {
                int nr = r + dx[k], nc = c + dy[k];
                if (nr < 0 || nr >= L || nc < 0 || nc >= L) continue;
                if (g[nr][nc] == '*' && !inBlock(nr, nc, x, y)) return false;
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> L >> W) {
        vector<string> g(L, string(L, ' '));
        int x = 0, y = 0, dir = 0;
        while (true) {
            for (int i = 0; i < W; i++)
                for (int j = 0; j < W; j++)
                    g[x + i][y + j] = '*';
            if (canMove(x, y, dir, g)) {
                x += dx[dir];
                y += dy[dir];
            } else {
                int nd = (dir + 1) % 4;
                if (canMove(x, y, nd, g)) {
                    dir = nd;
                    x += dx[dir];
                    y += dy[dir];
                } else {
                    break;
                }
            }
        }
        for (int i = 0; i < L; i++) cout << g[i] << "\n";
    }
    return 0;
}
