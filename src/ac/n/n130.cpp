#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int R, C;
    while (cin >> R >> C) {
        string line;
        getline(cin, line);               // consume end of line after C
        string S;
        getline(cin, S);                  // S may be empty
        vector<string> board(R);
        for (int i = 0; i < R; ++i) {
            getline(cin, board[i]);
        }

        int totalFree = 0;
        for (const auto &row : board)
            for (char ch : row)
                if (ch == '.') ++totalFree;

        int L = static_cast<int>(S.size());
        int lead = (totalFree - L) / 2;   // guaranteed integer

        int cnt = 0;                      // processed free cells
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (board[i][j] == '#') {
                    cout << '#';
                } else { // free cell
                    if (cnt < lead) {
                        cout << '.';
                    } else if (cnt < lead + L) {
                        cout << S[cnt - lead];
                    } else {
                        cout << '.';
                    }
                    ++cnt;
                }
            }
            cout << '\n';
        }
    }
    return 0;
}
