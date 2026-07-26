#include <bits/stdc++.h>
using namespace std;

struct Wizard {
    int r, c, s, t;
    bool alive;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    while (cin >> n >> m >> k) {
        vector<Wizard> w(k);
        for (int i = 0; i < k; ++i) {
            cin >> w[i].r >> w[i].c >> w[i].s >> w[i].t;
            w[i].alive = true;
        }

        // bomb board
        static bool bomb[100][100];
        static bool explode[100][100];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                bomb[i][j] = false;

        vector<int> alive;
        alive.reserve(k);
        for (int i = 0; i < k; ++i) alive.push_back(i);

        while (!alive.empty()) {
            // 1. drop bombs
            for (int idx : alive) {
                int r = w[idx].r, c = w[idx].c;
                bomb[r][c] = true;
            }

            // 2. move wizards, decide deaths
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    explode[i][j] = false;

            vector<int> nextAlive;
            nextAlive.reserve(alive.size());

            for (int idx : alive) {
                int nr = w[idx].r + w[idx].s;
                int nc = w[idx].c + w[idx].t;

                if (nr < 0 || nr >= n || nc < 0 || nc >= m) {
                    // wizard disappears, nothing to do
                    continue;
                }
                if (bomb[nr][nc]) {
                    // steps onto a bomb -> both die, bomb explodes
                    explode[nr][nc] = true;
                } else {
                    // survives
                    w[idx].r = nr;
                    w[idx].c = nc;
                    nextAlive.push_back(idx);
                }
            }

            // 3. remove exploded bombs
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    if (explode[i][j]) bomb[i][j] = false;

            alive.swap(nextAlive);
        }

        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (bomb[i][j]) ++ans;
        cout << ans << '\n';
    }
    return 0;
}
