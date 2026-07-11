#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <tuple>
#include <cctype>

using namespace std;

int dir_to_int(const string& s) {
    if (s == "N") return 0;
    if (s == "NE") return 1;
    if (s == "E") return 2;
    if (s == "SE") return 3;
    if (s == "S") return 4;
    if (s == "SW") return 5;
    if (s == "W") return 6;
    if (s == "NW") return 7;
    return -1;
}

string int_to_dir(int d) {
    static const vector<string> dirs = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};
    return dirs[d];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int R, C;
    if (!(cin >> R >> C)) return 0;

    vector<string> grid(R);
    for (int i = 0; i < R; ++i) {
        cin >> grid[i];
    }

    // Directions: 0=N, 1=NE, 2=E, 3=SE, 4=S, 5=SW, 6=W, 7=NW
    const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    const int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

    set<tuple<int, int, int>> fall_set; // (x, y, dir)
    bool teleported = false;

    int x, y;
    string dir_str, plan_str;

    while (cin >> x >> y >> dir_str) {
        cin >> plan_str;

        if (teleported) {
            cout << "I think I don't need to move anymore." << '\n';
            continue;
        }

        // Parse plan string into commands
        vector<pair<char, int>> cmds;
        for (size_t i = 0; i < plan_str.size(); ) {
            char c = plan_str[i];
            if (c == 'M') {
                cmds.emplace_back('M', 0);
                ++i;
            } else if (c == 'R' || c == 'L') {
                ++i;
                int deg = 0;
                while (i < plan_str.size() && isdigit(plan_str[i])) {
                    deg = deg * 10 + (plan_str[i] - '0');
                    ++i;
                }
                cmds.emplace_back(c, deg);
            } else {
                // Should not happen, skip
                ++i;
            }
        }

        int dir = dir_to_int(dir_str);
        bool plan_ended = false;

        for (const auto& cmd : cmds) {
            if (cmd.first == 'R') {
                int steps = cmd.second / 45;
                dir = (dir + steps) % 8;
            } else if (cmd.first == 'L') {
                int steps = cmd.second / 45;
                dir = (dir - steps + 8) % 8;
            } else { // 'M'
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                bool is_fall = false;
                if (nx < 1 || nx > C || ny < 1 || ny > R) {
                    is_fall = true;
                } else if (grid[ny - 1][nx - 1] == 'H') {
                    is_fall = true;
                }

                if (is_fall) {
                    tuple<int, int, int> state = {x, y, dir};
                    if (fall_set.count(state)) {
                        // Skip this move
                        continue;
                    } else {
                        fall_set.insert(state);
                        cout << x << ' ' << y << ' ' << int_to_dir(dir) << " BAD PLAN!" << '\n';
                        plan_ended = true;
                        break;
                    }
                } else {
                    char cell = grid[ny - 1][nx - 1];
                    if (cell == 'T') {
                        x = nx;
                        y = ny;
                        cout << x << ' ' << y << " FINISHED!" << '\n';
                        teleported = true;
                        plan_ended = true;
                        break;
                    } else {
                        // Ground (G) or any other non-special cell
                        x = nx;
                        y = ny;
                    }
                }
            }
        }

        if (!plan_ended && !teleported) {
            cout << x << ' ' << y << ' ' << int_to_dir(dir) << '\n';
        }
    }

    return 0;
}
