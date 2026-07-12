#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<vector<int>> L(N + 1, vector<int>(M + 1, 0));
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                cin >> L[i][j];
            }
        }
        
        vector<vector<int>> dp(N + 1, vector<int>(M + 1, -1));
        dp[0][0] = 0;
        
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                if (L[i][j] < 5) continue;
                for (int k = j; k <= M; ++k) {
                    if (dp[i - 1][k - j] != -1) {
                        dp[i][k] = max(dp[i][k], dp[i - 1][k - j] + L[i][j]);
                    }
                }
            }
        }
        
        int max_sum = -1;
        for (int j = N; j <= M; ++j) {
            if (dp[N][j] > max_sum) {
                max_sum = dp[N][j];
            }
        }
        
        if (max_sum == -1) {
            cout << "Peter, you shouldn't have played billiard that much.\n";
        } else {
            int int_part = max_sum / N;
            int rem = max_sum % N;
            int frac = rem * 100 / N;
            int next_digit = (rem * 1000 / N) % 10;
            if (next_digit >= 5) {
                frac++;
                if (frac == 100) {
                    frac = 0;
                    int_part++;
                }
            }
            cout << "Maximal possible average mark - " << int_part << "." << setw(2) << setfill('0') << frac << ".\n";
        }
    }
    
    return 0;
}
