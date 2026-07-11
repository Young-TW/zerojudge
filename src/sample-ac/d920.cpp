#include <iostream>
#include <queue>
#include <unordered_map>
#include <cstdint>

using namespace std;

struct State {
    uint64_t board;
    int zero_pos;
    int dist;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    uint64_t target_state = 0;
    for (int i = 0; i < 15; ++i) {
        target_state |= (uint64_t)(i + 1) << (i * 4);
    }

    unordered_map<uint64_t, int> dist;
    dist.reserve(1 << 18);
    queue<State> q;
    
    dist[target_state] = 0;
    q.push({target_state, 15, 0});

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.dist == 10) continue;

        int r = cur.zero_pos / 4;
        int c = cur.zero_pos % 4;

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < 4 && nc >= 0 && nc < 4) {
                int next_pos = nr * 4 + nc;
                uint64_t next_state = cur.board;
                int val = (cur.board >> (next_pos * 4)) & 0xF;
                
                next_state &= ~((uint64_t)0xF << (cur.zero_pos * 4));
                next_state |= (uint64_t)val << (cur.zero_pos * 4);
                next_state &= ~((uint64_t)0xF << (next_pos * 4));

                if (dist.find(next_state) == dist.end()) {
                    dist[next_state] = cur.dist + 1;
                    q.push({next_state, next_pos, cur.dist + 1});
                }
            }
        }
    }

    int x;
    while (cin >> x) {
        uint64_t state = (uint64_t)x;
        for (int i = 1; i < 16; ++i) {
            cin >> x;
            state |= (uint64_t)x << (i * 4);
        }

        auto it = dist.find(state);
        if (it != dist.end()) {
            cout << it->second << "\n";
        } else {
            cout << "TOO LONG\n";
        }
    }

    return 0;
}
