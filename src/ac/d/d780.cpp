#include <iostream>
#include <algorithm>

using namespace std;

int grid[9][9];
int row_mask[9];
int col_mask[9];
int box_mask[9];
int max_score;
int weights[9][9];

inline int my_abs(int x) {
    return x < 0 ? -x : x;
}

void init_weights() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int dist = max(my_abs(i - 4), my_abs(j - 4));
            weights[i][j] = 10 - dist;
        }
    }
}

void dfs(int current_score) {
    int best_i = -1, best_j = -1;
    int min_options = 10;
    int best_avail = 0;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (grid[i][j] == 0) {
                int b = (i / 3) * 3 + (j / 3);
                int avail = row_mask[i] & col_mask[j] & box_mask[b];
                int count = __builtin_popcount(avail);
                if (count == 0) return;
                if (count < min_options) {
                    min_options = count;
                    best_i = i;
                    best_j = j;
                    best_avail = avail;
                    if (count == 1) {
                        i = 9;
                        break;
                    }
                }
            }
        }
    }

    if (best_i == -1) {
        if (current_score > max_score) {
            max_score = current_score;
        }
        return;
    }

    int i = best_i, j = best_j;
    int b = (i / 3) * 3 + (j / 3);
    int avail = best_avail;
    int weight = weights[i][j];

    while (avail) {
        int bit = avail & (-avail);
        avail ^= bit;
        int num = __builtin_ctz(bit);

        grid[i][j] = num;
        row_mask[i] ^= bit;
        col_mask[j] ^= bit;
        box_mask[b] ^= bit;

        dfs(current_score + weight * num);

        grid[i][j] = 0;
        row_mask[i] ^= bit;
        col_mask[j] ^= bit;
        box_mask[b] ^= bit;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init_weights();
    
    while (cin >> grid[0][0]) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (i == 0 && j == 0) continue;
                cin >> grid[i][j];
            }
        }

        for (int i = 0; i < 9; ++i) {
            row_mask[i] = (1 << 10) - 2;
            col_mask[i] = (1 << 10) - 2;
            box_mask[i] = (1 << 10) - 2;
        }

        int current_score = 0;
        bool valid = true;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (grid[i][j] != 0) {
                    int num = grid[i][j];
                    int bit = 1 << num;
                    int b = (i / 3) * 3 + (j / 3);
                    if ((row_mask[i] & bit) == 0 || (col_mask[j] & bit) == 0 || (box_mask[b] & bit) == 0) {
                        valid = false;
                    }
                    row_mask[i] ^= bit;
                    col_mask[j] ^= bit;
                    box_mask[b] ^= bit;
                    current_score += weights[i][j] * num;
                }
            }
        }

        if (!valid) {
            cout << -1 << "\n";
            continue;
        }

        max_score = -1;
        dfs(current_score);
        cout << max_score << "\n";
    }
    return 0;
}
