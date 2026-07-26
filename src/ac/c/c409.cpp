#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF64 = (1LL<<62);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while (cin >> N >> M) {
        vector<vector<ll>> a(N + 1, vector<ll>(M + 1, 0));
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= M; ++j)
                cin >> a[i][j];

        // best[i][j] = max dp[p][q] with p<=i , q<=j
        vector<vector<ll>> best(N + 1, vector<ll>(M + 1, 0));
        ll answer = 0;                     // empty selection is allowed

        // temporary arrays
        vector<ll> dpRow(M + 1, -INF64);   // dp for current bottom row
        vector<ll> colSum(M + 1, 0);       // vertical strip sums for current (top..bottom)

        for (int bottom = 1; bottom <= N; ++bottom) {
            fill(dpRow.begin(), dpRow.end(), -INF64);
            fill(colSum.begin(), colSum.end(), 0);

            // iterate over possible top rows, from bottom upwards
            for (int top = bottom; top >= 1; --top) {
                // add row 'top' to the column sums
                for (int c = 1; c <= M; ++c) colSum[c] += a[top][c];

                ll curBest = best[top - 1][0];   // l = 0, prefCol(0)=0
                ll prefCol = 0;                  // sum of colSum[1..c]

                for (int c = 1; c <= M; ++c) {
                    // candidate left border = c-1
                    ll cand = best[top - 1][c - 1] - prefCol;
                    if (cand > curBest) curBest = cand;

                    prefCol += colSum[c];
                    ll total = prefCol + curBest;          // rectangle ending at column c
                    if (total > dpRow[c]) dpRow[c] = total;
                }
            }

            // update best[][] with the newly obtained dpRow[]
            for (int c = 1; c <= M; ++c) {
                ll mx = dpRow[c];
                if (best[bottom - 1][c] > mx) mx = best[bottom - 1][c];
                if (best[bottom][c - 1] > mx) mx = best[bottom][c - 1];
                best[bottom][c] = mx;
                if (dpRow[c] > answer) answer = dpRow[c];
            }
        }

        if (answer < 0) answer = 0;   // choose nothing if all are negative
        cout << answer << '\n';
    }
    return 0;
}
