#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1005;
int cards[MAXN];
int dp[MAXN][MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        for (int i = 0; i < N; ++i) {
            cin >> cards[i];
        }
        
        for (int i = 0; i < N; ++i) {
            dp[i][i] = 0;
            if (i + 1 < N) {
                dp[i][i + 1] = 0;
            }
        }
        
        for (int len = 2; len < N; ++len) {
            for (int i = 0; i + len < N; ++i) {
                int j = i + len;
                int max_val = 0;
                for (int k = i + 1; k < j; ++k) {
                    int val = dp[i][k] + dp[k][j];
                    if (val > max_val) {
                        max_val = val;
                    }
                }
                dp[i][j] = max_val + cards[i] * cards[j];
            }
        }
        
        cout << dp[0][N - 1] << "\n";
    }
    
    return 0;
}
