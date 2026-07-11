#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    while (cin >> t) {
        while (t--) {
            string n_str;
            if (!(cin >> n_str)) break;
            
            int S = 0;
            for (char c : n_str) {
                S += (c - '0');
            }
            
            int L = n_str.length();
            int k = L - 1;
            int m = 0;
            for (int i = L - 1; i >= 0; --i) {
                if (n_str[i] == '9') {
                    m++;
                } else {
                    break;
                }
            }
            
            int ans = S + 9 * max(0, k - m);
            cout << ans << "\n";
        }
    }
    
    return 0;
}
