#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        if (s.find("\xE8\xA8\xB1") != string::npos || // 許 UTF-8
            s.find("\xE8\x93\x8B") != string::npos || // 蓋 UTF-8
            s.find("\xE5\x8A\x9F") != string::npos || // 功 UTF-8
            s.find("\xB3\x5C") != string::npos ||     // 許 Big5
            s.find("\xBB\x5C") != string::npos ||     // 蓋 Big5
            s.find("\xA5\x5C") != string::npos) {     // 功 Big5
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    
    return 0;
}
