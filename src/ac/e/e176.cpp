#include <bits/stdc++.h>
using namespace std;

struct Candidate {
    int size;   // number of stones in the group
    int r, c;   // liberty position (0‑based row, column)
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int dr[4] = { -1, 1, 0, 0 };
    const int dc[4] = { 0, 0, -1, 1 };

    int n;
    while (cin >> n && n != 0) {
        vector<string> board(n);
        for (int i = 0; i < n; ++i) cin >> board[i];

        vector<vector<char>> visited(n, vector<char>(n, 0));
        vector<Candidate> candidates;

        // ----- find all atari black groups -----
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (board[r][c] != 'O' || visited[r][c]) continue;

                queue<pair<int,int>> q;
                q.emplace(r, c);
                visited[r][c] = 1;

                int stones = 0;
                bool libSeen[19][19] = {false};
                vector<pair<int,int>> libs;

                while (!q.empty()) {
                    auto cur = q.front(); q.pop();
                    ++stones;
                    int cr = cur.first, cc = cur.second;

                    for (int d = 0; d < 4; ++d) {
                        int nr = cr + dr[d];
                        int nc = cc + dc[d];
                        if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
                        if (board[nr][nc] == 'O' && !visited[nr][nc]) {
                            visited[nr][nc] = 1;
                            q.emplace(nr, nc);
                        } else if (board[nr][nc] == '.' && !libSeen[nr][nc]) {
                            libSeen[nr][nc] = true;
                            libs.emplace_back(nr, nc);
                        }
                    }
                }

                if (libs.size() == 1) {
                    Candidate cand;
                    cand.size = stones;
                    cand.r = libs[0].first;
                    cand.c = libs[0].second;
                    candidates.push_back(cand);
                }
            }
        }

        // ----- test legality of each candidate -----
        vector<Candidate> legal;
        for (const auto &cand : candidates) {
            int r = cand.r, c = cand.c;
            // place temporary stone
            board[r][c] = 'O';
            // BFS over the new black group
            vector<vector<char>> vis2(n, vector<char>(n, 0));
            queue<pair<int,int>> q;
            q.emplace(r, c);
            vis2[r][c] = 1;
            bool hasLiberty = false;

            while (!q.empty() && !hasLiberty) {
                auto cur = q.front(); q.pop();
                int cr = cur.first, cc = cur.second;
                for (int d = 0; d < 4; ++d) {
                    int nr = cr + dr[d];
                    int nc = cc + dc[d];
                    if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
                    if (board[nr][nc] == '.') {
                        hasLiberty = true;
                        break;
                    }
                    if (board[nr][nc] == 'O' && !vis2[nr][nc]) {
                        vis2[nr][nc] = 1;
                        q.emplace(nr, nc);
                    }
                }
            }
            board[r][c] = '.'; // revert

            if (hasLiberty) legal.push_back(cand);
        }

        if (legal.empty()) {
            cout << "T_T\n";
            continue;
        }

        // ----- choose the best legal candidate -----
        int bestSize = 0;
        for (const auto &c : legal) bestSize = max(bestSize, c.size);

        int bestX = n + 1, bestY = n + 1; // 1‑based
        for (const auto &c : legal) {
            if (c.size != bestSize) continue;
            int x = c.c + 1;
            int y = n - c.r;
            if (x < bestX || (x == bestX && y < bestY)) {
                bestX = x;
                bestY = y;
            }
        }
        cout << bestX << ' ' << bestY << "\n";
    }
    return 0;
}
