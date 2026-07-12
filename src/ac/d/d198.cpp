#include <iostream>
#include <string>
#include <sstream>

using namespace std;

long long dp[105][105];
bool blocked[105][105];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;
    cin.ignore();

    bool first_case = true;
    string line;

    while (T--) {
        int W, N;
        bool found = false;
        while (getline(cin, line)) {
            stringstream ss(line);
            if (ss >> W >> N) {
                found = true;
                break;
            }
        }
        if (!found) break;

        for (int i = 0; i <= W; ++i) {
            for (int j = 0; j <= N; ++j) {
                dp[i][j] = 0;
                blocked[i][j] = false;
            }
        }

        for (int i = 0; i < W; ++i) {
            while (getline(cin, line)) {
                stringstream ss(line);
                int r;
                if (ss >> r) {
                    int c;
                    while (ss >> c) {
                        if (r >= 1 && r <= W && c >= 1 && c <= N) {
                            blocked[r][c] = true;
                        }
                    }
                    break;
                }
            }
        }

        dp[1][1] = 1;
        if (blocked[1][1]) dp[1][1] = 0;

        for (int i = 1; i <= W; ++i) {
            for (int j = 1; j <= N; ++j) {
                if (i == 1 && j == 1) continue;
                if (blocked[i][j]) {
                    dp[i][j] = 0;
                } else {
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
                }
            }
        }

        if (!first_case) {
            cout << "\n";
        }
        first_case = false;
        cout << dp[W][N] << "\n";
    }

    return 0;
}
