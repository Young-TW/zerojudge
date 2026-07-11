#include <iostream>
#include <string>

using namespace std;

int n;
int bad[15];
long long ans;

void solve(int row, int col, int diag1, int diag2) {
    if (row == n) {
        ans++;
        return;
    }
    int available = ~(col | diag1 | diag2 | bad[row]) & ((1 << n) - 1);
    while (available) {
        int p = available & -available;
        available ^= p;
        solve(row + 1, col | p, (diag1 | p) << 1, (diag2 | p) >> 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int case_num = 1;
    while (cin >> n && n) {
        for (int i = 0; i < n; ++i) {
            bad[i] = 0;
            string s;
            cin >> s;
            for (int j = 0; j < n; ++j) {
                if (s[j] == '*') {
                    bad[i] |= (1 << j);
                }
            }
        }
        ans = 0;
        solve(0, 0, 0, 0);
        cout << "Case " << case_num++ << ": " << ans << "\n";
    }
    return 0;
}
