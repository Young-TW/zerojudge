#include <iostream>
#include <string>

using namespace std;

void solve() {
    int T;
    while (cin >> T) {
        string line;
        getline(cin, line); // consume rest of the line containing T
        while (T--) {
            getline(cin, line); // blank line separating test cases
            int grid[3][3];
            for (int i = 0; i < 3; ++i) {
                getline(cin, line);
                for (int j = 0; j < 3; ++j) {
                    grid[i][j] = line[j] - '0';
                }
            }
            
            bool is_zero = true;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (grid[i][j] != 0) {
                        is_zero = false;
                    }
                }
            }
            
            if (is_zero) {
                cout << -1 << "\n";
                continue;
            }
            
            int steps = 0;
            while (true) {
                int next_grid[3][3] = {0};
                bool next_is_zero = true;
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        int sum = 0;
                        if (i > 0) sum += grid[i-1][j];
                        if (i < 2) sum += grid[i+1][j];
                        if (j > 0) sum += grid[i][j-1];
                        if (j < 2) sum += grid[i][j+1];
                        next_grid[i][j] = sum % 2;
                        if (next_grid[i][j] != 0) {
                            next_is_zero = false;
                        }
                    }
                }
                steps++;
                if (next_is_zero) {
                    break;
                }
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        grid[i][j] = next_grid[i][j];
                    }
                }
            }
            cout << steps - 1 << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
