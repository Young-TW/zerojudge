#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            string s;
            cin >> s;
            
            int non_zero = 0;
            while (non_zero < (int)s.length() - 1 && s[non_zero] == '0') {
                non_zero++;
            }
            s = s.substr(non_zero);
            
            if (s == "0") {
                cout << 1 << "\n";
            } else if (s == "1") {
                cout << 66 << "\n";
            } else {
                int d = s.back() - '0';
                int r = d % 5;
                if (r == 2) cout << 56 << "\n";
                else if (r == 3) cout << 96 << "\n";
                else if (r == 4) cout << 36 << "\n";
                else if (r == 0) cout << 76 << "\n";
                else if (r == 1) cout << 16 << "\n";
            }
        }
    }
    
    return 0;
}
