#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using int64 = long long;

int64 total_pairs_all(int64 n, int64 m) {
    if (n <= m) {
        return (n + 1) * (n + 2) / 2;
    } else {
        return (m + 1) * (m + 2) / 2 + (n - m) * (m + 1);
    }
}

int64 count_good(int64 n, int64 m, int64 k) {
    vector<int> nd, md;
    int64 tn = n, tm = m;
    if (tn == 0) nd.push_back(0);
    else while (tn > 0) { nd.push_back(tn % k); tn /= k; }
    if (tm == 0) md.push_back(0);
    else while (tm > 0) { md.push_back(tm % k); tm /= k; }
    reverse(nd.begin(), nd.end());
    reverse(md.begin(), md.end());
    int L = max(nd.size(), md.size());
    nd.insert(nd.begin(), L - nd.size(), 0);
    md.insert(md.begin(), L - md.size(), 0);

    int64 dp[2][2] = {{0, 0}, {0, 0}};
    dp[1][1] = 1;

    auto total_pairs_ab = [](int64 a, int64 b) -> int64 {
        if (a < 0 || b < 0) return 0;
        if (b >= a) {
            return (a + 1) * (a + 2) / 2;
        } else {
            return (b + 1) * (b + 2) / 2 + (a - b) * (b + 1);
        }
    };

    for (int pos = 0; pos < L; ++pos) {
        int64 new_dp[2][2] = {{0, 0}, {0, 0}};
        for (int ti = 0; ti < 2; ++ti) {
            for (int tj = 0; tj < 2; ++tj) {
                int64 cur = dp[ti][tj];
                if (cur == 0) continue;
                int64 A = ti ? nd[pos] : k - 1;
                int64 B = tj ? md[pos] : k - 1;

                int64 c11 = (B <= A) ? 1 : 0;
                int64 c10 = (B > 0) ? (min(A, B - 1) + 1) : 0;
                int64 c01 = (B < A) ? (A - B) : 0;
                int64 c00 = total_pairs_ab(A - 1, B - 1);

                new_dp[0][0] += cur * c00;
                new_dp[0][tj] += cur * c01;
                new_dp[ti][0] += cur * c10;
                new_dp[ti][tj] += cur * c11;
            }
        }
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                dp[i][j] = new_dp[i][j];
    }

    int64 total = 0;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            total += dp[i][j];
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 t, k;
    bool first_group = true;
    while (cin >> t >> k) {
        if (!first_group) {
            cout << '\n';
        }
        first_group = false;
        for (int64 i = 0; i < t; ++i) {
            int64 n, m;
            cin >> n >> m;
            int64 total = total_pairs_all(n, m);
            int64 good = count_good(n, m, k);
            int64 ans = total - good;
            cout << ans << '\n';
        }
    }
    return 0;
}
