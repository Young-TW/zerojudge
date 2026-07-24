#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        vector<int> moves(m);
        for (int i = 0; i < m; ++i) {
            cin >> moves[i];
        }

        // win[i] = true 表示剩 i 顆石頭時，當前玩家必勝
        vector<bool> win(n + 1, false);

        for (int i = 1; i <= n; ++i) {
            for (int s : moves) {
                if (i >= s && !win[i - s]) {
                    win[i] = true;
                    break;
                }
            }
        }

        if (win[n]) {
            cout << "Stan wins\n";
        } else {
            cout << "Ollie wins\n";
        }
    }

    return 0;
}
