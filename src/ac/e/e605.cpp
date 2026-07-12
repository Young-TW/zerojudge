#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    int case_num = 1;
    bool first_case = true;
    
    while (cin >> n >> m && (n || m)) {
        if (!first_case) {
            cout << "\n";
        }
        first_case = false;
        
        cout << "Field #" << case_num++ << ":\n";
        
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
        }
        
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '*') {
                    cout << '*';
                } else {
                    int count = 0;
                    for (int k = 0; k < 8; ++k) {
                        int ni = i + dx[k];
                        int nj = j + dy[k];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj] == '*') {
                            count++;
                        }
                    }
                    cout << count;
                }
            }
            cout << "\n";
        }
    }
    
    return 0;
}
