#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (!(cin >> t)) return 0;

    bool first_case = true;
    while (t--) {
        if (!first_case) {
            cout << "\n";
        }
        first_case = false;

        int m, n;
        cin >> m >> n;
        vector<string> grid(m);
        for (int i = 0; i < m; ++i) {
            cin >> grid[i];
            for (int j = 0; j < n; ++j) {
                grid[i][j] = tolower((unsigned char)grid[i][j]);
            }
        }

        int k;
        cin >> k;
        for (int q = 0; q < k; ++q) {
            string word;
            cin >> word;
            for (char &c : word) {
                c = tolower((unsigned char)c);
            }

            int len = (int)word.length();
            int ans_r = -1, ans_c = -1;

            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (grid[i][j] == word[0]) {
                        for (int d = 0; d < 8; ++d) {
                            bool match = true;
                            for (int l = 0; l < len; ++l) {
                                int ni = i + dx[d] * l;
                                int nj = j + dy[d] * l;
                                if (ni < 0 || ni >= m || nj < 0 || nj >= n || grid[ni][nj] != word[l]) {
                                    match = false;
                                    break;
                                }
                            }
                            if (match) {
                                ans_r = i + 1;
                                ans_c = j + 1;
                                break;
                            }
                        }
                    }
                    if (ans_r != -1) break;
                }
                if (ans_r != -1) break;
            }
            cout << ans_r << " " << ans_c << "\n";
        }
    }

    return 0;
}
