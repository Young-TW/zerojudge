#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    vector<string> grid;
    int M_size = 0, N_size = 0;
    
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        char cmd;
        if (!(ss >> cmd)) continue;
        
        if (cmd == 'X') {
            break;
        } else if (cmd == 'I') {
            int M, N;
            ss >> M >> N;
            M_size = M;
            N_size = N;
            grid.assign(N, string(M, 'O'));
        } else if (cmd == 'C') {
            for (int i = 0; i < N_size; ++i) {
                fill(grid[i].begin(), grid[i].end(), 'O');
            }
        } else if (cmd == 'L') {
            int X, Y; char C;
            ss >> X >> Y >> C;
            if (X >= 1 && X <= M_size && Y >= 1 && Y <= N_size) {
                grid[Y-1][X-1] = C;
            }
        } else if (cmd == 'V') {
            int X, Y1, Y2; char C;
            ss >> X >> Y1 >> Y2 >> C;
            if (Y1 > Y2) swap(Y1, Y2);
            for (int y = Y1; y <= Y2; ++y) {
                if (X >= 1 && X <= M_size && y >= 1 && y <= N_size) {
                    grid[y-1][X-1] = C;
                }
            }
        } else if (cmd == 'H') {
            int X1, X2, Y; char C;
            ss >> X1 >> X2 >> Y >> C;
            if (X1 > X2) swap(X1, X2);
            for (int x = X1; x <= X2; ++x) {
                if (x >= 1 && x <= M_size && Y >= 1 && Y <= N_size) {
                    grid[Y-1][x-1] = C;
                }
            }
        } else if (cmd == 'K') {
            int X1, Y1, X2, Y2; char C;
            ss >> X1 >> Y1 >> X2 >> Y2 >> C;
            if (X1 > X2) swap(X1, X2);
            if (Y1 > Y2) swap(Y1, Y2);
            for (int y = Y1; y <= Y2; ++y) {
                for (int x = X1; x <= X2; ++x) {
                    if (x >= 1 && x <= M_size && y >= 1 && y <= N_size) {
                        grid[y-1][x-1] = C;
                    }
                }
            }
        } else if (cmd == 'F') {
            int X, Y; char C;
            ss >> X >> Y >> C;
            if (X >= 1 && X <= M_size && Y >= 1 && Y <= N_size) {
                int start_x = X - 1;
                int start_y = Y - 1;
                char target_color = grid[start_y][start_x];
                if (target_color != C) {
                    queue<pair<int, int>> q;
                    q.push({start_x, start_y});
                    grid[start_y][start_x] = C;
                    int dx[] = {0, 0, 1, -1};
                    int dy[] = {1, -1, 0, 0};
                    while (!q.empty()) {
                        pair<int, int> curr = q.front();
                        q.pop();
                        for (int i = 0; i < 4; ++i) {
                            int nx = curr.first + dx[i];
                            int ny = curr.second + dy[i];
                            if (nx >= 0 && nx < M_size && ny >= 0 && ny < N_size) {
                                if (grid[ny][nx] == target_color) {
                                    grid[ny][nx] = C;
                                    q.push({nx, ny});
                                }
                            }
                        }
                    }
                }
            }
        } else if (cmd == 'S') {
            string Name;
            ss >> Name;
            cout << Name << "\n";
            for (int i = 0; i < N_size; ++i) {
                cout << grid[i] << "\n";
            }
        } else {
            // Ignore the line
        }
    }
    
    return 0;
}
