#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        for (size_t i = 0; i < s.length(); ++i) {
            if (i > 0) {
                cout << "_";
            }
            cout << (int)(unsigned char)s[i];
        }
        cout << "\n";
    }
    
    return 0;
}
