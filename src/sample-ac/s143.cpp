#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int row, col;
    while (cin >> row >> col) {
        int matrix[105][105];
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                cin >> matrix[i][j];
            }
        }
        
        for (int j = 0; j < col; ++j) {
            for (int i = 0; i < row; ++i) {
                cout << matrix[i][j];
                if (i < row - 1) {
                    cout << " ";
                }
            }
            cout << "\n";
        }
    }
    return 0;
}
