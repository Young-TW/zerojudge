#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        int i = s.length() - 1;
        while (i >= 0 && s[i] == '0') {
            s[i] = '9';
            i--;
        }
        s[i]--;
        
        if (s.length() > 1 && s[0] == '0') {
            cout << s.substr(1) << "\n";
        } else {
            cout << s << "\n";
        }
    }
    
    return 0;
}
