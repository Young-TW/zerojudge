#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MOD = 20123;
    int N, M;
    while (cin >> N >> M) {
        // sign[i][j]
        vector< vector<int> > sign(N, vector<int>(M));
        // prefix sums of stairs, pref[i][t] = #stairs in rooms [0, t-1]
        vector< vector<int> > pref(N, vector<int>(M + 1, 0));

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                int has, s;
                cin >> has >> s;
                sign[i][j] = s;
                pref[i][j + 1] = pref[i][j] + has;
            }
        }

        int cur;
        cin >> cur;

        long long answer = 0;

        for (int i = 0; i < N; ++i) {
            int x = sign[i][cur];
            answer += x;
            if (answer >= MOD) answer %= MOD;

            int total = pref[i][M];               // number of stairs on this floor
            // problem guarantees at least one stair; guard against zero just in case
            if (total == 0) break;

            int k = (int)(((int64_t)x - 1) % total) + 1;   // 1‑based

            int cntFromR = pref[i][M] - pref[i][cur];      // stairs in [cur , M-1]

            if (cntFromR >= k) {
                int need = pref[i][cur] + k;
                // lower_bound on pref[i][cur+1 .. M]
                int lo = cur + 1, hi = M;
                while (lo < hi) {
                    int mid = (lo + hi) >> 1;
                    if (pref[i][mid] >= need) hi = mid;
                    else lo = mid + 1;
                }
                cur = lo - 1;
            } else {
                int k2 = k - cntFromR;
                // lower_bound on pref[i][1 .. cur]
                int lo = 1, hi = cur;
                while (lo < hi) {
                    int mid = (lo + hi) >> 1;
                    if (pref[i][mid] >= k2) hi = mid;
                    else lo = mid + 1;
                }
                cur = lo - 1;
            }
        }

        cout << (answer % MOD) << '\n';
    }
    return 0;
}
