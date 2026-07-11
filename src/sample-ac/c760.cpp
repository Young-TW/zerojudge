#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        if (!s.empty()) {
            s[0] = toupper(static_cast<unsigned char>(s[0]));
        }
        cout << s << "\n";
    }
    
    return 0;
}
