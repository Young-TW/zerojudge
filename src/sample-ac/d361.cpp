#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string m, n;
    while (cin >> m >> n) {
        bool m_zero = (m.find_first_not_of('0') == string::npos);
        bool n_zero = (n.find_first_not_of('0') == string::npos);
        
        if (m_zero && n_zero) break;
        
        if (n_zero) {
            cout << 1 << "\n";
        } else {
            int r = 0;
            for (char c : n) {
                r = (r * 10 + (c - '0')) % 4;
            }
            if (r == 0) r = 4;
            
            int d = m.back() - '0';
            int ans = 1;
            for (int i = 0; i < r; ++i) {
                ans = (ans * d) % 10;
            }
            cout << ans << "\n";
        }
    }
    
    return 0;
}
