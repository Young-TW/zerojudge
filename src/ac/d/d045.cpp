#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    for (int t = 1; t <= T; ++t) {
        vector<vector<bool>> solved(3, vector<bool>(10005, false));
        vector<vector<int>> problems(3);
        
        for (int i = 0; i < 3; ++i) {
            int S;
            cin >> S;
            for (int j = 0; j < S; ++j) {
                int p;
                cin >> p;
                if (!solved[i][p]) {
                    solved[i][p] = true;
                    problems[i].push_back(p);
                }
            }
        }
        
        vector<vector<int>> unique_problems(3);
        for (int i = 0; i < 3; ++i) {
            int j = (i + 1) % 3;
            int k = (i + 2) % 3;
            for (int p : problems[i]) {
                if (!solved[j][p] && !solved[k][p]) {
                    unique_problems[i].push_back(p);
                }
            }
            sort(unique_problems[i].begin(), unique_problems[i].end());
        }
        
        size_t max_count = 0;
        for (int i = 0; i < 3; ++i) {
            if (unique_problems[i].size() > max_count) {
                max_count = unique_problems[i].size();
            }
        }
        
        cout << "Case #" << t << ":\n";
        for (int i = 0; i < 3; ++i) {
            if (unique_problems[i].size() == max_count) {
                cout << (i + 1) << " " << unique_problems[i].size();
                for (int p : unique_problems[i]) {
                    cout << " " << p;
                }
                cout << "\n";
            }
        }
    }
    
    return 0;
}
