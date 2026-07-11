#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

struct State {
    vector<int> dirs;
    vector<int> commands;
    int steps;

    State(vector<int> d, vector<int> c, int s) : dirs(d), commands(c), steps(s) {}

    bool operator==(const State& other) const {
        return dirs == other.dirs;
    }
};

namespace std {
    template <>
    struct hash<State> {
        size_t operator()(const State& s) const {
            size_t h = 0;
            for (int d : s.dirs) {
                h = h * 31 + d;
            }
            return h;
        }
    };
}

vector<vector<int>> command_masks = {
    {0, 1, 3, 4},    // 1
    {0, 1, 2},       // 2
    {1, 2, 4, 5},    // 3
    {0, 3, 6},       // 4
    {1, 3, 4, 5, 7}, // 5
    {2, 5, 8},       // 6
    {3, 4, 6, 7},    // 7
    {6, 7, 8},       // 8
    {4, 5, 7, 8}     // 9
};

vector<int> apply_command(const vector<int>& dirs, int cmd) {
    vector<int> new_dirs = dirs;
    for (int pos : command_masks[cmd-1]) {
        new_dirs[pos] = (new_dirs[pos] + 1) % 4;
    }
    return new_dirs;
}

vector<int> bfs(const vector<int>& initial) {
    unordered_map<State, bool> visited;
    queue<State> q;
    vector<int> target(9, 0);
    State initial_state(initial, {}, 0);

    if (initial == target) {
        return {};
    }

    q.push(initial_state);
    visited[initial_state] = true;

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        for (int cmd = 1; cmd <= 9; ++cmd) {
            vector<int> new_dirs = apply_command(current.dirs, cmd);
            vector<int> new_commands = current.commands;
            new_commands.push_back(cmd);

            State new_state(new_dirs, new_commands, current.steps + 1);

            if (new_dirs == target) {
                return new_commands;
            }

            if (!visited[new_state]) {
                visited[new_state] = true;
                q.push(new_state);
            }
        }
    }

    return {};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        vector<int> dirs(9);
        for (int i = 0; i < 9; ++i) {
            cin >> dirs[i];
        }

        vector<int> commands = bfs(dirs);

        for (size_t i = 0; i < commands.size(); ++i) {
            if (i != 0) {
                cout << " ";
            }
            cout << commands[i];
        }
        cout << "\n";
    }

    return 0;
}
