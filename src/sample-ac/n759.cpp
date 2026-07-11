#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (getline(cin, s)) {
        if (s == "DONE") break;
        
        string clean = "";
        for (char c : s) {
            if (c >= 'A' && c <= 'Z') {
                clean += (char)(c - 'A' + 'a');
            } else if (c >= 'a' && c <= 'z') {
                clean += c;
            }
        }
        
        bool is_palindrome = true;
        int n = clean.size();
        for (int i = 0; i < n / 2; ++i) {
            if (clean[i] != clean[n - 1 - i]) {
                is_palindrome = false;
                break;
            }
        }
        
        if (is_palindrome) {
            cout << "You won't be eaten!\n";
        } else {
            cout << "Uh oh..\n";
        }
    }
    
    return 0;
}
