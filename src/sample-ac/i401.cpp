#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_Y = 60005;
const int MAX_X = 30005;

vector<pair<int, int>> rows[MAX_Y];
vector<pair<int, int>> cols[MAX_X];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        vector<int> used_rows;
        vector<int> used_cols;

        for (int i = 0; i < n; ++i) {
            int x, y, t;
            cin >> x >> y >> t;
            int row_idx = y + 30000;
            int col_idx = x;
            if (rows[row_idx].empty()) used_rows.push_back(row_idx);
            if (cols[col_idx].empty()) used_cols.push_back(col_idx);
            rows[row_idx].push_back({x, t});
            cols[col_idx].push_back({y, t});
        }

        for (int idx : used_rows) {
            sort(rows[idx].begin(), rows[idx].end());
        }
        for (int idx : used_cols) {
            sort(cols[idx].begin(), cols[idx].end());
        }

        int cx = 0, cy = 0;
        int dir = 0; // 0: right, 1: left, 2: up, 3: down
        int reflections = 0;

        int next_dir[2][4] = {
            {2, 3, 0, 1}, // t=0 (/)
            {3, 2, 1, 0}  // t=1 (\)
        };

        while (true) {
            if (dir == 0) { // right
                auto& vec = rows[cy + 30000];
                auto it = upper_bound(vec.begin(), vec.end(), make_pair(cx, 2));
                if (it == vec.end()) break;
                cx = it->first;
                int t = it->second;
                dir = next_dir[t][dir];
                reflections++;
            } else if (dir == 1) { // left
                auto& vec = rows[cy + 30000];
                auto it = lower_bound(vec.begin(), vec.end(), make_pair(cx, 0));
                if (it == vec.begin()) break;
                --it;
                cx = it->first;
                int t = it->second;
                dir = next_dir[t][dir];
                reflections++;
            } else if (dir == 2) { // up
                auto& vec = cols[cx];
                auto it = upper_bound(vec.begin(), vec.end(), make_pair(cy, 2));
                if (it == vec.end()) break;
                cy = it->first;
                int t = it->second;
                dir = next_dir[t][dir];
                reflections++;
            } else if (dir == 3) { // down
                auto& vec = cols[cx];
                auto it = lower_bound(vec.begin(), vec.end(), make_pair(cy, 0));
                if (it == vec.begin()) break;
                --it;
                cy = it->first;
                int t = it->second;
                dir = next_dir[t][dir];
                reflections++;
            }
        }

        cout << reflections << "\n";

        for (int idx : used_rows) {
            rows[idx].clear();
        }
        for (int idx : used_cols) {
            cols[idx].clear();
        }
    }

    return 0;
}
