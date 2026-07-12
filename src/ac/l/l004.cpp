#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h;
    while (cin >> h) {
        if (h <= 0) {
            cout << "雙方和棋\n";
            continue;
        }

        int T;
        if (!(cin >> T)) break;

        if (T <= 0) {
            cout << "雙方和棋\n";
            continue;
        }

        vector<vector<int>> board(T, vector<int>(T, 0));
        for (int i = 0; i < T; ++i) {
            for (int j = 0; j < T; ++j) {
                string s;
                cin >> s;
                if (s != "-") {
                    board[i][j] = stoi(s);
                }
            }
        }

        int min_win_step = INT_MAX;
        int win_color = -1; // 1 for black, 0 for white
        int win_dir = -1;   // 0: vertical, 1: horizontal, 2: diagonal

        int dr[] = {0, 1, 1, 1};
        int dc[] = {1, 0, 1, -1};
        int dir_type[] = {1, 0, 2, 2}; // 1: horizontal, 0: vertical, 2: diagonal

        for (int i = 0; i < T; ++i) {
            for (int j = 0; j < T; ++j) {
                if (board[i][j] == 0) continue;
                int color = board[i][j] % 2;
                for (int d = 0; d < 4; ++d) {
                    int end_r = i + dr[d] * (h - 1);
                    int end_c = j + dc[d] * (h - 1);
                    if (end_r < 0 || end_r >= T || end_c < 0 || end_c >= T) continue;

                    bool valid = true;
                    int max_step = 0;
                    for (int k = 0; k < h; ++k) {
                        int val = board[i + dr[d] * k][j + dc[d] * k];
                        if (val == 0 || val % 2 != color) {
                            valid = false;
                            break;
                        }
                        if (val > max_step) max_step = val;
                        if (max_step >= min_win_step) {
                            valid = false;
                            break;
                        }
                    }
                    if (valid) {
                        if (max_step < min_win_step) {
                            min_win_step = max_step;
                            win_color = color;
                            win_dir = dir_type[d];
                        }
                    }
                }
            }
        }

        if (min_win_step == INT_MAX) {
            cout << "雙方和棋\n";
        } else {
            if (win_color == 1) {
                cout << "黑方勝利\n";
            } else {
                cout << "白方勝利\n";
            }
            if (win_dir == 0) {
                cout << "勝利方式為直\n";
            } else if (win_dir == 1) {
                cout << "勝利方式為橫\n";
            } else {
                cout << "勝利方式為斜\n";
            }
            cout << "在第" << min_win_step << "步獲勝\n";
        }
    }

    return 0;
}
