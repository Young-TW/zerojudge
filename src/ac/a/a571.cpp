#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    while (cin >> N) {
        vector<pair<int,int>> ships(N);
        vector<int> coords;
        coords.reserve(2 * (size_t)N);
        for (int i = 0; i < N; i++) {
            int s, e;
            cin >> s >> e;
            ships[i] = make_pair(s, e);
            coords.push_back(s);
            coords.push_back(e);
        }
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
        int M = (int)coords.size();

        // For each start-index i, list of end-indices k (ship from coords[i] to coords[k]).
        vector<vector<int>> endsAt(M);
        for (size_t t = 0; t < ships.size(); t++) {
            int i = (int)(lower_bound(coords.begin(), coords.end(), ships[t].first)  - coords.begin());
            int k = (int)(lower_bound(coords.begin(), coords.end(), ships[t].second) - coords.begin());
            endsAt[i].push_back(k);
        }

        // dp[i][j] = max selectable ships with all endpoints within coords[i..j].
        // Laminar (non-crossing) + no shared endpoints, like RNA secondary structure.
        vector<vector<int>> dp(M, vector<int>(M, 0));
        for (int len = 2; len <= M; len++) {
            for (int i = 0; i + len - 1 < M; i++) {
                int j = i + len - 1;
                int best = dp[i + 1][j]; // don't start any ship at coords[i]
                for (size_t t = 0; t < endsAt[i].size(); t++) {
                    int k = endsAt[i][t];
                    if (k <= i || k > j) continue;
                    int inside = (i + 1 <= k - 1) ? dp[i + 1][k - 1] : 0; // strictly nested
                    int right  = (k + 1 <= j)     ? dp[k + 1][j]     : 0; // strictly to the right
                    int val = 1 + inside + right;
                    if (val > best) best = val;
                }
                dp[i][j] = best;
            }
        }

        int ans = (M >= 2) ? dp[0][M - 1] : 0;
        cout << ans << "\n";
    }
    return 0;
}
