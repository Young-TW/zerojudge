#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

int R, C;
vector<string> grid;
string best;
vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void dfs(int x, int y, vector<vector<bool>>& visited, string& current) {
    if (current.size() > best.size() || (current.size() == best.size() && current > best)) {
        best = current;
    }

    vector<pair<int, pair<int, int>>> neighbors;
    for (auto& dir : directions) {
        int nx = x + dir.first;
        int ny = y + dir.second;
        if (nx >= 0 && nx < R && ny >= 0 && ny < C && grid[nx][ny] != '#' && !visited[nx][ny]) {
            neighbors.push_back({grid[nx][ny] - '0', {nx, ny}});
        }
    }

    sort(neighbors.rbegin(), neighbors.rend());

    for (auto& neighbor : neighbors) {
        int nx = neighbor.second.first;
        int ny = neighbor.second.second;
        visited[nx][ny] = true;
        current.push_back(grid[nx][ny]);
        dfs(nx, ny, visited, current);
        current.pop_back();
        visited[nx][ny] = false;
    }
}

int main() {
    while (cin >> R >> C) {
        if (R == 0 && C == 0) break;
        grid.resize(R);
        for (int i = 0; i < R; ++i) {
            cin >> grid[i];
        }

        best = "";
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (grid[i][j] != '#') {
                    vector<vector<bool>> visited(R, vector<bool>(C, false));
                    string current;
                    current.push_back(grid[i][j]);
                    visited[i][j] = true;
                    dfs(i, j, visited, current);
                }
            }
        }
        cout << best << endl;
    }
    return 0;
}
