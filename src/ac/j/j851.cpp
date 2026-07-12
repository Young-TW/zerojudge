#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m) {
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
        }
        
        long long ans = 0;
        
        for (int i = 0; i < n; ++i) {
            int last = -1;
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '#') {
                    if (last != -1) {
                        ans++;
                    }
                    last = j;
                }
            }
        }
        
        for (int j = 0; j < m; ++j) {
            int last = -1;
            for (int i = 0; i < n; ++i) {
                if (grid[i][j] == '#') {
                    if (last != -1) {
                        ans++;
                    }
                    last = i;
                }
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
