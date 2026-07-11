#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int B;
    while (cin >> B) {
        int P;
        if (!(cin >> P)) break;
        
        vector<int> diff(B + 2, 0);
        
        for (int i = 0; i < P; ++i) {
            int X, Y;
            cin >> X >> Y;
            int L = min(X, Y);
            int R = max(X, Y);
            diff[L]++;
            diff[R + 1]--;
        }
        
        int min_val = 1e9;
        int max_val = -1;
        int min_idx = -1;
        int max_idx = -1;
        int current = 0;
        
        for (int i = 1; i <= B; ++i) {
            current += diff[i];
            if (current < min_val) {
                min_val = current;
                min_idx = i;
            }
            if (current >= max_val) {
                max_val = current;
                max_idx = i;
            }
        }
        
        cout << min_idx << " " << max_idx << "\n";
    }
    
    return 0;
}
