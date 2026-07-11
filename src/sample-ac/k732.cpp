#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> a(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> a[i][j];
            }
        }
        
        vector<pair<int, int>> ans;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int x = a[i][j];
                int sum = 0;
                for (int r = 0; r < n; ++r) {
                    for (int c = 0; c < m; ++c) {
                        int dist = (i > r ? i - r : r - i) + (j > c ? j - c : c - j);
                        if (dist <= x) {
                            sum += a[r][c];
                        }
                    }
                }
                if (sum % 10 == x) {
                    ans.push_back({i, j});
                }
            }
        }
        
        cout << ans.size() << "\n";
        for (size_t k = 0; k < ans.size(); ++k) {
            cout << ans[k].first << " " << ans[k].second << "\n";
        }
    }
    
    return 0;
}
