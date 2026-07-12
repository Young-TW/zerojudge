#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<string> grid(n);
        vector<bool> row_bomb(n, false);
        vector<bool> col_bomb(n, false);
        
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '*') {
                    row_bomb[i] = true;
                    col_bomb[j] = true;
                }
            }
        }
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (row_bomb[i] || col_bomb[j]) {
                    cout << '*';
                } else {
                    cout << '0';
                }
            }
            cout << '\n';
        }
    }
    
    return 0;
}
