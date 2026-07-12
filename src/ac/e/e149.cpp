#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool check_win(char c, const vector<string>& board) {
    int dx[] = {0, 1, 1, 1};
    int dy[] = {1, 0, 1, -1};
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (board[i][j] == c) {
                for (int k = 0; k < 4; ++k) {
                    int cnt = 1;
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    while (ni >= 0 && ni < 6 && nj >= 0 && nj < 6 && board[ni][nj] == c) {
                        cnt++;
                        ni += dx[k];
                        nj += dy[k];
                    }
                    if (cnt >= 5) return true;
                }
            }
        }
    }
    return false;
}

bool check_valid_win(char c, vector<string>& board) {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (board[i][j] == c) {
                board[i][j] = 'X';
                if (!check_win(c, board)) {
                    board[i][j] = c;
                    return true;
                }
                board[i][j] = c;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        while (n--) {
            vector<string> board(6);
            int count_B = 0, count_W = 0;
            for (int i = 0; i < 6; ++i) {
                cin >> board[i];
                for (int j = 0; j < 6; ++j) {
                    if (board[i][j] == 'B') count_B++;
                    else if (board[i][j] == 'W') count_W++;
                }
            }
            
            bool B_win = check_win('B', board);
            bool W_win = check_win('W', board);
            
            bool valid = false;
            if (B_win && W_win) {
                valid = false;
            } else if (B_win) {
                if (count_B == count_W + 1) {
                    valid = check_valid_win('B', board);
                }
            } else if (W_win) {
                if (count_W == count_B) {
                    valid = check_valid_win('W', board);
                }
            } else {
                if (count_B == count_W || count_B == count_W + 1) valid = true;
            }
            
            cout << (valid ? 'Y' : 'N') << "\n";
        }
    }
    return 0;
}
