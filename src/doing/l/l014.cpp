#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int x, y;
    while (cin >> x >> y) {
        vector<string> board(y);
        vector<pair<int, int>> steps;
        
        for (int i = 0; i < y; ++i) {
            cin >> board[i];
            for (int j = 0; j < x; ++j) {
                if (board[i][j] != '-') {
                    int step_num = board[i][j] - '0';
                    if (step_num >= 1 && step_num <= 9) {
                        if (steps.size() < static_cast<size_t>(step_num)) {
                            steps.resize(step_num);
                        }
                        steps[step_num - 1] = make_pair(i + 1, j + 1);
                    }
                }
            }
        }
        
        for (size_t i = 0; i < steps.size(); ++i) {
            cout << "第" << (i + 1) << "步為第" << steps[i].first << "列，第" << steps[i].second << "行" << endl;
        }
    }
    
    return 0;
}
