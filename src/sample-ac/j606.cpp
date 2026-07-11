#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int K, Q, R;
    while (cin >> K >> Q >> R) {
        string S;
        cin >> S;
        
        vector<vector<char>> ans(Q, vector<char>(R));
        string current = S;
        
        for (int q = 0; q < Q; ++q) {
            string next(K, ' ');
            for (int i = 0; i < K; ++i) {
                int p;
                cin >> p;
                next[p - 1] = current[i];
            }
            current = next;
            for (int r = 0; r < R; ++r) {
                ans[q][r] = current[r];
            }
        }
        
        for (int r = 0; r < R; ++r) {
            for (int q = 0; q < Q; ++q) {
                cout << ans[q][r];
            }
            cout << "\n";
        }
    }
    
    return 0;
}
