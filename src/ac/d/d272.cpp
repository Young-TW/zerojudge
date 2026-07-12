#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    while (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            int cuts = 0;
            int cur_mask = 0;
            
            for (int i = 0; i < n; ++i) {
                string s;
                cin >> s;
                int next_mask = 0;
                for (char c : s) {
                    next_mask |= (1 << (c - 'a'));
                }
                
                if (cur_mask == 0) {
                    cur_mask = next_mask;
                } else {
                    int inter = cur_mask & next_mask;
                    if (inter == 0) {
                        cuts++;
                        cur_mask = next_mask;
                    } else {
                        cur_mask = inter;
                    }
                }
            }
            cout << cuts << "\n";
        }
    }
    
    return 0;
}
