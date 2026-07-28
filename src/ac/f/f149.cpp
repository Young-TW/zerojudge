#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int R, C;
    while (cin >> R >> C) {
        vector<vector<int>> a(R, vector<int>(C));
        long long totalBomb = 0;
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                cin >> a[i][j];
                if (a[i][j] == 1) ++totalBomb;
            }
        }

        const int dr[8] = { -1,-1,-1, 0,0, 1,1,1 };
        const int dc[8] = { -1, 0, 1,-1,1,-1,0,1 };

        vector<vector<char>> deact(R, vector<char>(C, 0));

        // Step 1 : deactivate colliding detectors
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (a[i][j] != 5) continue;
                for (int d = 0; d < 8; ++d) {
                    int ni = i + dr[d];
                    int nj = j + dc[d];
                    if (ni < 0 || ni >= R || nj < 0 || nj >= C) continue;
                    if (a[ni][nj] == 5) {
                        deact[i][j] = deact[ni][nj] = 1;
                    }
                }
            }
        }

        // Step 2 : detection
        long long detected = 0;
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (a[i][j] != 5 || deact[i][j]) continue; // only active detectors
                for (int d = 0; d < 8; ++d) {
                    int ni = i + dr[d];
                    int nj = j + dc[d];
                    if (ni < 0 || ni >= R || nj < 0 || nj >= C) continue;
                    if (a[ni][nj] == 1) {
                        ++detected;
                        a[ni][nj] = 0;               // bomb disappears
                    }
                }
            }
        }

        cout << detected << ' ' << (totalBomb - detected) << '\n';
    }
    return 0;
}
