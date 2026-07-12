#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

int m, n, h;
bool is_pile[105][105];
set<int> lines_at[105][105];
map<int, vector<pair<int, int>>> active_lines;
int current_area = 0;
int max_area = 0;
int line_id_counter = 0;

void remove_line(int id) {
    if (active_lines.find(id) == active_lines.end()) return;
    for (auto& p : active_lines[id]) {
        int r = p.first, c = p.second;
        lines_at[r][c].erase(id);
        if (lines_at[r][c].empty() && !is_pile[r][c]) {
            current_area--;
        }
    }
    active_lines.erase(id);
}

void add_line(int r1, int c1, int r2, int c2) {
    int id = line_id_counter++;
    vector<pair<int, int>> cells;
    if (r1 == r2) {
        for (int c = min(c1, c2); c <= max(c1, c2); c++) {
            cells.push_back({r1, c});
        }
    } else {
        for (int r = min(r1, r2); r <= max(r1, r2); r++) {
            cells.push_back({r, c1});
        }
    }
    for (auto& p : cells) {
        int r = p.first, c = p.second;
        if (lines_at[r][c].empty() && !is_pile[r][c]) {
            current_area++;
        }
        lines_at[r][c].insert(id);
    }
    active_lines[id] = cells;
}

void add_pile(int r, int c) {
    vector<int> to_remove(lines_at[r][c].begin(), lines_at[r][c].end());
    for (int id : to_remove) {
        remove_line(id);
    }
    bool was_occupied = !lines_at[r][c].empty() || is_pile[r][c];
    if (!was_occupied) {
        current_area++;
    }
    is_pile[r][c] = true;

    for (int i = r - 1; i >= 0; i--) {
        if (is_pile[i][c]) {
            add_line(i, c, r, c);
            break;
        }
    }
    for (int i = r + 1; i < m; i++) {
        if (is_pile[i][c]) {
            add_line(i, c, r, c);
            break;
        }
    }
    for (int j = c - 1; j >= 0; j--) {
        if (is_pile[r][j]) {
            add_line(r, j, r, c);
            break;
        }
    }
    for (int j = c + 1; j < n; j++) {
        if (is_pile[r][j]) {
            add_line(r, j, r, c);
            break;
        }
    }
}

void remove_pile(int r, int c) {
    vector<int> to_remove(lines_at[r][c].begin(), lines_at[r][c].end());
    for (int id : to_remove) {
        remove_line(id);
    }
    is_pile[r][c] = false;
    current_area--;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> m >> n >> h) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                is_pile[i][j] = false;
                lines_at[i][j].clear();
            }
        }
        active_lines.clear();
        current_area = 0;
        max_area = 0;
        line_id_counter = 0;

        for (int i = 0; i < h; i++) {
            int r, c, t;
            cin >> r >> c >> t;
            if (t == 0) {
                add_pile(r, c);
            } else {
                remove_pile(r, c);
            }
            if (current_area > max_area) {
                max_area = current_area;
            }
        }
        cout << max_area << "\n" << current_area << "\n";
    }
    return 0;
}
