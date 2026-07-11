#include <iostream>
#include <cstring>

using namespace std;

int M, N;
int board_size;
long long ans;

bool col[10];
int d1[20];
int d2[20];

void solve(int row, int q, int r) {
    if (row == board_size) {
        ans++;
        return;
    }
    for (int c = 0; c < board_size; ++c) {
        if (!col[c]) {
            int d1_idx = row + c;
            int d2_idx = row - c + board_size - 1;
            
            if (q > 0 && d1[d1_idx] == 0 && d2[d2_idx] == 0) {
                col[c] = true;
                d1[d1_idx] = 2;
                d2[d2_idx] = 2;
                solve(row + 1, q - 1, r);
                col[c] = false;
                d1[d1_idx] = 0;
                d2[d2_idx] = 0;
            }
            
            if (r > 0 && d1[d1_idx] != 2 && d2[d2_idx] != 2) {
                col[c] = true;
                int prev_d1 = d1[d1_idx];
                int prev_d2 = d2[d2_idx];
                d1[d1_idx] = 1;
                d2[d2_idx] = 1;
                solve(row + 1, q, r - 1);
                col[c] = false;
                d1[d1_idx] = prev_d1;
                d2[d2_idx] = prev_d2;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> M >> N) {
        board_size = M + N;
        ans = 0;
        memset(col, false, sizeof(col));
        memset(d1, 0, sizeof(d1));
        memset(d2, 0, sizeof(d2));
        solve(0, M, N);
        cout << ans << "\n";
    }
    
    return 0;
}
