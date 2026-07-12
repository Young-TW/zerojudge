#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            vector<int> L;
            int x;
            while (cin >> x && x != 0) {
                L.push_back(x);
            }
            
            sort(L.rbegin(), L.rend());
            
            long long sum = 0;
            bool too_expensive = false;
            
            for (size_t i = 0; i < L.size(); ++i) {
                long long p = 1;
                for (size_t j = 0; j <= i; ++j) {
                    p *= L[i];
                    if (p > 5000000) {
                        p = 5000001;
                        break;
                    }
                }
                sum += 2 * p;
                if (sum > 5000000) {
                    too_expensive = true;
                    break;
                }
            }
            
            if (too_expensive) {
                cout << "Too expensive\n";
            } else {
                cout << sum << "\n";
            }
        }
    }
    
    return 0;
}
