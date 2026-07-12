#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, N;
int grid[9][9];
int row_mask[9];
int col_mask[9];
int box_mask[9];

int get_box_index(int r, int c) {
    return (r / n) * n + (c / n);
}

bool dfs() {
    int best_r = -1, best_c = -1;
    int min_choices = 10;
    int best_mask = 0;

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (grid[r][c] == 0) {
                int b = get_box_index(r, c);
                int mask = row_mask[r] & col_mask[c] & box_mask[b];
                int choices = __builtin_popcount(mask);
                if (choices == 0) return false;
                if (choices < min_choices) {
                    min_choices = choices;
                    best_r = r;
                    best_c = c;
                    best_mask = mask;
                    if (choices == 1) break;
                }
            }
        }
        if (min_choices == 1) break;
    }

    if (best_r == -1) {
        return true;
    }

    int r = best_r, c = best_c;
    int b = get_box_index(r, c);
    int mask = best_mask;

    for (int i = 0; i < N; ++i) {
        if (mask & (1 << i)) {
            int val = i + 1;
            grid[r][c] = val;
            row_mask[r] ^= (1 << i);
            col_mask[c] ^= (1 << i);
            box_mask[b] ^= (1 << i);

            if (dfs()) return true;

            grid[r][c] = 0;
            row_mask[r] ^= (1 << i);
            col_mask[c] ^= (1 << i);
            box_mask[b] ^= (1 << i);
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> n) {
        N = n * n;
        int full_mask = (1 << N) - 1;
        for (int i = 0; i < N; ++i) {
            row_mask[i] = full_mask;
            col_mask[i] = full_mask;
            box_mask[i] = full_mask;
        }

        bool valid = true;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> grid[i][j];
                if (grid[i][j] != 0) {
                    int val = grid[i][j];
                    int bit = val - 1;
                    int b = get_box_index(i, j);
                    if (!((row_mask[i] & (1 << bit)) && (col_mask[j] & (1 << bit)) && (box_mask[b] & (1 << bit)))) {
                        valid = false;
                    }
                    row_mask[i] ^= (1 << bit);
                    col_mask[j] ^= (1 << bit);
                    box_mask[b] ^= (1 << bit);
                }
            }
        }

        if (!valid) {
            cout << "NO SOLUTION\n";
            continue;
        }

        if (dfs()) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    cout << grid[i][j] << (j == N - 1 ? "" : " ");
                }
                cout << "\n";
            }
        } else {
            cout << "NO SOLUTION\n";
        }
    }

    return 0;
}
