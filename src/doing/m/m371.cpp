#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <queue>
using namespace std;

int n, m;
vector<vector<int>> grid;
vector<pair<int, int>> positions;
unordered_map<int, vector<pair<int, int>>> pos_map;

bool can_remove(int x1, int y1, int x2, int y2) {
    if (x1 == x2) {
        int start = min(y1, y2);
        int end = max(y1, y2);
        for (int y = start + 1; y < end; ++y) {
            if (grid[x1][y] != -1) return false;
        }
        return true;
    } else if (y1 == y2) {
        int start = min(x1, x2);
        int end = max(x1, x2);
        for (int x = start + 1; x < end; ++x) {
            if (grid[x][y1] != -1) return false;
        }
        return true;
    }
    return false;
}

int solve() {
    int total = 0;
    while (true) {
        bool found = false;
        for (auto& entry : pos_map) {
            if (entry.second.size() < 2) continue;
            auto p1 = entry.second[0];
            auto p2 = entry.second[1];
            if (can_remove(p1.first, p1.second, p2.first, p2.second)) {
                total += grid[p1.first][p1.second];
                grid[p1.first][p1.second] = -1;
                grid[p2.first][p2.second] = -1;
                pos_map.erase(entry.first);
                found = true;
                break;
            }
        }
        if (!found) break;
    }
    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> m) {
        grid.assign(n, vector<int>(m));
        pos_map.clear();
        positions.clear();

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> grid[i][j];
                if (grid[i][j] != 0) {
                    pos_map[grid[i][j]].emplace_back(i, j);
                }
            }
        }

        cout << solve() << '\n';
    }

    return 0;
}
