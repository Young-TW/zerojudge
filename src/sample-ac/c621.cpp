#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        string digits = "";
        for (size_t i = 0; i < s.length(); ++i) {
            char c = s[i];
            if (isdigit(static_cast<unsigned char>(c))) {
                digits += c;
            }
        }
        reverse(digits.begin(), digits.end());
        
        string ans(s.length(), ' ');
        size_t d_idx = 0;
        for (size_t i = 0; i < s.length(); ++i) {
            char c = s[i];
            if (isdigit(static_cast<unsigned char>(c))) {
                ans[i] = digits[d_idx++];
            }
        }
        
        size_t l = 0;
        while (l < s.length()) {
            if (isalpha(static_cast<unsigned char>(s[l]))) {
                size_t r = l;
                while (r < s.length() && isalpha(static_cast<unsigned char>(s[r]))) {
                    r++;
                }
                for (size_t k = 0; k < r - l; ++k) {
                    ans[l + k] = s[r - 1 - k];
                }
                l = r;
            } else {
                l++;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
