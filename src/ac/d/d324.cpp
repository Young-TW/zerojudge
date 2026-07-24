#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

int target_r, target_c;
vector<vector<int>> solutions;

void solve(int col, int row_mask, int d1_mask, int d2_mask, vector<int>& current) {
    if (col == 9) {
        solutions.push_back(current);
        return;
    }
    
    if (col == target_c) {
        int r = target_r;
        int bit = 1 << r;
        if (!(row_mask & bit) && !(d1_mask & bit) && !(d2_mask & bit)) {
            current.push_back(r);
            solve(col + 1, row_mask | bit, (d1_mask | bit) << 1, (d2_mask | bit) >> 1, current);
            current.pop_back();
        }
    } else {
        for (int r = 1; r <= 8; ++r) {
            int bit = 1 << r;
            if (!(row_mask & bit) && !(d1_mask & bit) && !(d2_mask & bit)) {
                current.push_back(r);
                solve(col + 1, row_mask | bit, (d1_mask | bit) << 1, (d2_mask | bit) >> 1, current);
                current.pop_back();
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        bool first_case = true;
        while (T--) {
            if (!first_case) {
                cout << "\n";
            }
            first_case = false;
            
            cin >> target_r >> target_c;
            
            solutions.clear();
            vector<int> current;
            solve(1, 0, 0, 0, current);
            
            cout << "SOLN       COLUMN\n";
            cout << " #      1 2 3 4 5 6 7 8\n";
            cout << "\n";
            
            for (size_t i = 0; i < solutions.size(); ++i) {
                cout << setw(2) << (i + 1) << "      ";
                for (int j = 0; j < 8; ++j) {
                    cout << solutions[i][j] << (j == 7 ? '\n' : ' ');
                }
            }
        }
    }
    
    return 0;
}
