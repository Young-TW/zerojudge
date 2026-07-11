#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> board(9);
    for (int i = 0; i < 9; ++i) {
        cin >> board[i];
    }

    bool wrong = false;
    vector<vector<bool>> visited(9, vector<bool>(9, false));

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == '.' && !visited[i][j]) {
                queue<pair<int, int>> q;
                q.push(make_pair(i, j));
                visited[i][j] = true;
                vector<pair<int, int>> region;
                bool touch_B = false, touch_W = false;

                while (!q.empty()) {
                    pair<int, int> curr = q.front();
                    q.pop();
                    int x = curr.first;
                    int y = curr.second;
                    region.push_back(curr);

                    for (int k = 0; k < 4; ++k) {
                        int nx = x + dx[k];
                        int ny = y + dy[k];
                        if (nx >= 0 && nx < 9 && ny >= 0 && ny < 9) {
                            if (board[nx][ny] == '.') {
                                if (!visited[nx][ny]) {
                                    visited[nx][ny] = true;
                                    q.push(make_pair(nx, ny));
                                }
                            } else if (board[nx][ny] == 'B') {
                                touch_B = true;
                            } else if (board[nx][ny] == 'W') {
                                touch_W = true;
                            }
                        }
                    }
                }

                if (touch_B && touch_W) {
                    wrong = true;
                } else if (touch_B) {
                    for (size_t k = 0; k < region.size(); ++k) {
                        board[region[k].first][region[k].second] = 'B';
                    }
                } else if (touch_W) {
                    for (size_t k = 0; k < region.size(); ++k) {
                        board[region[k].first][region[k].second] = 'W';
                    }
                }
            }
        }
    }

    if (wrong) {
        cout << "Wrong\n//中間那塊被B和W圍著(此行不須輸出)\n";
        return 0;
    }

    int count_B = 0, count_W = 0;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == 'B') count_B++;
            else if (board[i][j] == 'W') count_W++;
        }
    }

    if (count_B > count_W) {
        cout << "Black wins!!\n";
    } else if (count_W > count_B) {
        cout << "White wins!!\n";
    } else {
        cout << "Draw\n";
    }

    cout << count_B << ":" << count_W << "\n";

    for (int i = 0; i < 9; ++i) {
        cout << board[i] << "\n";
    }

    return 0;
}
