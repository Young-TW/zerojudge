#include <iostream>

using namespace std;

int board[9][9];
int row_mask[9], col_mask[9], box_mask[9];
int solutions;

int popcount(int x) {
    int cnt = 0;
    while (x) {
        x &= x - 1;
        cnt++;
    }
    return cnt;
}

void dfs() {
    if (solutions >= 2) return;
    
    int best_r = -1, best_c = -1, best_cnt = 10, best_mask = 0;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == 0) {
                int b = (i / 3) * 3 + j / 3;
                int used = row_mask[i] | col_mask[j] | box_mask[b];
                int available = (~used) & 0x3FE;
                int cnt = popcount(available);
                if (cnt < best_cnt) {
                    best_cnt = cnt;
                    best_r = i;
                    best_c = j;
                    best_mask = available;
                    if (cnt == 0) return;
                    if (cnt == 1) break;
                }
            }
        }
        if (best_cnt == 1) break;
    }
    
    if (best_r == -1) {
        solutions++;
        return;
    }
    
    int r = best_r, c = best_c;
    int b = (r / 3) * 3 + c / 3;
    int available = best_mask;
    
    for (int val = 1; val <= 9; ++val) {
        if (available & (1 << val)) {
            board[r][c] = val;
            row_mask[r] |= (1 << val);
            col_mask[c] |= (1 << val);
            box_mask[b] |= (1 << val);
            
            dfs();
            
            board[r][c] = 0;
            row_mask[r] &= ~(1 << val);
            col_mask[c] &= ~(1 << val);
            box_mask[b] &= ~(1 << val);
            
            if (solutions >= 2) return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int case_num = 1;
    while (cin >> board[0][0]) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (i == 0 && j == 0) continue;
                cin >> board[i][j];
            }
        }
        
        bool illegal = false;
        for (int i = 0; i < 9; ++i) {
            int r_mask = 0, c_mask = 0;
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] != 0) {
                    if (r_mask & (1 << board[i][j])) illegal = true;
                    r_mask |= (1 << board[i][j]);
                }
                if (board[j][i] != 0) {
                    if (c_mask & (1 << board[j][i])) illegal = true;
                    c_mask |= (1 << board[j][i]);
                }
            }
        }
        for (int r = 0; r < 9; r += 3) {
            for (int c = 0; c < 9; c += 3) {
                int b_mask = 0;
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if (board[r+i][c+j] != 0) {
                            if (b_mask & (1 << board[r+i][c+j])) illegal = true;
                            b_mask |= (1 << board[r+i][c+j]);
                        }
                    }
                }
            }
        }
        
        cout << "Case " << case_num << ": ";
        if (illegal) {
            cout << "Illegal.\n";
        } else {
            for (int i = 0; i < 9; ++i) {
                row_mask[i] = col_mask[i] = box_mask[i] = 0;
            }
            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    if (board[i][j] != 0) {
                        int val = board[i][j];
                        int b = (i / 3) * 3 + j / 3;
                        row_mask[i] |= (1 << val);
                        col_mask[j] |= (1 << val);
                        box_mask[b] |= (1 << val);
                    }
                }
            }
            solutions = 0;
            dfs();
            if (solutions == 0) cout << "Impossible.\n";
            else if (solutions == 1) cout << "Unique.\n";
            else cout << "Ambiguous.\n";
        }
        case_num++;
    }
    
    return 0;
}
