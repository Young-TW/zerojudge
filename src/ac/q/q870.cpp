#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        vector<vector<int>> matrix(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> matrix[i][j];
            }
        }

        vector<int> p(n, 0); // row sums
        vector<int> m(n, 0); // col sums

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                p[i] += matrix[i][j];
                m[j] += matrix[i][j];
            }
        }

        int cnt_m = 0, cnt_p = 0;
        for (int i = 0; i < n; ++i) {
            if (m[i] > p[i]) cnt_m++;
            else if (p[i] > m[i]) cnt_p++;
        }

        if (cnt_m > cnt_p) {
            vector<int> col_indices(n);
            for (int i = 0; i < n; ++i) col_indices[i] = i;
            sort(col_indices.begin(), col_indices.end(), [&](int a, int b) {
                if (m[a] != m[b]) return m[a] < m[b];
                return a < b;
            });

            for (int i = 0; i < n; ++i) {
                int col_idx = col_indices[i];
                for (int j = 0; j < n; ++j) {
                    cout << matrix[j][col_idx] << (j == n - 1 ? "" : " ");
                }
                cout << "\n";
            }
        } else if (cnt_p > cnt_m) {
            vector<int> row_indices(n);
            for (int i = 0; i < n; ++i) row_indices[i] = i;
            sort(row_indices.begin(), row_indices.end(), [&](int a, int b) {
                if (p[a] != p[b]) return p[a] < p[b];
                return a < b;
            });

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    int row_idx = row_indices[j];
                    cout << matrix[row_idx][i] << (j == n - 1 ? "" : " ");
                }
                cout << "\n";
            }
        } else {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    cout << matrix[i][j] << (j == n - 1 ? "" : " ");
                }
                cout << "\n";
            }
        }
    }
    return 0;
}
