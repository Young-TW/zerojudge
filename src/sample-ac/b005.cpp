#include <iostream>
#include <vector>

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
        
        vector<int> row_sum(n, 0);
        vector<int> col_sum(n, 0);
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                row_sum[i] += matrix[i][j];
                col_sum[j] += matrix[i][j];
            }
        }
        
        int odd_rows = 0;
        int odd_row_idx = -1;
        int odd_cols = 0;
        int odd_col_idx = -1;
        
        for (int i = 0; i < n; ++i) {
            if (row_sum[i] % 2 != 0) {
                odd_rows++;
                odd_row_idx = i;
            }
            if (col_sum[i] % 2 != 0) {
                odd_cols++;
                odd_col_idx = i;
            }
        }
        
        if (odd_rows == 0 && odd_cols == 0) {
            cout << "OK\n";
        } else if (odd_rows == 1 && odd_cols == 1) {
            cout << "Change bit (" << odd_row_idx + 1 << "," << odd_col_idx + 1 << ")\n";
        } else {
            cout << "Corrupt\n";
        }
    }
    
    return 0;
}
