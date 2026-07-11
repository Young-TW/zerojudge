#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n) {
        vector<vector<bool>> reach(n + 1, vector<bool>(n + 1, false));
        
        int u;
        while (cin >> u && u) {
            int v;
            while (cin >> v && v) {
                reach[u][v] = true;
            }
        }
        
        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (reach[i][k] && reach[k][j]) {
                        reach[i][j] = true;
                    }
                }
            }
        }
        
        int q;
        cin >> q;
        while (q--) {
            int start;
            cin >> start;
            vector<int> unreachable;
            for (int i = 1; i <= n; ++i) {
                if (!reach[start][i]) {
                    unreachable.push_back(i);
                }
            }
            cout << unreachable.size();
            for (int x : unreachable) {
                cout << " " << x;
            }
            cout << "\n";
        }
    }
    
    return 0;
}
