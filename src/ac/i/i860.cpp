#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        long long m, y, c;
        string s;
        cin >> m >> y >> c >> s;
        
        bool ok = true;
        for (char ch : s) {
            if (ch == 'M') {
                m--;
            } else if (ch == 'Y') {
                y--;
            } else if (ch == 'C') {
                c--;
            } else if (ch == 'R') {
                m--;
                y--;
            } else if (ch == 'B') {
                m--;
                y--;
                c--;
            } else if (ch == 'G') {
                y--;
                c--;
            } else if (ch == 'V') {
                m--;
                c--;
            } else if (ch == 'W') {
                // White requires no paint
            }
            
            if (m < 0 || y < 0 || c < 0) {
                ok = false;
                break;
            }
        }
        
        if (ok) {
            cout << "YES " << m << " " << y << " " << c << "\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
