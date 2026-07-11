#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct Wizard {
    int r, c, s, t;
    bool alive;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    while (cin >> n >> m >> k) {
        vector<Wizard> wizards(k);
        for (int i = 0; i < k; ++i) {
            cin >> wizards[i].r >> wizards[i].c >> wizards[i].s >> wizards[i].t;
            wizards[i].alive = true;
        }

        vector<vector<int>> bomb(n, vector<int>(m, 0));
        vector<vector<int>> next_bomb(n, vector<int>(m, 0));

        bool has_wizard;
        do {
            has_wizard = false;
            next_bomb.assign(n, vector<int>(m, 0));

            for (int i = 0; i < k; ++i) {
                if (!wizards[i].alive) continue;
                has_wizard = true;
                int r = wizards[i].r;
                int c = wizards[i].c;
                if (r >= 0 && r < n && c >= 0 && c < m) {
                    bomb[r][c]++;
                }
            }

            for (int i = 0; i < k; ++i) {
                if (!wizards[i].alive) continue;
                wizards[i].r += wizards[i].s;
                wizards[i].c += wizards[i].t;
                int r = wizards[i].r;
                int c = wizards[i].c;
                if (r < 0 || r >= n || c < 0 || c >= m) {
                    wizards[i].alive = false;
                } else if (bomb[r][c] > 0) {
                    wizards[i].alive = false;
                    next_bomb[r][c] = 1;
                }
            }

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (bomb[i][j] > 0 && next_bomb[i][j] == 0) {
                        next_bomb[i][j] = 1;
                    }
                }
            }

            bomb = next_bomb;
        } while (has_wizard);

        int count = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (bomb[i][j] > 0) {
                    count++;
                }
            }
        }
        cout << count << '\n';
    }

    return 0;
}
