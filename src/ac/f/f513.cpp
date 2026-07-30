#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    int R, C;
    while (cin >> R >> C) {
        vector<vector<int> > a(R, vector<int>(C));
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                cin >> a[i][j];

        int cnt = 0;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                bool isolated = true;
                for (int k = 0; k < 8; k++) {
                    int ni = i + dr[k];
                    int nj = j + dc[k];
                    if (ni >= 0 && ni < R && nj >= 0 && nj < C && a[ni][nj] == a[i][j]) {
                        isolated = false;
                        break;
                    }
                }
                if (isolated) cnt++;
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}
