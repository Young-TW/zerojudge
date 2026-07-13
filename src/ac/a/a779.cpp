#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (getline(cin, s)) {
        string filtered = "";
        for (size_t i = 0; i < s.length(); ++i) {
            unsigned char c = s[i];
            if (isalnum(c)) {
                filtered += tolower(c);
            }
        }
        
        string rev = filtered;
        reverse(rev.begin(), rev.end());
        
        cout << s << "\n";
        if (filtered == rev) {
            cout << "-- is a palindrome\n";
        } else {
            cout << "-- is not a palindrome\n";
        }
    }
    
    return 0;
}
