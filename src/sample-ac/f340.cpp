#include <bits/stdc++.h>
using namespace std;

struct TPiece {
    // rel[rot][i][0] = dx, rel[rot][i][1] = dy
    int rel[4][4][2];
    TPiece() {
        // base shape, rotation 0
        int base[4][2] = { {-1,0}, {0,0}, {1,0}, {0,-1} };
        for (int r = 0; r < 4; ++r) {
            for (int i = 0; i < 4; ++i) {
                int dx = base[i][0];
                int dy = base[i][1];
                // rotate r times clockwise
                for (int k = 0; k < r; ++k) {
                    int ndx = dy;
                    int ndy = -dx;
                    dx = ndx; dy = ndy;
                }
                rel[r][i][0] = dx;
                rel[r][i][1] = dy;
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int X, Y;
    TPiece piece;
    while (cin >> X >> Y) {
        int n;
        if (!(cin >> n)) break;
        vector<int> cmd(n);
        for (int i = 0; i < n; ++i) cin >> cmd[i];

        // board[y][x], 1‑based, y = 1..Y, x = 1..X
        vector<vector<char>> board(Y + 1, vector<char>(X + 1, 0));

        auto canPlace = [&](int ax, int ay, int rot) -> bool {
            for (int i = 0; i < 4; ++i) {
                int x = ax + piece.rel[rot][i][0];
                int y = ay + piece.rel[rot][i][1];
                if (x < 1 || x > X || y < 1 || y > Y) return false;
                if (board[y][x]) return false;
            }
            return true;
        };

        auto place = [&](int ax, int ay, int rot) {
            for (int i = 0; i < 4; ++i) {
                int x = ax + piece.rel[rot][i][0];
                int y = ay + piece.rel[rot][i][1];
                board[y][x] = 1;
            }
        };

        int ax = (X + 1) / 2;          // ceil(X/2)
        int ay = Y;
        int rot = 0;
        bool locked = false;

        for (int c : cmd) {
            // ----- gravity -----
            if (!canPlace(ax, ay - 1, rot)) {
                place(ax, ay, rot);
                locked = true;
                break;
            }
            --ay;   // fall one row

            // ----- command -----
            if (c == 0) continue;

            if (c == 1) {                 // move right
                if (canPlace(ax + 1, ay, rot)) ++ax;
            } else if (c == 2) {          // move left
                if (canPlace(ax - 1, ay, rot)) --ax;
            } else if (c == 4) {          // rotate clockwise
                int nr = (rot + 1) & 3;
                if (canPlace(ax, ay, nr)) rot = nr;
            } else if (c == 3) {          // hard drop
                while (canPlace(ax, ay - 1, rot)) --ay;
                place(ax, ay, rot);
                locked = true;
                break;
            }
        }

        // ----- produce output -----
        vector<string> out(Y, string(X, '0'));
        for (int y = 1; y <= Y; ++y)
            for (int x = 1; x <= X; ++x)
                if (board[y][x]) out[y - 1][x - 1] = '1';

        if (!locked) {
            for (int i = 0; i < 4; ++i) {
                int x = ax + piece.rel[rot][i][0];
                int y = ay + piece.rel[rot][i][1];
                out[y - 1][x - 1] = '1';
            }
        }

        for (int y = Y; y >= 1; --y) {
            cout << out[y - 1] << '\n';
        }
    }
    return 0;
}
