#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int C;
    while (cin >> C) {
        vector<int> M(C);
        for (int i = 0; i < C; ++i) {
            cin >> M[i];
        }
        int L;
        cin >> L;
        
        sort(M.begin(), M.end());
        
        int required_N = L - M[0];
        
        if (C == 1) {
            cout << required_N << "\n";
        } else {
            int max_allowed_N = M[1] - L;
            if (required_N <= max_allowed_N) {
                cout << required_N << "\n";
            } else {
                cout << "You are too black!\n";
            }
        }
    }
    
    return 0;
}
