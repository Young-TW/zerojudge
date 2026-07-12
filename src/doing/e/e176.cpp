#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

int main() {
    int n;
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    
    while (cin >> n && n != 0) {
        vector<string> board(n);
        for (int i = 0; i < n; i++) cin >> board[i];
        
        // board[row][col]: row 0 = top (y=n 1-indexed), row n-1 = bottom (y=1)
        // 0-indexed: x=col, y=row; 1-indexed: x=col+1, y=n-row
        
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        // each entry: {size, libX1, libY1, libX0, libY0}
        vector<vector<int>> atariGroups;
        
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (board[row][col] == 'O' && !visited[row][col]) {
                    vector<pair<int,int>> stones;
                    queue<pair<int,int>> q;
                    q.push(make_pair(col, row));
                    visited[row][col] = true;
                    while (!q.empty()) {
                        pair<int,int> cur = q.front(); q.pop();
                        stones.push_back(cur);
                        int x = cur.first, y = cur.second;
                        for (int d = 0; d < 4; d++) {
                            int nx = x + dx[d], ny = y + dy[d];
                            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                            if (board[ny][nx] == 'O' && !visited[ny][nx]) {
                                visited[ny][nx] = true;
                                q.push(make_pair(nx, ny));
                            }
                        }
                    }
                    // collect unique liberties
                    vector<vector<bool>> libVis(n, vector<bool>(n, false));
                    vector<pair<int,int>> libs;
                    for (size_t i = 0; i < stones.size(); i++) {
                        int x = stones[i].first, y = stones[i].second;
                        for (int d = 0; d < 4; d++) {
                            int nx = x + dx[d], ny = y + dy[d];
                            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                            if (board[ny][nx] == '.' && !libVis[ny][nx]) {
                                libVis[ny][nx] = true;
                                libs.push_back(make_pair(nx, ny));
                            }
                        }
                    }
                    if (libs.size() == 1) {
                        int libX0 = libs[0].first, libY0 = libs[0].second;
                        int libX1 = libX0 + 1, libY1 = n - libY0;
                        vector<int> g;
                        g.push_back((int)stones.size());
                        g.push_back(libX1);
                        g.push_back(libY1);
                        g.push_back(libX0);
                        g.push_back(libY0);
                        atariGroups.push_back(g);
                    }
                }
            }
        }
        
        if (atariGroups.empty()) {
            cout << "T_T" << endl;
            continue;
        }
        
        int maxSize = 0;
        for (size_t i = 0; i < atariGroups.size(); i++)
            maxSize = max(maxSize, atariGroups[i][0]);
        
        int bestX1 = n + 1, bestY1 = n + 1, bestX0 = -1, bestY0 = -1;
        for (size_t i = 0; i < atariGroups.size(); i++) {
            if (atariGroups[i][0] == maxSize) {
                if (atariGroups[i][1] < bestX1 ||
                    (atariGroups[i][1] == bestX1 && atariGroups[i][2] < bestY1)) {
                    bestX1 = atariGroups[i][1];
                    bestY1 = atariGroups[i][2];
                    bestX0 = atariGroups[i][3];
                    bestY0 = atariGroups[i][4];
                }
            }
        }
        
        // Check legality: place O at (bestX0, bestY0), check if group has any liberty
        // Do not consider capturing opponent stones
        board[bestY0][bestX0] = 'O';
        vector<vector<bool>> vis2(n, vector<bool>(n, false));
        queue<pair<int,int>> q;
        q.push(make_pair(bestX0, bestY0));
        vis2[bestY0][bestX0] = true;
        bool hasLib = false;
        while (!q.empty()) {
            pair<int,int> cur = q.front(); q.pop();
            int x = cur.first, y = cur.second;
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                if (board[ny][nx] == '.') {
                    hasLib = true;
                } else if (board[ny][nx] == 'O' && !vis2[ny][nx]) {
                    vis2[ny][nx] = true;
                    q.push(make_pair(nx, ny));
                }
            }
        }
        board[bestY0][bestX0] = '.';
        
        if (hasLib) {
            cout << bestX1 << " " << bestY1 << endl;
        } else {
            cout << "T_T" << endl;
        }
    }
    return 0;
}
