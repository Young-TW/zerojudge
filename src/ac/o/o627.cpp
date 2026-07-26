#include <bits/stdc++.h>
using namespace std;

int N, M;
int adjMask[16];                 // neighbours of each vertex as bitmask
int orderVec[16];                // vertices processed in this order
int bestDiff;                    // current best answer (INF = N+1)

void dfs(int pos, int colMask[3]) {
    if (pos == N) {
        int sz[3];
        sz[0] = __builtin_popcount(colMask[0]);
        sz[1] = __builtin_popcount(colMask[1]);
        sz[2] = __builtin_popcount(colMask[2]);
        int mx = max(sz[0], max(sz[1], sz[2]));
        int mn = min(sz[0], min(sz[1], sz[2]));
        bestDiff = min(bestDiff, mx - mn);
        return;
    }
    int v = orderVec[pos];
    for (int c = 0; c < 3; ++c) {
        if ((adjMask[v] & colMask[c]) == 0) {          // can put v into colour c
            colMask[c] |= (1 << v);
            dfs(pos + 1, colMask);
            colMask[c] ^= (1 << v);                    // backtrack
            if (bestDiff == 0) return;                 // optimal already found
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> N >> M) {
        // initialise
        for (int i = 0; i < N; ++i) adjMask[i] = 0;
        for (int i = 0; i < M; ++i) {
            int x, y;
            cin >> x >> y;
            --x; --y;
            adjMask[x] |= (1 << y);
            adjMask[y] |= (1 << x);
        }
        // order vertices by decreasing degree (helps pruning)
        vector<pair<int,int>> deg;
        for (int i = 0; i < N; ++i) deg.push_back({__builtin_popcount(adjMask[i]), i});
        sort(deg.rbegin(), deg.rend());
        for (int i = 0; i < N; ++i) orderVec[i] = deg[i].second;

        bestDiff = N + 1;          // INF
        int colMask[3] = {0, 0, 0};
        dfs(0, colMask);

        if (bestDiff == N + 1) cout << -1 << '\n';
        else                     cout << bestDiff << '\n';
    }
    return 0;
}
