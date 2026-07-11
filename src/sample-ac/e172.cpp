#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    bool first_case = true;
    while (cin >> n && n != 0) {
        if (!first_case) {
            cout << "\n";
        }
        first_case = false;
        
        int board[20][20] = {0};
        vector<pair<int, int>> duplicates;
        
        for (int i = 1; i <= n; ++i) {
            int x, y;
            cin >> x >> y;
            if (board[x][y] == 0) {
                board[x][y] = i;
            } else {
                duplicates.push_back({board[x][y], i});
            }
        }
        
        for (int y = 19; y >= 1; --y) {
            for (int x = 1; x <= 19; ++x) {
                if (x > 1) cout << " ";
                cout << board[x][y];
            }
            cout << "\n";
        }
        
        sort(duplicates.begin(), duplicates.end());
        
        for (size_t i = 0; i < duplicates.size(); ++i) {
            cout << duplicates[i].first << " = " << duplicates[i].second << "\n";
        }
    }
    
    return 0;
}
