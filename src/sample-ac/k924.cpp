#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int add_table[11][2048];
int sub_table[11][2048];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int d = 0; d < 11; ++d) {
        for (int mask = 0; mask < 2048; ++mask) {
            int res_add = 0, res_sub = 0;
            for (int i = 0; i < 11; ++i) {
                if (mask & (1 << i)) {
                    res_add |= 1 << ((i + d) % 11);
                    res_sub |= 1 << ((i - d + 11) % 11);
                }
            }
            add_table[d][mask] = res_add;
            sub_table[d][mask] = res_sub;
        }
    }

    string A, B;
    while (cin >> A >> B) {
        int N = (int)A.length();
        int M = (int)B.length();
        
        if (M > N) {
            swap(A, B);
            swap(N, M);
        }
        
        vector<int> dp(M + 1, 0);
        dp[0] = 1;

        for (int i = 0; i <= N; ++i) {
            vector<int> next_dp(M + 1, 0);
            for (int j = 0; j <= M; ++j) {
                if (i == 0 && j == 0) {
                    next_dp[0] = 1;
                    continue;
                }
                int L = i + j;
                int new_dp = 0;
                if (i > 0) {
                    int d = A[i-1] - '0';
                    if (L % 2 == 1) {
                        new_dp |= add_table[d][dp[j]];
                    } else {
                        new_dp |= sub_table[d][dp[j]];
                    }
                }
                if (j > 0) {
                    int d = B[j-1] - '0';
                    if (L % 2 == 1) {
                        new_dp |= add_table[d][next_dp[j-1]];
                    } else {
                        new_dp |= sub_table[d][next_dp[j-1]];
                    }
                }
                next_dp[j] = new_dp;
            }
            dp = next_dp;
        }

        if (dp[M] & 1) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}
