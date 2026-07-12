#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    while (n--) {
        int p, k;
        cin >> p >> k;
        string str;
        for (int i = 0; i < p; ++i) {
            string line;
            cin >> line;
            str += line;
        }
        int s;
        cin >> s;
        vector<string> dict(s);
        for (int i = 0; i < s; ++i) {
            cin >> dict[i];
        }

        int N = str.length();
        vector<int> min_len(N, 1e9);
        for (int i = 0; i < N; ++i) {
            for (const string& w : dict) {
                int len = w.length();
                if (i + len <= N && str.substr(i, len) == w) {
                    min_len[i] = min(min_len[i], len);
                }
            }
        }

        vector<vector<int>> cnt(N, vector<int>(N, 0));
        for (int L = N - 1; L >= 0; --L) {
            for (int R = L; R < N; ++R) {
                if (L == R) {
                    cnt[L][R] = (min_len[L] == 1) ? 1 : 0;
                } else {
                    cnt[L][R] = cnt[L + 1][R];
                    if (min_len[L] != 1e9 && L + min_len[L] - 1 <= R) {
                        cnt[L][R]++;
                    }
                }
            }
        }

        vector<vector<int>> dp(N + 1, vector<int>(k + 1, -1e9));
        dp[0][0] = 0;
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= min(i, k); ++j) {
                for (int t = j - 1; t < i; ++t) {
                    if (dp[t][j - 1] != -1e9) {
                        dp[i][j] = max(dp[i][j], dp[t][j - 1] + cnt[t][i - 1]);
                    }
                }
            }
        }

        if (k > N) {
            cout << 0 << "\n";
        } else {
            cout << dp[N][k] << "\n";
        }
    }

    return 0;
}
