#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

bool isKo(int r, int c, char color, const vector<string>& grid) {
    int n = grid.size();
    char opp = (color == 'O' ? 'X' : 'O');
    vector<string> temp = grid;
    temp[r][c] = color;

    int total_removed = 0;
    bool visited[20][20] = {};
    vector<vector<pair<int,int> > > groups_to_remove;

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    // 找出所有無氣的對方棋子組
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (temp[i][j] == opp && !visited[i][j]) {
                vector<pair<int,int> > group;
                vector<pair<int,int> > q;
                q.push_back({i, j});
                visited[i][j] = true;
                int head = 0;
                while (head < (int)q.size()) {
                    int cr = q[head].first;
                    int cc = q[head].second;
                    head++;
                    group.push_back({cr, cc});
                    for (int d = 0; d < 4; ++d) {
                        int nr = cr + dr[d];
                        int nc = cc + dc[d];
                        if (nr >= 0 && nr < n && nc >= 0 && nc < n && temp[nr][nc] == opp && !visited[nr][nc]) {
                            visited[nr][nc] = true;
                            q.push_back({nr, nc});
                        }
                    }
                }

                // 計算該組的氣
                bool lib_visited[20][20] = {};
                int liberties = 0;
                for (auto& p : group) {
                    int gr = p.first;
                    int gc = p.second;
                    for (int d = 0; d < 4; ++d) {
                        int nr = gr + dr[d];
                        int nc = gc + dc[d];
                        if (nr >= 0 && nr < n && nc >= 0 && nc < n && temp[nr][nc] == '.') {
                            if (!lib_visited[nr][nc]) {
                                lib_visited[nr][nc] = true;
                                ++liberties;
                            }
                        }
                    }
                }

                if (liberties == 0) {
                    groups_to_remove.push_back(group);
                    total_removed += group.size();
                }
            }
        }
    }

    // 移除無氣組
    for (auto& group : groups_to_remove) {
        for (auto& p : group) {
            temp[p.first][p.second] = '.';
        }
    }

    if (total_removed != 1) return false;

    // 檢查所有己方組的氣，並找到包含 (r,c) 的組
    bool visited2[20][20] = {};
    int myGroupSize = 0;
    int myGroupLiberties = 0;
    bool foundMyGroup = false;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (temp[i][j] == color && !visited2[i][j]) {
                vector<pair<int,int> > group;
                vector<pair<int,int> > q;
                q.push_back({i, j});
                visited2[i][j] = true;
                int head = 0;
                while (head < (int)q.size()) {
                    int cr = q[head].first;
                    int cc = q[head].second;
                    head++;
                    group.push_back({cr, cc});
                    for (int d = 0; d < 4; ++d) {
                        int nr = cr + dr[d];
                        int nc = cc + dc[d];
                        if (nr >= 0 && nr < n && nc >= 0 && nc < n && temp[nr][nc] == color && !visited2[nr][nc]) {
                            visited2[nr][nc] = true;
                            q.push_back({nr, nc});
                        }
                    }
                }

                // 計算該組氣
                bool lib_visited[20][20] = {};
                int liberties = 0;
                for (auto& p : group) {
                    int gr = p.first;
                    int gc = p.second;
                    for (int d = 0; d < 4; ++d) {
                        int nr = gr + dr[d];
                        int nc = gc + dc[d];
                        if (nr >= 0 && nr < n && nc >= 0 && nc < n && temp[nr][nc] == '.') {
                            if (!lib_visited[nr][nc]) {
                                lib_visited[nr][nc] = true;
                                ++liberties;
                            }
                        }
                    }
                }

                if (liberties == 0) {
                    return false; // 有己方棋子無氣，非法下子
                }

                bool contains = false;
                for (auto& p : group) {
                    if (p.first == r && p.second == c) {
                        contains = true;
                        break;
                    }
                }
                if (contains) {
                    myGroupSize = group.size();
                    myGroupLiberties = liberties;
                    foundMyGroup = true;
                }
            }
        }
    }

    if (!foundMyGroup) return false;

    // 打劫條件：提掉對方一子，且我方落子所在組只剩一氣，且該組僅有此落子（孤立）
    if (total_removed == 1 && myGroupLiberties == 1 && myGroupSize == 1) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    int caseNo = 1;
    while (cin >> n && n != 0) {
        vector<string> rows(n);
        for (int i = 0; i < n; ++i) {
            cin >> rows[i];
        }

        // 翻轉棋盤，使 grid[0][0] 對應 (1,1)
        vector<string> grid(n, string(n, '.'));
        for (int i = 0; i < n; ++i) {
            int r = n - i - 1; // y = n - i
            for (int j = 0; j < n; ++j) {
                grid[r][j] = rows[i][j];
            }
        }

        vector<pair<int,int> > koPoints;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] != '.') continue;
                if (isKo(r, c, 'O', grid) || isKo(r, c, 'X', grid)) {
                    koPoints.push_back({c + 1, r + 1}); // x = c+1, y = r+1
                }
            }
        }

        sort(koPoints.begin(), koPoints.end());
        cout << "Case " << caseNo << ":\n";
        if (koPoints.empty()) {
            cout << "Peace!!\n";
        } else {
            for (auto& p : koPoints) {
                cout << p.first << ' ' << p.second << '\n';
            }
        }
        ++caseNo;
    }
    return 0;
}
