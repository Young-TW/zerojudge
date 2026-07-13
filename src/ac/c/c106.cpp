#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        int need = 1;
        bool valid = true;
        int len = s.length();
        
        for (int i = 0; i < len; ++i) {
            char c = s[i];
            if (c >= 'p' && c <= 'z') {
                need--;
            } else if (c == 'N') {
                // need remains unchanged
            } else if (c == 'C' || c == 'D' || c == 'E' || c == 'I') {
                need++;
            } else {
                valid = false;
                break;
            }
            
            if (need <= 0) {
                if (i != len - 1) {
                    valid = false;
                    break;
                }
            }
        }
        
        if (valid && need == 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
