#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m, n, k;
    // allow several test cases until EOF
    while (cin >> m >> n >> k) {
        vector<string> board(m);
        for (int i = 0; i < m; ++i) {
            cin >> board[i];
        }
        vector<int> dir(k);
        for (int i = 0; i < k; ++i) cin >> dir[i];

        // direction vectors: dx = column change, dy = row change
        const int dx[6] = { 0, 1, 1, 0, -1, -1 };
        const int dy[6] = { -1, 0, 1, 1, 0, -1 };

        int row = m - 1;   // start: left bottom
        int col = 0;

        string answer;
        answer.reserve(k);
        set<char> used;

        for (int d : dir) {
            int nr = row + dy[d];
            int nc = col + dx[d];
            if (0 <= nr && nr < m && 0 <= nc && nc < n) {
                row = nr;
                col = nc;
            }
            char ch = board[row][col];
            answer.push_back(ch);
            used.insert(ch);
        }

        cout << answer << '\n' << used.size() << '\n';
    }
    return 0;
}
