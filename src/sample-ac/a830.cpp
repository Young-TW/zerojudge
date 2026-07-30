#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long M, N, W, X, Y, Z;
    while (cin >> M >> N >> W >> X >> Y >> Z) {
        // birth[t] : newborn created exactly at minute t
        vector<long long> birth(W + 1, 0);
        birth[0] = N;                     // initial newborns

        for (long long t = 1; t <= W; ++t) {
            long long reproducing = 0;

            // initially mature bacteria
            if (t % Y == 0) reproducing += M;

            // bacteria born earlier
            for (long long i = 0; i < t; ++i) {
                if (birth[i] == 0) continue;
                long long firstRepro = i + X + Y;
                if (t >= firstRepro && (t - (i + X)) % Y == 0) {
                    reproducing += birth[i];
                }
            }

            birth[t] = reproducing * Z;
        }

        long long total = M + N;
        for (long long t = 1; t <= W; ++t) total += birth[t];
        cout << total << '\n';
    }
    return 0;
}
