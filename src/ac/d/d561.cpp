#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s) {
        bool is_neg = false;
        if (s[0] == '-') {
            is_neg = true;
            s = s.substr(1);
        } else if (s[0] == '+') {
            s = s.substr(1);
        }
        
        string int_part = "0";
        string frac_part = "";
        
        size_t dot_pos = s.find('.');
        if (dot_pos != string::npos) {
            if (dot_pos > 0) int_part = s.substr(0, dot_pos);
            frac_part = s.substr(dot_pos + 1);
        } else {
            int_part = s;
        }
        
        if (int_part.empty()) int_part = "0";
        
        // Pad frac_part to at least 3 characters
        while (frac_part.length() < 3) {
            frac_part += '0';
        }
        
        string combined = int_part + frac_part.substr(0, 2);
        
        if (frac_part[2] >= '5') {
            // Add 1 to combined
            int carry = 1;
            for (int i = combined.length() - 1; i >= 0 && carry; i--) {
                int sum = combined[i] - '0' + carry;
                combined[i] = sum % 10 + '0';
                carry = sum / 10;
            }
            if (carry) combined = "1" + combined;
        }
        
        // Now combined has at least 3 characters (since int_part is at least "0" and we added 2 chars)
        // Wait, if int_part was "0", combined is "0xx", length 3.
        // If int_part was "123", combined is "123xx", length 5.
        // We need to split combined back into int_part and frac_part.
        // The last 2 characters of combined are the fractional part.
        string new_frac = combined.substr(combined.length() - 2);
        string new_int = combined.substr(0, combined.length() - 2);
        if (new_int.empty()) new_int = "0";
        
        // Check if the result is zero
        bool is_zero = true;
        for (char c : new_int) {
            if (c != '0') {
                is_zero = false;
                break;
            }
        }
        if (new_frac != "00") is_zero = false;
        
        if (is_neg && !is_zero) {
            cout << "-";
        }
        cout << new_int << "." << new_frac << "\n";
    }
    
    return 0;
}
