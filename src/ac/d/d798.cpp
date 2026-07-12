#include <iostream>
#include <algorithm>

using namespace std;

int T[500][500];
int row_st[9][500][500];
int log2_table[501];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    log2_table[1] = 0;
    for (int i = 2; i <= 500; ++i) {
        log2_table[i] = log2_table[i / 2] + 1;
    }

    int N, M;
    while (cin >> N >> M) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> T[i][j];
            }
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                row_st[0][i][j] = T[i][j];
            }
            for (int k = 1; k <= log2_table[M]; ++k) {
                for (int j = 0; j + (1 << k) <= M; ++j) {
                    row_st[k][i][j] = max(row_st[k-1][i][j], row_st[k-1][i][j + (1 << (k-1))]);
                }
            }
        }

        int Q;
        cin >> Q;
        while (Q--) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1--; y1--; x2--; y2--;

            int ky = log2_table[y2 - y1 + 1];
            int y2_offset = y2 - (1 << ky) + 1;

            int ans = 0;
            for (int i = x1; i <= x2; ++i) {
                int* row = row_st[ky][i];
                int val = row[y1] > row[y2_offset] ? row[y1] : row[y2_offset];
                if (val > ans) ans = val;
            }
            cout << ans << "\n";
        }
    }

    return 0;
}
