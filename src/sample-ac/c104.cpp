#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

int solutions[92][8];
int sol_count = 0;

int col[8];
bool used_col[8], diag1[15], diag2[15];

void solve(int row) {
    if (row == 8) {
        for (int i = 0; i < 8; i++) {
            solutions[sol_count][i] = col[i];
        }
        sol_count++;
        return;
    }
    for (int c = 0; c < 8; c++) {
        if (!used_col[c] && !diag1[row - c + 7] && !diag2[row + c]) {
            col[row] = c;
            used_col[c] = true;
            diag1[row - c + 7] = true;
            diag2[row + c] = true;
            solve(row + 1);
            used_col[c] = false;
            diag1[row - c + 7] = false;
            diag2[row + c] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve(0);
    
    int k;
    while (cin >> k) {
        while (k--) {
            int board[8][8];
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    cin >> board[i][j];
                }
            }
            int max_sum = 0;
            for (int s = 0; s < sol_count; s++) {
                int sum = 0;
                for (int i = 0; i < 8; i++) {
                    sum += board[i][solutions[s][i]];
                }
                max_sum = max(max_sum, sum);
            }
            cout << setw(5) << max_sum << "\n";
        }
    }
    return 0;
}
