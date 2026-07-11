#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string board[15];
    while (cin >> board[0]) {
        for (int i = 1; i < 15; ++i) {
            cin >> board[i];
        }
        
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 30; ++j) {
                if (board[i][j] == '*') {
                    cout << '*';
                } else {
                    int cnt = 0;
                    for (int di = -1; di <= 1; ++di) {
                        for (int dj = -1; dj <= 1; ++dj) {
                            if (di == 0 && dj == 0) continue;
                            int ni = i + di;
                            int nj = j + dj;
                            if (ni >= 0 && ni < 15 && nj >= 0 && nj < 30) {
                                if (board[ni][nj] == '*') {
                                    cnt++;
                                }
                            }
                        }
                    }
                    if (cnt == 0) {
                        cout << '.';
                    } else {
                        cout << cnt;
                    }
                }
            }
            cout << "\n";
        }
    }
    
    return 0;
}
