#include <bits/stdc++.h>
using namespace std;

const int COL = 5;
const int ROW = 7;

int N;                              // required number of moves
int board0[COL][ROW];               // initial board

/* ------------------------------------------------------------ */
/* basic operations                                              */

void gravity(int b[COL][ROW]) {
    for (int x = 0; x < COL; ++x) {
        int w = 0;
        for (int y = 0; y < ROW; ++y) {
            if (b[x][y]) {
                b[x][w++] = b[x][y];
            }
        }
        while (w < ROW) b[x][w++] = 0;
    }
}

bool eliminate(int b[COL][ROW]) {
    bool clear[COL][ROW] = {0};
    bool any = false;

    // horizontal
    for (int y = 0; y < ROW; ++y) {
        int x = 0;
        while (x < COL) {
            if (b[x][y] == 0) { ++x; continue; }
            int c = b[x][y];
            int k = x + 1;
            while (k < COL && b[k][y] == c) ++k;
            if (k - x >= 3) {
                for (int t = x; t < k; ++t) clear[t][y] = true;
                any = true;
            }
            x = k;
        }
    }

    // vertical
    for (int x = 0; x < COL; ++x) {
        int y = 0;
        while (y < ROW) {
            if (b[x][y] == 0) { ++y; continue; }
            int c = b[x][y];
            int k = y + 1;
            while (k < ROW && b[x][k] == c) ++k;
            if (k - y >= 3) {
                for (int t = y; t < k; ++t) clear[x][t] = true;
                any = true;
            }
            y = k;
        }
    }

    if (!any) return false;
    for (int x = 0; x < COL; ++x)
        for (int y = 0; y < ROW; ++y)
            if (clear[x][y]) b[x][y] = 0;
    return true;
}

void cascade(int b[COL][ROW]) {
    while (true) {
        gravity(b);
        if (!eliminate(b)) break;
    }
}

/* ------------------------------------------------------------ */
/* state encoding                                                */

string encode(const int b[COL][ROW]) {
    string s;
    s.reserve(COL * ROW);
    for (int x = 0; x < COL; ++x)
        for (int y = 0; y < ROW; ++y)
            s.push_back(char(b[x][y]));   // values 0..10 fit into a char
    return s;
}

/* ------------------------------------------------------------ */
/* DFS                                                          */

vector<array<int,3>> answer;               // current path
vector<array<int,3>> bestAns;               // solution to output
unordered_map<string,int> visited;         // state -> minimal depth

bool emptyBoard(const int b[COL][ROW]) {
    for (int x = 0; x < COL; ++x)
        for (int y = 0; y < ROW; ++y)
            if (b[x][y]) return false;
    return true;
}

bool dfs(int cur[COL][ROW], int depth) {
    if (emptyBoard(cur)) {
        if (depth == N) {
            bestAns = answer;
            return true;
        }
        return false;               // cleared too early
    }
    if (depth == N) return false;   // moves exhausted, not empty

    string key = encode(cur);
    auto it = visited.find(key);
    if (it != visited.end() && it->second <= depth) return false;
    visited[key] = depth;

    // try moves in required order
    for (int x = 0; x < COL; ++x) {
        for (int y = 0; y < ROW; ++y) {
            if (cur[x][y] == 0) continue;
            for (int dir : {1, -1}) {          // 1 before -1
                int nx = x + dir;
                if (nx < 0 || nx >= COL) continue;

                int nxt[COL][ROW];
                memcpy(nxt, cur, sizeof nxt);

                if (nxt[nx][y] != 0) {        // exchange
                    swap(nxt[x][y], nxt[nx][y]);
                } else {                      // drop into empty column
                    int colour = nxt[x][y];
                    nxt[x][y] = 0;
                    int h = 0;
                    while (h < ROW && nxt[nx][h] != 0) ++h;
                    if (h >= ROW) continue;   // should never happen
                    nxt[nx][h] = colour;
                }

                cascade(nxt);
                answer.push_back({x, y, dir});
                if (dfs(nxt, depth + 1)) return true;
                answer.pop_back();
            }
        }
    }
    return false;
}

/* ------------------------------------------------------------ */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> N) {
        // read 5 columns
        memset(board0, 0, sizeof board0);
        for (int x = 0; x < COL; ++x) {
            int v, y = 0;
            while (cin >> v) {
                if (v == 0) break;
                if (y < ROW) board0[x][y++] = v;
            }
        }

        answer.clear();
        bestAns.clear();
        visited.clear();

        int start[COL][ROW];
        memcpy(start, board0, sizeof start);
        bool ok = dfs(start, 0);

        if (!ok) {
            cout << -1 << '\n';
        } else {
            for (auto &mv : bestAns) {
                cout << mv[0] << ' ' << mv[1] << ' ' << mv[2] << '\n';
            }
        }
    }
    return 0;
}
