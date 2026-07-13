#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <functional>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<vector<string>> board(N + 1, vector<string>(N + 1));
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                cin >> board[i][j];
            }
        }
        
        int M;
        if (!(cin >> M)) break;
        
        int score[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
        
        for (int i = 0; i < M; ++i) {
            string word;
            int r, c;
            char dir;
            cin >> word >> r >> c >> dir;
            
            int letter_score = 0;
            int word_mult = 1;
            
            for (size_t j = 0; j < word.length(); ++j) {
                char ch = word[j];
                int base = score[ch - 'A'];
                int curr_r = r, curr_c = c;
                
                if (dir == 'V') curr_r += j;
                else curr_c += j;
                
                if (curr_r >= 1 && curr_r <= N && curr_c >= 1 && curr_c <= N) {
                    string cell = board[curr_r][curr_c];
                    int letter_mult = 1;
                    
                    if (cell[0] == '2' && cell[1] == 'L') {
                        letter_mult = 2;
                    } else if (cell[0] == '3' && cell[1] == 'L') {
                        letter_mult = 3;
                    } else if (cell[0] == '2' && cell[1] == 'W') {
                        word_mult *= 2;
                    } else if (cell[0] == '3' && cell[1] == 'W') {
                        word_mult *= 3;
                    }
                    
                    letter_score += base * letter_mult;
                } else {
                    letter_score += base;
                }
            }
            
            cout << word << " " << letter_score * word_mult << "\n";
        }
    }
    
    return 0;
}
