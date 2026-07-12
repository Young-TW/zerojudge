#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, Q;
    int case_num = 1;
    
    while (cin >> N >> Q) {
        if (N == 0 && Q == 0) break;
        
        vector<int> marbles(N);
        for (int i = 0; i < N; ++i) {
            cin >> marbles[i];
        }
        
        sort(marbles.begin(), marbles.end());
        
        cout << "CASE# " << case_num << ":\n";
        
        for (int i = 0; i < Q; ++i) {
            int x;
            cin >> x;
            
            auto it = lower_bound(marbles.begin(), marbles.end(), x);
            if (it != marbles.end() && *it == x) {
                cout << x << " found at " << (distance(marbles.begin(), it) + 1) << "\n";
            } else {
                cout << x << " not found\n";
            }
        }
        
        case_num++;
    }
    
    return 0;
}
