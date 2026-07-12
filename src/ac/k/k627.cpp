#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve(int case_num) {
    int R, C;
    if (!(cin >> R >> C)) return;
    
    vector<vector<int>> grid(R, vector<int>(C));
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cin >> grid[i][j];
        }
    }

    vector<vector<int>> U(R, vector<int>(C, 0));
    vector<vector<int>> D(R, vector<int>(C, 0));
    vector<vector<int>> L(R, vector<int>(C, 0));
    vector<vector<int>> RR(R, vector<int>(C, 0));

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (grid[i][j]) {
                U[i][j] = (i == 0 ? 1 : U[i - 1][j] + 1);
                L[i][j] = (j == 0 ? 1 : L[i][j - 1] + 1);
            }
        }
    }

    for (int i = R - 1; i >= 0; --i) {
        for (int j = C - 1; j >= 0; --j) {
            if (grid[i][j]) {
                D[i][j] = (i == R - 1 ? 1 : D[i + 1][j] + 1);
                RR[i][j] = (j == C - 1 ? 1 : RR[i][j + 1] + 1);
            }
        }
    }

    long long ans = 0;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (grid[i][j]) {
                int A = U[i][j], B = RR[i][j];
                ans += max(0, min(B, A / 2) - 1);
                ans += max(0, min(A, B / 2) - 1);

                A = U[i][j], B = L[i][j];
                ans += max(0, min(B, A / 2) - 1);
                ans += max(0, min(A, B / 2) - 1);

                A = D[i][j], B = RR[i][j];
                ans += max(0, min(B, A / 2) - 1);
                ans += max(0, min(A, B / 2) - 1);

                A = D[i][j], B = L[i][j];
                ans += max(0, min(B, A / 2) - 1);
                ans += max(0, min(A, B / 2) - 1);
            }
        }
    }

    cout << "Case #" << case_num << ": " << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        for (int i = 1; i <= T; ++i) {
            solve(i);
        }
    }
    return 0;
}
