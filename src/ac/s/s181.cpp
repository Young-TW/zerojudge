#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

long long dp[70][6][512][3];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, r, k;
    long long t;
    while (cin >> n >> m >> r >> k >> t) {
        int N = m * r;
        vector<int> a(N + 1);
        for (int i = 1; i <= N; ++i) {
            cin >> a[i];
        }

        memset(dp, 0, sizeof(dp));

        int max_S = 1 << n;
        for (int cnt = 0; cnt <= k; ++cnt) {
            for (int S = 0; S < max_S; ++S) {
                for (int c = 0; c <= 2; ++c) {
                    if (cnt == k) {
                        dp[N + 1][cnt][S][c] = 1;
                    } else {
                        dp[N + 1][cnt][S][c] = 0;
                    }
                }
            }
        }

        for (int i = N; i >= 1; --i) {
            for (int cnt = 0; cnt <= k; ++cnt) {
                for (int S = 0; S < max_S; ++S) {
                    for (int c = 0; c <= 2; ++c) {
                        long long res = 0;
                        int next_i = i + 1;
                        bool same_class = (next_i <= N) && ((i - 1) / r == (next_i - 1) / r);
                        
                        // 不選 i
                        int next_c_not_choose = same_class ? c : 0;
                        res += dp[next_i][cnt][S][next_c_not_choose];
                        
                        // 選 i
                        if (cnt < k && !(S & (1 << (a[i] - 1))) && c < 2) {
                            int next_cnt = cnt + 1;
                            int next_S = S | (1 << (a[i] - 1));
                            int next_c_choose = same_class ? (c + 1) : 0;
                            res += dp[next_i][next_cnt][next_S][next_c_choose];
                        }
                        dp[i][cnt][S][c] = res;
                    }
                }
            }
        }

        long long current_t = t;
        int cnt = 0;
        int S = 0;
        int c = 0;
        vector<int> ans;
        for (int i = 1; i <= N; ++i) {
            int next_i = i + 1;
            bool same_class = (next_i <= N) && ((i - 1) / r == (next_i - 1) / r);
            
            long long choose_ways = 0;
            if (cnt < k && !(S & (1 << (a[i] - 1))) && c < 2) {
                int next_cnt = cnt + 1;
                int next_S = S | (1 << (a[i] - 1));
                int next_c_choose = same_class ? (c + 1) : 0;
                choose_ways = dp[next_i][next_cnt][next_S][next_c_choose];
            }
            
            if (current_t <= choose_ways) {
                ans.push_back(i);
                cnt++;
                S |= (1 << (a[i] - 1));
                c = same_class ? (c + 1) : 0;
            } else {
                current_t -= choose_ways;
                c = same_class ? c : 0;
            }
        }

        for (size_t i = 0; i < ans.size(); ++i) {
            if (i > 0) cout << " ";
            cout << ans[i];
        }
        cout << "\n";
    }

    return 0;
}
