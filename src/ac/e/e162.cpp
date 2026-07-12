#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s) {
        int n = s.length();
        int c0 = count(s.begin(), s.end(), '0');
        int c00 = 0;
        
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0' && s[(i + 1) % n] == '0') {
                c00++;
            }
        }
        
        if (c00 * n > c0 * c0) {
            cout << "SHOOT\n";
        } else if (c00 * n < c0 * c0) {
            cout << "ROTATE\n";
        } else {
            cout << "EQUAL\n";
        }
    }
    
    return 0;
}
