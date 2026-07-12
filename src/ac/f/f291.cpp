#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        long long col = 0;
        long long row = 0;
        size_t i = 0;
        
        while (i < s.size() && isalpha(s[i])) {
            col = col * 26 + (s[i] - 'A' + 1);
            ++i;
        }
        
        while (i < s.size() && isdigit(s[i])) {
            row = row * 10 + (s[i] - '0');
            ++i;
        }
        
        cout << col * row << "\n";
    }
    
    return 0;
}
