#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int C, R;
    long long L;
    while (cin >> C >> R >> L) {
        string dummy;
        getline(cin, dummy);                 // consume end‑of‑line

        vector<string> grid(R);
        for (int i = 0; i < R; ++i) {
            getline(cin, grid[i]);
            if ((int)grid[i].size() < C)      // pad missing trailing blanks
                grid[i] += string(C - grid[i].size(), ' ');
        }

        // locate start
        int sr = -1, sc = -1;
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                if (grid[i][j] == 'S') {
                    sr = i; sc = j;
                }

        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};

        vector<vector<int>> dist(R, vector<int>(C, -1));
        queue<pair<int,int>> q;
        dist[sr][sc] = 0;
        q.emplace(sr, sc);

        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            for (int k = 0; k < 4; ++k) {
                int nr = r + dr[k];
                int nc = c + dc[k];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                if (grid[nr][nc] == '#') continue;
                if (dist[nr][nc] != -1) continue;
                dist[nr][nc] = dist[r][c] + 1;
                q.emplace(nr, nc);
            }
        }

        // build output map
        vector<string> out = grid;
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                if (dist[i][j] != -1 && (long long)dist[i][j] < L)
                    out[i][j] = '.';

        // print map
        for (int i = 0; i < R; ++i)
            cout << out[i] << '\n';

        // check remaining fires
        bool anyFire = false;
        for (int i = 0; i < R && !anyFire; ++i)
            for (int j = 0; j < C; ++j)
                if (out[i][j] == 'F') { anyFire = true; break; }

        if (!anyFire) {
            cout << '\n' << "All Fires Extinguished!\n";
        }
    }
    return 0;
}
