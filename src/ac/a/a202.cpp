#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x, y;
    while (cin >> x >> y) {
        vector<string> gap(y);
        for (int i = 0; i < y; ++i) cin >> gap[i];

        bool error = false;

        // 1. length and character check
        for (int i = 0; i < y && !error; ++i) {
            if ((int)gap[i].size() != x) { error = true; break; }
            for (char c : gap[i])
                if (c != 'O' && c != 'P') { error = true; break; }
        }

        // 2. no two adjacent bars on the same level
        for (int j = 0; j < x && !error; ++j) {
            for (int i = 0; i + 1 < y; ++i) {
                if (gap[i][j] == 'O' && gap[i + 1][j] == 'O') {
                    error = true;
                    break;
                }
            }
        }

        if (error) {
            cout << "ERROR\n";
            continue;
        }

        // simulation
        vector<char> cur(y + 1);
        for (int i = 0; i <= y; ++i) cur[i] = char('A' + i);

        for (int j = 0; j < x; ++j) {
            for (int i = 0; i < y; ++i) {
                if (gap[i][j] == 'O')
                    swap(cur[i], cur[i + 1]);
            }
        }

        // output picture
        for (int i = 0; i <= y; ++i) {
            cout << char('A' + i);
            for (int j = 0; j < x; ++j) cout << '-';
            cout << cur[i] << "\n";

            if (i == y) break;               // no connector after last line
            cout << ' ';
            for (int j = 0; j < x; ++j) {
                cout << (gap[i][j] == 'O' ? '|' : ' ');
            }
            cout << "\n";
        }
        cout << string(x, ' ') << "\n";
    }
    return 0;
}
