#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void solve() {
    string grid[10];
    for (int i = 0; i < 10; ++i) {
        cin >> grid[i];
    }

    int min_presses = 1000;

    for (int mask = 0; mask < 1024; ++mask) {
        int current[10][10];
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                current[i][j] = (grid[i][j] == 'O') ? 1 : 0;
            }
        }

        int presses = 0;
        auto press = [&](int r, int c) {
            presses++;
            current[r][c] ^= 1;
            if (r > 0) current[r - 1][c] ^= 1;
            if (r < 9) current[r + 1][c] ^= 1;
            if (c > 0) current[r][c - 1] ^= 1;
            if (c < 9) current[r][c + 1] ^= 1;
        };

        for (int j = 0; j < 10; ++j) {
            if (mask & (1 << j)) {
                press(0, j);
            }
        }

        for (int i = 1; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (current[i - 1][j]) {
                    press(i, j);
                }
            }
        }

        bool valid = true;
        for (int j = 0; j < 10; ++j) {
            if (current[9][j]) {
                valid = false;
                break;
            }
        }

        if (valid) {
            min_presses = min(min_presses, presses);
        }
    }

    cout << min_presses << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
