#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MOD = 2520;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int L;
    while (cin >> L) {
        int S, T, M;
        if (!(cin >> S >> T >> M)) break;
        
        vector<int> stones;
        for (int i = 0; i < M; ++i) {
            int p;
            cin >> p;
            if (p < L) {
                stones.push_back(p);
            }
        }
        sort(stones.begin(), stones.end());

        if (S == T) {
            int ans = 0;
            for (int pos : stones) {
                if (pos % S == 0) {
                    ans++;
                }
            }
            cout << ans << "\n";
        } else {
            vector<int> new_stones;
            int last = 0;
            int current_pos = 0;
            for (int pos : stones) {
                int dist = pos - last;
                if (dist > MOD) {
                    dist = MOD;
                }
                current_pos += dist;
                new_stones.push_back(current_pos);
                last = pos;
            }
            
            int dist_L = L - last;
            if (dist_L > MOD) {
                dist_L = MOD;
            }
            int new_L = current_pos + dist_L;

            vector<int> dp(new_L + T + 1, INF);
            vector<int> has_stone(new_L + T + 1, 0);
            
            for (int pos : new_stones) {
                if (pos < (int)has_stone.size()) {
                    has_stone[pos] = 1;
                }
            }

            dp[0] = 0;
            for (int i = 1; i <= new_L + T; ++i) {
                for (int j = S; j <= T; ++j) {
                    if (i - j >= 0) {
                        dp[i] = min(dp[i], dp[i - j] + has_stone[i]);
                    }
                }
            }

            int ans = INF;
            for (int i = new_L; i <= new_L + T; ++i) {
                ans = min(ans, dp[i]);
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
