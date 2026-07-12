#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N && N != 0) {
        long long best_val = -1;
        int best_idx = -1;
        
        for (int i = 1; i <= N; ++i) {
            long long w, h;
            cin >> w >> h;
            if (w < h) {
                swap(w, h);
            }
            
            long long val;
            if (w >= 4 * h) {
                val = 4 * h;
            } else {
                val = max(w, 2 * h);
            }
            
            if (val > best_val) {
                best_val = val;
                best_idx = i;
            }
        }
        
        cout << best_idx << "\n";
    }
    
    return 0;
}
