#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    if (!(cin >> n)) return 0;
    
    while (n--) {
        string s;
        cin >> s;
        string digits = "";
        for (char c : s) {
            if (c != '-') {
                digits += c;
            }
        }
        
        bool valid = true;
        if (digits.length() == 10) {
            int S = 0;
            for (int i = 0; i < 9; ++i) {
                if (!isdigit(static_cast<unsigned char>(digits[i]))) {
                    valid = false;
                    break;
                }
                S += (digits[i] - '0') * (10 - i);
            }
            if (valid) {
                int M = S % 11;
                int N = 11 - M;
                char expected_check;
                if (N == 10) expected_check = 'X';
                else if (N == 11) expected_check = '0';
                else expected_check = N + '0';
                
                if (digits[9] != expected_check) {
                    valid = false;
                }
            }
        } else if (digits.length() == 13) {
            int S = 0;
            for (int i = 0; i < 12; ++i) {
                if (!isdigit(static_cast<unsigned char>(digits[i]))) {
                    valid = false;
                    break;
                }
                S += (digits[i] - '0') * ((i % 2 == 0) ? 1 : 3);
            }
            if (valid) {
                int M = S % 10;
                int N = 10 - M;
                char expected_check;
                if (N == 10) expected_check = '0';
                else expected_check = N + '0';
                
                if (digits[12] != expected_check) {
                    valid = false;
                }
            }
        } else {
            valid = false;
        }
        
        cout << (valid ? 'T' : 'F') << '\n';
    }
    
    return 0;
}
