#include <iostream>

using namespace std;

int n;
long long score[35];
long long dp[35][35];
int root[35][35];

void print_pre(int i, int j, bool& first) {
    if (i > j) return;
    if (!first) cout << " ";
    cout << root[i][j];
    first = false;
    print_pre(i, root[i][j] - 1, first);
    print_pre(root[i][j] + 1, j, first);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) {
            cin >> score[i];
        }
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dp[i][j] = 0;
            }
            dp[i][i] = score[i];
            root[i][i] = i;
        }
        
        for (int len = 2; len <= n; ++len) {
            for (int i = 1; i <= n - len + 1; ++i) {
                int j = i + len - 1;
                dp[i][j] = 0;
                for (int k = i; k <= j; ++k) {
                    long long left = (k == i) ? 1 : dp[i][k-1];
                    long long right = (k == j) ? 1 : dp[k+1][j];
                    long long val = left * right + score[k];
                    if (val > dp[i][j]) {
                        dp[i][j] = val;
                        root[i][j] = k;
                    }
                }
            }
        }
        
        cout << dp[1][n] << "\n";
        bool first = true;
        print_pre(1, n, first);
        cout << "\n";
    }
    
    return 0;
}
