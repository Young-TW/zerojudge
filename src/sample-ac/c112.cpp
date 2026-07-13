#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

int p[15];
long long dp[15][15];
int split[15][15];

string build(int i, int j) {
    if (i == j) {
        return "A" + to_string(i);
    }
    int k = split[i][j];
    return "(" + build(i, k) + " x " + build(k + 1, j) + ")";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    int caseNum = 1;
    while (cin >> N && N) {
        for (int i = 1; i <= N; ++i) {
            int r, c;
            cin >> r >> c;
            p[i] = r;
            p[i + 1] = c;
        }
        
        for (int i = 1; i <= N; ++i) {
            dp[i][i] = 0;
        }
        
        for (int len = 2; len <= N; ++len) {
            for (int i = 1; i <= N - len + 1; ++i) {
                int j = i + len - 1;
                dp[i][j] = -1;
                for (int k = i; k < j; ++k) {
                    long long cost = dp[i][k] + dp[k + 1][j] + (long long)p[i] * p[k + 1] * p[j + 1];
                    if (dp[i][j] == -1 || cost < dp[i][j]) {
                        dp[i][j] = cost;
                        split[i][j] = k;
                    }
                }
            }
        }
        
        cout << "Case " << caseNum++ << ": " << build(1, N) << "\n";
    }
    
    return 0;
}
