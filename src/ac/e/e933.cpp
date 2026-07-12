#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    if (!(cin >> s)) return 0;
    
    string w;
    while (cin >> w) {
        if (w.length() != s.length()) {
            continue;
        }
        
        bool ok = true;
        int len = s.length();
        for (int i = 0; i < len; ++i) {
            if (s[i] == w[i]) {
                ok = false;
                break;
            }
            for (int j = i + 1; j < len; ++j) {
                if (s[i] == s[j] && w[i] != w[j]) {
                    ok = false;
                    break;
                }
                if (w[i] == w[j] && s[i] != s[j]) {
                    ok = false;
                    break;
                }
            }
            if (!ok) {
                break;
            }
        }
        
        if (ok) {
            cout << w << "\n";
            return 0;
        }
    }
    
    cout << "impossible\n";
    return 0;
}
