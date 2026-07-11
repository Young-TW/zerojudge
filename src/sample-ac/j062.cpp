#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    int case_num = 1;
    
    while (cin >> n && n) {
        vector<vector<int>> matrix(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> matrix[i][j];
            }
        }
        
        int layers = (n + 1) / 2;
        vector<int> sums(layers, 0);
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int layer = min({i, j, n - 1 - i, n - 1 - j});
                sums[layer] += matrix[i][j];
            }
        }
        
        cout << "Case " << case_num << ":";
        for (int i = 0; i < layers; ++i) {
            cout << " " << sums[i];
        }
        cout << "\n";
        case_num++;
    }
    
    return 0;
}
