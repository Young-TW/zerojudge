#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int n;
vector<string> board;
int ans;

bool can_place(int r, int c) {
    for (int i = r - 1; i >= 0; --i) {
        if (board[i][c] == 'X') break;
        if (board[i][c] == 'O') return false;
    }
    for (int i = r + 1; i < n; ++i) {
        if (board[i][c] == 'X') break;
        if (board[i][c] == 'O') return false;
    }
    for (int j = c - 1; j >= 0; --j) {
        if (board[r][j] == 'X') break;
        if (board[r][j] == 'O') return false;
    }
    for (int j = c + 1; j < n; ++j) {
        if (board[r][j] == 'X') break;
        if (board[r][j] == 'O') return false;
    }
    return true;
}

void dfs(int r, int c, int count) {
    if (r == n) {
        ans = max(ans, count);
        return;
    }
    int nr = r, nc = c + 1;
    if (nc == n) {
        nc = 0;
        nr++;
    }
    
    if (board[r][c] == '.') {
        if (can_place(r, c)) {
            board[r][c] = 'O';
            dfs(nr, nc, count + 1);
            board[r][c] = '.';
        }
    }
    dfs(nr, nc, count);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> n && n) {
        board.assign(n, "");
        for (int i = 0; i < n; ++i) {
            cin >> board[i];
        }
        ans = 0;
        dfs(0, 0, 0);
        cout << ans << "\n";
    }
    return 0;
}
