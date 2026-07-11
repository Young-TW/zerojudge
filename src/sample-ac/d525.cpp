#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        if (s == "0") break;
        
        unsigned long long x;
        int sum_parity = 0;
        while (cin >> x) {
            if (x == 0) break;
            sum_parity ^= (x & 1);
        }
        
        int ans_parity = (s.back() - '0') & 1;
        
        if (ans_parity != sum_parity) {
            cout << 0 << "\n";
        } else {
            cout << (sum_parity ? 2 : 1) << "\n";
        }
    }
    
    return 0;
}
