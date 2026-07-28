#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    const string tpl[6] = {
        "..+---+",
        "./   /|",
        "+---+ |",
        "|   | +",
        "|   |/.",
        "+---+.."
    };

    int m, n;
    while (cin >> m >> n) {
        vector<vector<int> > h(m + 1, vector<int>(n + 1, 0));
        int K = 0;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                cin >> h[i][j];
                K = max(K, 2 * (m - i) + 3 * h[i][j] + 3);
            }
        }
        int L = 4 * n + 2 * m + 1;
        vector<string> cv(K, string(L, '.'));

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                for (int k = 1; k <= h[i][j]; ++k) {
                    int br = K - 1 - 2 * (m - i) - 3 * (k - 1);
                    int bc = 4 * (j - 1) + 2 * (m - i);
                    int tr = br - 5;
                    for (int r = 0; r < 6; ++r) {
                        for (int c = 0; c < 7; ++c) {
                            char ch = tpl[r][c];
                            if (ch != '.') cv[tr + r][bc + c] = ch;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < K; ++i) cout << cv[i] << '\n';
    }
    return 0;
}
