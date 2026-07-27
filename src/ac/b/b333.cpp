#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;          // n ≤ 1000

int n, m;
vector< bitset<MAXN> > greaterMask;   // greaterMask[i][j] == 1  ⇔  i > j
int dp[MAXN];
bool vis[MAXN];

int dfs(int v) {
    if (vis[v]) return dp[v];
    vis[v] = true;
    int best = 1; // the vertex itself
    // iterate over all bits set in greaterMask[v]
    for (int u = greaterMask[v]._Find_first(); u < MAXN; u = greaterMask[v]._Find_next(u)) {
        best = max(best, 1 + dfs(u));
    }
    dp[v] = best;
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while ( (cin >> n >> m) ) {
        greaterMask.assign(n + 1, bitset<MAXN>());
        for (int trip = 0; trip < m; ++trip) {
            int s; cin >> s;
            vector<int> stops(s);
            for (int i = 0; i < s; ++i) cin >> stops[i];
            int L = stops.front();
            int R = stops.back();

            bitset<MAXN> intervalMask, stopMask;
            for (int i = L; i <= R; ++i) intervalMask.set(i);
            for (int x : stops) stopMask.set(x);
            bitset<MAXN> nonStopMask = intervalMask & (~stopMask);

            for (int x : stops) {
                greaterMask[x] |= nonStopMask;
            }
        }

        // DP for longest path
        fill(dp, dp + n + 1, 0);
        fill(vis, vis + n + 1, false);
        int answer = 0;
        for (int v = 1; v <= n; ++v) {
            answer = max(answer, dfs(v));
        }
        cout << answer << '\n';
    }
    return 0;
}
