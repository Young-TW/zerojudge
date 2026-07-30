#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <map>
using namespace std;
struct State {
    vector<int> top;
    vector<int> bottom;
    int zero_top;
    int zero_bottom;
};
int N;
vector<int> target_top;
vector<int> target_bottom;
bool is_goal(const State& s) {
    for (int i = 0; i < N; ++i) {
        if (s.top[i] != target_top[i]) return false;
        if (s.bottom[i] != target_bottom[i]) return false;
    }
    return true;
}
string state_to_string(const State& s) {
    string res = "";
    for (int x : s.top) res += to_string(x) + ",";
    res += ";";
    for (int x : s.bottom) res += to_string(x) + ",";
    return res;
}
void solve() {
    if (N == 1) {
        cout << 0 << endl;
        return;
    }
    target_top.resize(N);
    target_bottom.resize(N);
    for (int i = 0; i < N; ++i) {
        target_top[i] = i;
        target_bottom[i] = i;
    }
    State start;
    start.top.resize(N);
    start.bottom.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> start.top[i];
        if (start.top[i] == 0) start.zero_top = i;
    }
    for (int i = 0; i < N; ++i) {
        cin >> start.bottom[i];
        if (start.bottom[i] == 0) start.zero_bottom = i;
    }
    if (is_goal(start)) {
        cout << 0 << endl;
        return;
    }
    queue<State> q;
    map<string, pair<State, vector<int>>> visited;
    map<string, string> parent;
    map<string, vector<int>> last_move;
    string start_key = state_to_string(start);
    q.push(start);
    parent[start_key] = ""; // 空字串代表起點
    last_move[start_key] = {};
    int steps = 0;
    bool found = false;
    string end_key = "";
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    while (!q.empty()) {
        State cur = q.front();
        q.pop();
        string cur_key = state_to_string(cur);
        if (is_goal(cur)) {
            found = true;
            end_key = cur_key;
            break;
        }
        int r0 = 0, c0 = cur.zero_top;
        for (int i = 0; i < 4; ++i) {
            int nr = r0 + dr[i];
            int nc = c0 + dc[i];
            if (nr >= 0 && nr < 2 && nc >= 0 && nc < N) {
                State next_state = cur;
                int val;
                if (nr == 0) {
                    val = next_state.top[nc];
                    next_state.top[nc] = 0;
                    next_state.top[c0] = val;
                    next_state.zero_top = nc;
                } else {
                    val = next_state.bottom[nc];
                    next_state.bottom[nc] = 0;
                    next_state.top[c0] = val;
                    next_state.zero_top = nc;
                    if (nr == 1) {
                        val = next_state.bottom[nc];
                        next_state.bottom[nc] = 0;
                        next_state.top[c0] = val;
                        next_state.zero_bottom = nc;
                        // 等等，範例輸入的 Top 是 "1 0 2"，Bottom 是 "2 1 0"。
                    }
                }
            }
        }
    }
}
void solve_clean() {
    cin >> N;
    vector<vector<int>> grid(2, vector<int>(N));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }
    vector<vector<int>> target(2, vector<int>(N));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < N; ++j) {
            target[i][j] = j;
        }
    }
    if (grid == target) {
        cout << 0 << endl;
        return;
    }
    queue<vector<vector<int>>> q;
    map<vector<vector<int>>, vector<vector<int>>> parent;
    map<vector<vector<int>>, vector<int>> move_record;
    q.push(grid);
    parent[grid] = {};
    move_record[grid] = {};
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    bool found = false;
    vector<vector<int>> final_state;
    while (!q.empty()) {
        vector<vector<int>> cur = q.front();
        q.pop();
        if (cur == target) {
            found = true;
            final_state = cur;
            break;
        }
        vector<pair<int,int>> zeros;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < N; ++j) {
                if (cur[i][j] == 0) {
                    zeros.push_back({i, j});
                }
            }
        }
        for (auto& z : zeros) {
            int zr = z.first, zc = z.second;
            for (int d = 0; d < 4; ++d) {
                int nr = zr + dr[d];
                int nc = zc + dc[d];
                if (nr >= 0 && nr < 2 && nc >= 0 && nc < N && cur[nr][nc] != 0) {
                    vector<vector<int>> next_grid = cur;
                    swap(next_grid[nr][nc], next_grid[zr][zc]);
                    if (parent.find(next_grid) == parent.end()) {
                        parent[next_grid] = cur;
                        move_record[next_grid] = {nr+1, nc+1, zr+1, zc+1};
                        q.push(next_grid);
                    }
                }
            }
        }
    }
    if (!found) {
        cout << -1 << endl;
        return;
    }
    vector<vector<int>> path_moves;
    vector<vector<int>> curr = final_state;
    while (!parent[curr].empty()) {
        path_moves.push_back(move_record[curr]);
        curr = parent[curr];
    }
    reverse(path_moves.begin(), path_moves.end());
    cout << path_moves.size() << endl;
    for (auto& m : path_moves) {
        cout << m[0] << " " << m[1] << " " << m[2] << " " << m[3] << endl;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve_clean();
    return 0;
}
