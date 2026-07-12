#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        if (s == "0") {
            break;
        }
        
        int sum = 0;
        bool fail = false;
        
        for (char c : s) {
            if (isalpha(static_cast<unsigned char>(c))) {
                char lower_c = tolower(static_cast<unsigned char>(c));
                sum += (lower_c - 'a' + 1);
            } else {
                fail = true;
                break;
            }
        }
        
        if (fail) {
            cout << "Fail\n";
        } else {
            cout << sum << "\n";
        }
    }
    
    return 0;
}
