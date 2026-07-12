#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <functional>

using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x[26], y[26];
    string row1 = "QWERTYUIOP";
    string row2 = "ASDFGHJKL";
    string row3 = "ZXCVBNM";

    for (int i = 0; i < row1.size(); ++i) {
        x[row1[i] - 'A'] = i;
        y[row1[i] - 'A'] = 0;
    }
    for (int i = 0; i < row2.size(); ++i) {
        x[row2[i] - 'A'] = i;
        y[row2[i] - 'A'] = 1;
    }
    for (int i = 0; i < row3.size(); ++i) {
        x[row3[i] - 'A'] = i;
        y[row3[i] - 'A'] = 2;
    }

    int dist[26][26];
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            dist[i][j] = (i == j) ? 0 : INF;
        }
    }

    int dx[] = {-1, 1, 0, 1, -1, 0};
    int dy[] = {0, 0, -1, -1, 1, 1};

    for (int i = 0; i < 26; ++i) {
        for (int d = 0; d < 6; ++d) {
            int nx = x[i] + dx[d];
            int ny = y[i] + dy[d];
            for (int j = 0; j < 26; ++j) {
                if (x[j] == nx && y[j] == ny) {
                    dist[i][j] = 1;
                    break;
                }
            }
        }
    }

    for (int k = 0; k < 26; ++k) {
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    int n;
    while (cin >> n) {
        string s;
        cin >> s;
        vector<vector<int>> dp(2, vector<int>(26, INF));
        
        int F = 'F' - 'A';
        int J = 'J' - 'A';
        int first = s[0] - 'A';
        
        dp[0][J] = dist[F][first];
        dp[0][F] = dist[J][first];
        
        for (int i = 1; i < n; ++i) {
            int cur = i % 2;
            int prev = 1 - cur;
            fill(dp[cur].begin(), dp[cur].end(), INF);
            
            int u = s[i - 1] - 'A';
            int v = s[i] - 'A';
            
            for (int j = 0; j < 26; ++j) {
                if (dp[prev][j] != INF) {
                    if (dp[prev][j] + dist[u][v] < dp[cur][j]) {
                        dp[cur][j] = dp[prev][j] + dist[u][v];
                    }
                    if (dp[prev][j] + dist[j][v] < dp[cur][u]) {
                        dp[cur][u] = dp[prev][j] + dist[j][v];
                    }
                }
            }
        }
        
        int ans = INF;
        int last = (n - 1) % 2;
        for (int j = 0; j < 26; ++j) {
            if (dp[last][j] < ans) {
                ans = dp[last][j];
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
