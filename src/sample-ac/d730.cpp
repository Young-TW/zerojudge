#include <iostream>
#include <cstring>

using namespace std;

int mask_low[10];

void init_masks() {
    int masks[10][5] = {
        {0, 0, 0, 0, 0},
        {1, 2, 4, 5, -1},
        {1, 2, 3, -1, -1},
        {2, 3, 5, 6, -1},
        {1, 4, 7, -1, -1},
        {2, 4, 5, 6, 8},
        {3, 6, 9, -1, -1},
        {4, 5, 7, 8, -1},
        {7, 8, 9, -1, -1},
        {5, 6, 8, 9, -1}
    };
    for (int c = 1; c <= 9; ++c) {
        mask_low[c] = 0;
        for (int i = 0; i < 5; ++i) {
            int kid = masks[c][i];
            if (kid == -1) break;
            mask_low[c] |= (1 << (2 * (kid - 1)));
        }
    }
}

inline int add_one(int state, int cmd) {
    int m = mask_low[cmd];
    int carry = state & m;
    return (state ^ m) ^ (carry << 1);
}

inline int sub_one(int state, int cmd) {
    int m = mask_low[cmd];
    int borrow = (~state) & m;
    return (state ^ m) ^ (borrow << 1);
}

int dist[262144];
int q[262144];

void bfs() {
    memset(dist, -1, sizeof(dist));
    dist[0] = 0;
    int head = 0, tail = 0;
    q[tail++] = 0;
    while (head < tail) {
        int u = q[head++];
        for (int c = 1; c <= 9; ++c) {
            int v = sub_one(u, c);
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q[tail++] = v;
            }
        }
    }
}

void solve(int S) {
    bool first = true;
    while (S != 0) {
        for (int c = 1; c <= 9; ++c) {
            int nextS = add_one(S, c);
            if (dist[nextS] == dist[S] - 1) {
                if (!first) cout << " ";
                cout << c;
                first = false;
                S = nextS;
                break;
            }
        }
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init_masks();
    bfs();
    int T;
    if (cin >> T) {
        while (T--) {
            int S = 0;
            for (int i = 0; i < 9; ++i) {
                int dir;
                cin >> dir;
                S |= (dir << (2 * i));
            }
            solve(S);
        }
    }
    return 0;
}
