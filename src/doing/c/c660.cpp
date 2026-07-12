#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        string lower_s = s;
        for (size_t i = 0; i < lower_s.length(); ++i) {
            lower_s[i] = tolower(static_cast<unsigned char>(lower_s[i]));
        }
        
        for (size_t i = 0; i < s.length(); ++i) {
            char original = lower_s[i];
            lower_s[i] = toupper(static_cast<unsigned char>(lower_s[i]));
            cout << lower_s << '\n';
            lower_s[i] = original;
        }
    }
    
    return 0;
}
