#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N, K;
    while (cin >> M >> N >> K) {
        vector<vector<long long>> grid(M, vector<long long>(N));
        for (int i = 0; i < M; ++i)
            for (int j = 0; j < N; ++j)
                cin >> grid[i][j];

        // Prefix sums
        vector<vector<long long>> pref(M + 1, vector<long long>(N + 1, 0));
        for (int i = 1; i <= M; ++i)
            for (int j = 1; j <= N; ++j)
                pref[i][j] = grid[i-1][j-1] + pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1];

        auto get_sum = [&](int i, int j) -> long long {
            // Sum of K×K square with top-left at (i, j)
            return pref[i+K][j+K] - pref[i][j+K] - pref[i+K][j] + pref[i][j];
        };

        int R = M - K + 1; // number of valid top rows
        int C = N - K + 1; // number of valid left cols

        // R_top[i] = max s[i'][j'] for i' <= i
        // R_bot[i] = max s[i'][j'] for i' >= i
        // C_left[j] = max s[i'][j'] for j' <= j
        // C_right[j] = max s[i'][j'] for j' >= j
        vector<long long> R_top(R, 0), R_bot(R, 0);
        vector<long long> C_left(C, 0), C_right(C, 0);
        vector<long long> row_max(R, 0), col_max(C, 0);

        // Compute row_max and col_max
        for (int i = 0; i < R; ++i) {
            row_max[i] = 0;
            for (int j = 0; j < C; ++j) {
                long long v = get_sum(i, j);
                row_max[i] = max(row_max[i], v);
                col_max[j] = max(col_max[j], v);
            }
        }

        // R_top
        for (int i = 0; i < R; ++i) {
            R_top[i] = row_max[i];
            if (i > 0) R_top[i] = max(R_top[i], R_top[i-1]);
        }
        // R_bot
        for (int i = R - 1; i >= 0; --i) {
            R_bot[i] = row_max[i];
            if (i < R - 1) R_bot[i] = max(R_bot[i], R_bot[i+1]);
        }
        // C_left
        for (int j = 0; j < C; ++j) {
            C_left[j] = col_max[j];
            if (j > 0) C_left[j] = max(C_left[j], C_left[j-1]);
        }
        // C_right
        for (int j = C - 1; j >= 0; --j) {
            C_right[j] = col_max[j];
            if (j < C - 1) C_right[j] = max(C_right[j], C_right[j+1]);
        }

        long long ans = 0;

        // Config 1: three horizontal bands
        // i2 in [K, M-2K], middle square at row i2
        for (int i2 = K; i2 <= M - 2 * K; ++i2) {
            long long val = R_top[i2 - K] + row_max[i2] + R_bot[i2 + K];
            ans = max(ans, val);
        }

        // Config 2: three vertical bands
        for (int j2 = K; j2 <= N - 2 * K; ++j2) {
            long long val = C_left[j2 - K] + col_max[j2] + C_right[j2 + K];
            ans = max(ans, val);
        }

        // Helper: given m[] array of size C, compute prefix_max and suffix_max,
        // then find max over c in [K-1, C-1-K+1] of (prefix_max[c-K+1] + suffix_max[c+1])
        // Wait, let me re-derive. c ranges over valid column splits.
        // c-K+1 >= 0 => c >= K-1
        // c+1 <= C-1 => c <= C-2
        // Also need c-K+1 <= C-1 and c+1 >= 0, which are satisfied.
        // So c in [K-1, C-2].
        // prefix_max[c-K+1] = max m[0..c-K+1]
        // suffix_max[c+1] = max m[c+1..C-1]
        
        auto split_max_cols = [&](vector<long long>& m) -> long long {
            int n = m.size(); // = C
            if (n < 2 * K) return 0; // can't split into two non-overlapping column bands
            vector<long long> pm(n), sm(n);
            pm[0] = m[0];
            for (int j = 1; j < n; ++j) pm[j] = max(pm[j-1], m[j]);
            sm[n-1] = m[n-1];
            for (int j = n-2; j >= 0; --j) sm[j] = max(sm[j+1], m[j]);
            long long best = 0;
            for (int c = K - 1; c <= n - 2; ++c) {
                // left col of left square <= c-K+1, left col of right square >= c+1
                // Need c-K+1 >= 0 (c >= K-1) and c+1 <= n-1 (c <= n-2)
                // Also need c-K+1 <= n-1 (always true) and c+1 >= 0 (always true)
                // But also need the left square to fit: c-K+1 >= 0, and right square: c+1 <= n-1
                // And non-overlap: left square right col = (c-K+1)+K-1 = c, right square left col = c+1. OK.
                best = max(best, pm[c-K+1] + sm[c+1]);
            }
            return best;
        };

        // Similarly for rows
        auto split_max_rows = [&](vector<long long>& m) -> long long {
            int n = m.size(); // = R
            if (n < 2 * K) return 0;
            vector<long long> pm(n), sm(n);
            pm[0] = m[0];
            for (int j = 1; j < n; ++j) pm[j] = max(pm[j-1], m[j]);
            sm[n-1] = m[n-1];
            for (int j = n-2; j >= 0; --j) sm[j] = max(sm[j+1], m[j]);
            long long best = 0;
            for (int r = K - 1; r <= n - 2; ++r) {
                best = max(best, pm[r-K+1] + sm[r+1]);
            }
            return best;
        };

        // Config 3: top, bottom-left, bottom-right
        // r in [K-1, M-K-1], top = R_top[r-K+1]
        // bottom: m[j] = max s[i][j] for i >= r+1
        {
            vector<long long> m(C, 0);
            for (int r = M - K - 1; r >= K - 1; --r) {
                // Add row r+1 to bottom region
                for (int j = 0; j < C; ++j)
                    m[j] = max(m[j], get_sum(r + 1, j));
                long long top = R_top[r - K + 1];
                long long bot = split_max_cols(m);
                ans = max(ans, top + bot);
            }
        }

        // Config 4: bottom, top-left, top-right
        // r in [K, M-K], bottom = R_bot[r]
        // top: m[j] = max s[i][j] for i <= r-K
        {
            vector<long long> m(C, 0);
            for (int r = K; r <= M - K; ++r) {
                // Add row r-K to top region
                for (int j = 0; j < C; ++j)
                    m[j] = max(m[j], get_sum(r - K, j));
                long long bottom = R_bot[r];
                long long top = split_max_cols(m);
                ans = max(ans, top + bottom);
            }
        }

        // Config 5: left, top-right, bottom-right
        // c in [K-1, N-K-1], left = C_left[c-K+1]
        // right: m[i] = max s[i][j] for j >= c+1
        {
            vector<long long> m(R, 0);
            for (int c = N - K - 1; c >= K - 1; --c) {
                // Add col c+1 to right region
                for (int i = 0; i < R; ++i)
                    m[i] = max(m[i], get_sum(i, c + 1));
                long long left = C_left[c - K + 1];
                long long right = split_max_rows(m);
                ans = max(ans, left + right);
            }
        }

        // Config 6: right, top-left, bottom-left
        // c in [K, N-K], right = C_right[c]
        // left: m[i] = max s[i][j] for j <= c-K
        {
            vector<long long> m(R, 0);
            for (int c = K; c <= N - K; ++c) {
                // Add col c-K to left region
                for (int i = 0; i < R; ++i)
                    m[i] = max(m[i], get_sum(i, c - K));
                long long right = C_right[c];
                long long left = split_max_rows(m);
                ans = max(ans, left + right);
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
