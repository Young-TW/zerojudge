#include <iostream>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

int manhattan[16][16];

bool is_solvable(const int board[16]) {
    int inversions = 0;
    int zero_row = 0;
    for (int i = 0; i < 16; ++i) {
        if (board[i] == 0) {
            zero_row = i / 4;
        } else {
            for (int j = i + 1; j < 16; ++j) {
                if (board[j] != 0 && board[i] > board[j]) {
                    inversions++;
                }
            }
        }
    }
    return (inversions + zero_row) % 2 == 1;
}

int compute_row_conf(const int board[16], int r) {
    int tar_col[4];
    int cnt = 0;
    for (int c = 0; c < 4; ++c) {
        int val = board[r * 4 + c];
        if (val != 0 && (val - 1) / 4 == r) {
            tar_col[cnt++] = (val - 1) % 4;
        }
    }
    int conflict = 0;
    for (int i = 0; i < cnt; ++i)
        for (int j = i + 1; j < cnt; ++j)
            if (tar_col[i] > tar_col[j]) conflict += 2;
    return conflict;
}

int compute_col_conf(const int board[16], int c) {
    int tar_row[4];
    int cnt = 0;
    for (int r = 0; r < 4; ++r) {
        int val = board[r * 4 + c];
        if (val != 0 && (val - 1) % 4 == c) {
            tar_row[cnt++] = (val - 1) / 4;
        }
    }
    int conflict = 0;
    for (int i = 0; i < cnt; ++i)
        for (int j = i + 1; j < cnt; ++j)
            if (tar_row[i] > tar_row[j]) conflict += 2;
    return conflict;
}

int solve(const int initial[16]) {
    if (!is_solvable(initial)) return -1;

    int board[16];
    memcpy(board, initial, sizeof(board));
    int zero_pos = 0;
    while (board[zero_pos] != 0) ++zero_pos;

    int md_sum = 0;
    for (int i = 0; i < 16; ++i) {
        if (board[i] != 0) md_sum += manhattan[board[i]][i];
    }

    int row_conf[4] = {0}, col_conf[4] = {0};
    int lc_sum = 0;
    for (int r = 0; r < 4; ++r) {
        row_conf[r] = compute_row_conf(board, r);
        lc_sum += row_conf[r];
    }
    for (int c = 0; c < 4; ++c) {
        col_conf[c] = compute_col_conf(board, c);
        lc_sum += col_conf[c];
    }

    int h0 = md_sum + lc_sum;
    if (h0 == 0) return 0;

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    const int opp[4] = {1, 0, 3, 2};

    int limit = h0;
    while (true) {
        auto dfs = [&](auto&& self, int g, int limit, int last_move) -> int {
            int f = g + md_sum + lc_sum;
            if (f > limit) return f;
            if (md_sum + lc_sum == 0) return -g;

            int min_f = INT_MAX;
            int r0 = zero_pos / 4;
            int c0 = zero_pos % 4;

            struct Move { int dir, nr, nc, delta_md; };
            Move moves[4];
            int move_cnt = 0;
            for (int dir = 0; dir < 4; ++dir) {
                if (last_move != -1 && dir == opp[last_move]) continue;
                int nr = r0 + dr[dir];
                int nc = c0 + dc[dir];
                if (nr < 0 || nr >= 4 || nc < 0 || nc >= 4) continue;
                int new_zero = nr * 4 + nc;
                int tile = board[new_zero];
                int delta_md = manhattan[tile][zero_pos] - manhattan[tile][new_zero];
                moves[move_cnt++] = {dir, nr, nc, delta_md};
            }
            sort(moves, moves + move_cnt, [](const Move& a, const Move& b) {
                return a.delta_md < b.delta_md;
            });

            for (int i = 0; i < move_cnt; ++i) {
                int dir = moves[i].dir;
                int nr = moves[i].nr;
                int nc = moves[i].nc;
                int new_zero = nr * 4 + nc;
                int tile = board[new_zero];
                int delta_md = moves[i].delta_md;

                int row_indices[2], col_indices[2];
                int row_cnt = 0, col_cnt = 0;
                if (r0 != nr) {
                    row_indices[row_cnt++] = r0;
                    row_indices[row_cnt++] = nr;
                } else {
                    row_indices[row_cnt++] = r0;
                }
                if (c0 != nc) {
                    col_indices[col_cnt++] = c0;
                    col_indices[col_cnt++] = nc;
                } else {
                    col_indices[col_cnt++] = c0;
                }

                int old_md_sum = md_sum;
                int old_lc_sum = lc_sum;
                int old_zero = zero_pos;
                int old_row_conf[2], old_col_conf[2];
                for (int j = 0; j < row_cnt; ++j) old_row_conf[j] = row_conf[row_indices[j]];
                for (int j = 0; j < col_cnt; ++j) old_col_conf[j] = col_conf[col_indices[j]];
                int old_lc_part = 0;
                for (int j = 0; j < row_cnt; ++j) old_lc_part += old_row_conf[j];
                for (int j = 0; j < col_cnt; ++j) old_lc_part += old_col_conf[j];

                swap(board[zero_pos], board[new_zero]);
                zero_pos = new_zero;
                md_sum += delta_md;

                int new_lc_part = 0;
                for (int j = 0; j < row_cnt; ++j) {
                    int r = row_indices[j];
                    int val = compute_row_conf(board, r);
                    row_conf[r] = val;
                    new_lc_part += val;
                }
                for (int j = 0; j < col_cnt; ++j) {
                    int c = col_indices[j];
                    int val = compute_col_conf(board, c);
                    col_conf[c] = val;
                    new_lc_part += val;
                }
                lc_sum = lc_sum - old_lc_part + new_lc_part;

                if (md_sum + lc_sum == 0) return -(g + 1);

                int new_f = g + 1 + md_sum + lc_sum;
                if (new_f > limit) {
                    if (new_f < min_f) min_f = new_f;
                } else {
                    int res = self(self, g + 1, limit, dir);
                    if (res < 0) return res;
                    if (res < min_f) min_f = res;
                }

                swap(board[old_zero], board[new_zero]);
                zero_pos = old_zero;
                md_sum = old_md_sum;
                lc_sum = old_lc_sum;
                for (int j = 0; j < row_cnt; ++j) row_conf[row_indices[j]] = old_row_conf[j];
                for (int j = 0; j < col_cnt; ++j) col_conf[col_indices[j]] = old_col_conf[j];
            }
            return min_f;
        };

        int res = dfs(dfs, 0, limit, -1);
        if (res < 0) return -res;
        if (res == INT_MAX) return -1;
        limit = res;
        if (limit > 500) return -1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 16; ++i) {
        for (int v = 0; v < 16; ++v) {
            if (v == 0) manhattan[v][i] = 0;
            else {
                int tr = (v - 1) / 4;
                int tc = (v - 1) % 4;
                int r = i / 4;
                int c = i % 4;
                manhattan[v][i] = abs(r - tr) + abs(c - tc);
            }
        }
    }

    int T;
    while (cin >> T) {
        while (T--) {
            int board[16];
            for (int i = 0; i < 16; ++i) cin >> board[i];
            int ans = solve(board);
            if (ans == -1) cout << "This puzzle is not solvable.\n";
            else cout << ans << '\n';
        }
    }
    return 0;
}
