#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        string s;
        cin >> s;
        
        int cnt = 0;
        bool ok = true;
        
        for (char c : s) {
            if (c == 'Y') {
                cnt++;
            } else {
                if (cnt == 0) {
                    ok = false;
                    break;
                }
                cnt--;
            }
        }
        
        if (ok && cnt == 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
