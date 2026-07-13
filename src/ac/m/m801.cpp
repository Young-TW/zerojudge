#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    string mirror = "AHIMOTUVWXY";
    
    while (cin >> s) {
        bool ok = true;
        int n = s.length();
        for (int i = 0; i < n; ++i) {
            if (mirror.find(s[i]) == string::npos) {
                ok = false;
                break;
            }
            if (s[i] != s[n - 1 - i]) {
                ok = false;
                break;
            }
        }
        
        if (ok) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    
    return 0;
}
