#include <bits/stdc++.h>
using namespace std;

/* ---------- 64‑bit key for a coordinate pair ---------- */
static inline long long encode_coord(long long x, long long y) {
    return ((x & 0xffffffffLL) << 32) | (y & 0xffffffffLL);
}

/* ---------- state (x , y , dir) for cycle detection ---------- */
struct State {
    long long x, y;
    int dir;
    bool operator==(const State& other) const {
        return x == other.x && y == other.y && dir == other.dir;
    }
};

struct StateHash {
    size_t operator()(State const& s) const noexcept {
        size_t h1 = std::hash<long long>()(s.x);
        size_t h2 = std::hash<long long>()(s.y);
        size_t h3 = std::hash<int>()(s.dir);
        // combine
        size_t h = h1;
        h ^= h2 + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= h3 + 0x9e3779b9 + (h << 6) + (h >> 2);
        return h;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long m, T;
    while (cin >> n >> m >> T) {
        unordered_map<long long, char> mirror;          // key = encode_coord
        unordered_map<long long, vector<int>> row;      // y -> list of x
        unordered_map<long long, vector<int>> col;      // x -> list of y

        for (int i = 0; i < n; ++i) {
            long long x, y;
            char t;
            cin >> x >> y >> t;
            mirror[encode_coord(x, y)] = t;
            row[y].push_back((int)x);
            col[x].push_back((int)y);
        }

        for (auto &p : row) sort(p.second.begin(), p.second.end());
        for (auto &p : col) sort(p.second.begin(), p.second.end());

        long long steps = 0;
        long long x = 0, y = 0;
        int dir = 0;                     // 0:right 1:up 2:left 3:down

        unordered_map<State, long long, StateHash> visited;

        while (steps < T) {
            State cur{x, y, dir};
            auto it_vis = visited.find(cur);
            if (it_vis != visited.end()) {
                long long prev = it_vis->second;
                long long cycle_len = steps - prev;
                if (cycle_len > 0) {
                    long long remain = T - steps;
                    long long skip = remain / cycle_len;
                    if (skip > 0) {
                        steps += skip * cycle_len;
                        continue;
                    }
                }
            } else {
                visited.emplace(cur, steps);
            }

            long long nx = x, ny = y;
            long long d = LLONG_MAX;          // distance to next mirror

            if (dir == 0) {                    // right
                auto it = row.find(y);
                if (it != row.end()) {
                    const vector<int>& vec = it->second;
                    auto ub = upper_bound(vec.begin(), vec.end(), (int)x);
                    if (ub != vec.end()) {
                        nx = *ub;
                        ny = y;
                        d = nx - x;
                    }
                }
            } else if (dir == 2) {             // left
                auto it = row.find(y);
                if (it != row.end()) {
                    const vector<int>& vec = it->second;
                    auto lb = lower_bound(vec.begin(), vec.end(), (int)x);
                    if (lb != vec.begin()) {
                        --lb;
                        nx = *lb;
                        ny = y;
                        d = x - nx;
                    }
                }
            } else if (dir == 1) {             // up
                auto it = col.find(x);
                if (it != col.end()) {
                    const vector<int>& vec = it->second;
                    auto ub = upper_bound(vec.begin(), vec.end(), (int)y);
                    if (ub != vec.end()) {
                        nx = x;
                        ny = *ub;
                        d = ny - y;
                    }
                }
            } else {                           // down, dir == 3
                auto it = col.find(x);
                if (it != col.end()) {
                    const vector<int>& vec = it->second;
                    auto lb = lower_bound(vec.begin(), vec.end(), (int)y);
                    if (lb != vec.begin()) {
                        --lb;
                        nx = x;
                        ny = *lb;
                        d = y - ny;
                    }
                }
            }

            if (d == LLONG_MAX) {                 // no mirror ahead
                long long remain = T - steps;
                if (dir == 0) x += remain;
                else if (dir == 2) x -= remain;
                else if (dir == 1) y += remain;
                else y -= remain;
                steps = T;
                break;
            }

            if (steps + d > T) {                  // cannot reach the mirror
                long long remain = T - steps;
                if (dir == 0) x += remain;
                else if (dir == 2) x -= remain;
                else if (dir == 1) y += remain;
                else y -= remain;
                steps = T;
                break;
            }

            // move to the mirror
            x = nx; y = ny;
            steps += d;

            // reflect
            char type = mirror[encode_coord(x, y)];
            if (type == '/') {
                if (dir == 0) dir = 1;
                else if (dir == 1) dir = 0;
                else if (dir == 2) dir = 3;
                else dir = 2;          // dir == 3
            } else { // '\'
                if (dir == 0) dir = 3;
                else if (dir == 3) dir = 0;
                else if (dir == 2) dir = 1;
                else dir = 2;          // dir == 1
            }
        }

        cout << x << ' ' << y << '\n';
    }
    return 0;
}
