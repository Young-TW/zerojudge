#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int K;
    while (cin >> K) {
        int row_short = (K + 2) / 2;
        int valley_col = 2 * K - row_short;
        int L_start = 3 * K - row_short - 1;
        
        for (int row = 1; row <= K; ++row) {
            vector<int> cols;
            if (row == 1) {
                for (int c = L_start; c < L_start + 2 * K; ++c)
                    cols.push_back(c);
            } else if (row == row_short) {
                for (int c = 1; c <= K; ++c)
                    cols.push_back(c);
                int col_R = L_start + 1 - row_short;
                cols.push_back(col_R);
            } else {
                if (row > row_short && row < K) {
                    int col_L = row + K - row_short;
                    cols.push_back(col_L);
                }
                if (row > 1 && row < K) {
                    int col_R = L_start + 1 - row;
                    cols.push_back(col_R);
                }
                if (row == K) {
                    cols.push_back(valley_col);
                }
            }
            
            int end_col = 0;
            for (int c : cols)
                if (c > end_col) end_col = c;
            
            string s(end_col, ' ');
            for (int c : cols)
                s[c - 1] = '*';
            cout << s << '\n';
        }
    }
    return 0;
}
