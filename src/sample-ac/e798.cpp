#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<vector<int>> arr(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> arr[i][j];
            }
        }

        for (int i = 0; i < n; i += 2) {
            for (int j = 0; j < n; j += 2) {
                int max_val = arr[i][j];
                max_val = max(max_val, arr[i][j + 1]);
                max_val = max(max_val, arr[i + 1][j]);
                max_val = max(max_val, arr[i + 1][j + 1]);
                
                if (j > 0) {
                    cout << " ";
                }
                cout << max_val;
            }
            cout << "\n";
        }
    }

    return 0;
}
