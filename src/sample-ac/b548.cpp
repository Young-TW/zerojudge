#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int val;
    while (cin >> val) {
        int board[5][5];
        board[0][0] = val;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (i == 0 && j == 0) continue;
                cin >> board[i][j];
            }
        }
        
        bool marked[26] = {false};
        int called;
        while (cin >> called && called != -1) {
            if (called >= 1 && called <= 25) {
                marked[called] = true;
            }
        }
        
        int best_num = -1;
        int max_score = -1;
        
        for (int num = 1; num <= 25; ++num) {
            if (!marked[num]) {
                marked[num] = true;
                int score = 0;
                
                // check rows
                for (int i = 0; i < 5; ++i) {
                    bool all_marked = true;
                    for (int j = 0; j < 5; ++j) {
                        if (!marked[board[i][j]]) {
                            all_marked = false;
                            break;
                        }
                    }
                    if (all_marked) score++;
                }
                
                // check cols
                for (int j = 0; j < 5; ++j) {
                    bool all_marked = true;
                    for (int i = 0; i < 5; ++i) {
                        if (!marked[board[i][j]]) {
                            all_marked = false;
                            break;
                        }
                    }
                    if (all_marked) score++;
                }
                
                // check diagonals
                bool diag1 = true;
                for (int i = 0; i < 5; ++i) {
                    if (!marked[board[i][i]]) {
                        diag1 = false;
                        break;
                    }
                }
                if (diag1) score++;
                
                bool diag2 = true;
                for (int i = 0; i < 5; ++i) {
                    if (!marked[board[i][4 - i]]) {
                        diag2 = false;
                        break;
                    }
                }
                if (diag2) score++;
                
                if (score > max_score) {
                    max_score = score;
                    best_num = num;
                }
                
                marked[num] = false;
            }
        }
        
        cout << best_num << "\n";
    }
    
    return 0;
}
