#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int R, C;
    while (cin >> R >> C) {
        string S;
        cin >> S;
        vector<string> grid(R);
        for (int i = 0; i < R; ++i) {
            cin >> grid[i];
        }
        
        int total_spaces = 0;
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (grid[i][j] == '.') {
                    total_spaces++;
                }
            }
        }
        
        int len = S.length();
        int leading = (total_spaces - len) / 2;
        
        int space_count = 0;
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (grid[i][j] == '.') {
                    if (space_count < leading) {
                        cout << '.';
                    } else if (space_count < leading + len) {
                        cout << S[space_count - leading];
                    } else {
                        cout << '.';
                    }
                    space_count++;
                } else {
                    cout << '#';
                }
            }
            cout << "\n";
        }
    }
    
    return 0;
}
