#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    if (!(cin >> n)) return 0;
    
    while (n--) {
        string s;
        if (!(cin >> s)) break;
        
        if (s == "1" || s == "4" || s == "78") {
            cout << "+\n";
        } else if (s.size() >= 2 && s[s.size() - 2] == '3' && s.back() == '5') {
            cout << "-\n";
        } else if (s.size() >= 2 && s[0] == '9' && s.back() == '4') {
            cout << "*\n";
        } else if (s.size() >= 3 && s[0] == '1' && s[1] == '9' && s[2] == '0') {
            cout << "?\n";
        }
    }
    
    return 0;
}
