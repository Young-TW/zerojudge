#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        int n = s.length();
        if (n % 2 != 0) {
            cout << "NO\n";
            continue;
        }
        
        bool is_palindrome = true;
        for (int i = 0; i < n / 2; ++i) {
            if (s[i] != s[n - 1 - i]) {
                is_palindrome = false;
                break;
            }
        }
        
        if (is_palindrome) {
            cout << "YES\n";
            cout << s.substr(0, n / 2) << "\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
