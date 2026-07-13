#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int n, p;
    while (cin >> n && n != 0) {
        cin >> p;
        
        vector<int> scores(n - 1);
        vector<vector<char>> answers(n, vector<char>(p));
        
        for (int i = 0; i < n - 1; ++i) {
            cin >> scores[i];
            for (int j = 0; j < p; ++j) {
                cin >> answers[i][j];
            }
        }
        
        for (int j = 0; j < p; ++j) {
            cin >> answers[n - 1][j];
        }
        
        int min_score = p + 1;
        int max_score = -1;
        bool possible = false;
        
        for (int mask = 0; mask < (1 << p); ++mask) {
            vector<char> key(p);
            for (int j = 0; j < p; ++j) {
                key[j] = (mask & (1 << j)) ? 'Y' : 'N';
            }
            
            bool valid = true;
            for (int i = 0; i < n - 1; ++i) {
                int score = 0;
                for (int j = 0; j < p; ++j) {
                    if (answers[i][j] == key[j]) {
                        score++;
                    }
                }
                if (score != scores[i]) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                possible = true;
                int d_score = 0;
                for (int j = 0; j < p; ++j) {
                    if (answers[n - 1][j] == key[j]) {
                        d_score++;
                    }
                }
                
                if (d_score < min_score) min_score = d_score;
                if (d_score > max_score) max_score = d_score;
            }
        }
        
        if (!possible) {
            cout << "c" << endl;
        } else if (min_score == max_score) {
            cout << "y " << min_score << endl;
        } else {
            cout << "n" << endl;
        }
    }
    
    return 0;
}
