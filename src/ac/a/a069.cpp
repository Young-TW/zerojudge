#include <bits/stdc++.h>
using namespace std;

static long long pref[9][9];                     // prefix sums
static long long dp[9][9][9][9][15];
static bool vis[9][9][9][9][15];

inline long long rectSum(int r1, int r2, int c1, int c2) {
    return pref[r2][c2] - pref[r1][c2] - pref[r2][c1] + pref[r1][c1];
}

long long solve(int r1, int r2, int c1, int c2, int k) {
    if (vis[r1][r2][c1][c2][k]) return dp[r1][r2][c1][c2][k];
    vis[r1][r2][c1][c2][k] = true;
    long long total = rectSum(r1, r2, c1, c2);
    if (k == 1) return dp[r1][r2][c1][c2][k] = total * total;

    const long long INF = (1LL << 60);
    long long best = INF;

    // horizontal cuts
    for (int r = r1 + 1; r < r2; ++r) {
        long long top = rectSum(r1, r, c1, c2);
        long long cand = top * top + solve(r, r2, c1, c2, k - 1);
        if (cand < best) best = cand;

        long long bottom = rectSum(r, r2, c1, c2);
        cand = bottom * bottom + solve(r1, r, c1, c2, k - 1);
        if (cand < best) best = cand;
    }

    // vertical cuts
    for (int c = c1 + 1; c < c2; ++c) {
        long long left = rectSum(r1, r2, c1, c);
        long long cand = left * left + solve(r1, r2, c, c2, k - 1);
        if (cand < best) best = cand;

        long long right = rectSum(r1, r2, c, c2);
        cand = right * right + solve(r1, r2, c1, c, k - 1);
        if (cand < best) best = cand;
    }

    return dp[r1][r2][c1][c2][k] = best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        // read board and build prefix sum
        long long total = 0;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                int v; cin >> v;
                total += v;
                pref[i + 1][j + 1] = pref[i][j + 1] + pref[i + 1][j] - pref[i][j] + v;
            }
        }
        // clear memoisation tables
        memset(vis, 0, sizeof(vis));

        long long sumSq = solve(0, 8, 0, 8, n);
        double mean = static_cast<double>(total) / n;
        double sigma2 = static_cast<double>(sumSq) / n - mean * mean;
        if (sigma2 < 0) sigma2 = 0;               // numerical safety
        double sigma = sqrt(sigma2);
        cout << fixed << setprecision(3) << sigma << "\n";
    }
    return 0;
}
