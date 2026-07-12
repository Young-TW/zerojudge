#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int n;
            cin >> n;
            vector<int> a(n);
            for (int i = 0; i < n; ++i) {
                cin >> a[i];
            }
            
            set<vector<int>> seen;
            bool zero = false;
            
            while (true) {
                bool all_zero = true;
                for (int i = 0; i < n; ++i) {
                    if (a[i] != 0) {
                        all_zero = false;
                        break;
                    }
                }
                
                if (all_zero) {
                    zero = true;
                    break;
                }
                
                if (seen.count(a)) {
                    zero = false;
                    break;
                }
                
                seen.insert(a);
                
                vector<int> next_a(n);
                for (int i = 0; i < n; ++i) {
                    int diff = a[i] - a[(i + 1) % n];
                    next_a[i] = diff < 0 ? -diff : diff;
                }
                a = next_a;
            }
            
            if (zero) {
                cout << "ZERO\n";
            } else {
                cout << "LOOP\n";
            }
        }
    }
    
    return 0;
}
