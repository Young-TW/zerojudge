#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s) {
        bool isNumber = true;
        for (size_t i = 0; i < s.size(); i++) {
            if (s[i] < '0' || s[i] > '9') { isNumber = false; break; }
        }
        if (isNumber) continue;
        
        int x = 0;
        for (size_t i = 0; i < s.size(); i++) {
            if (s[i] == 'A') {
                x ^= (int)(i + 1);
            }
        }
        cout << (x == 0 ? 'P' : 'N') << '\n';
    }
    return 0;
}
