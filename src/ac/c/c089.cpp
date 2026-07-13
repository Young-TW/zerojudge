#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string num_str;
    int from_base, to_base;
    
    while (cin >> num_str >> from_base >> to_base) {
        unsigned long long val = 0;
        bool too_large = false;
        
        for (char c : num_str) {
            int digit;
            if (c >= '0' && c <= '9') {
                digit = c - '0';
            } else if (c >= 'A' && c <= 'F') {
                digit = c - 'A' + 10;
            } else if (c >= 'a' && c <= 'f') {
                digit = c - 'a' + 10;
            } else {
                digit = 0;
            }
            
            val = val * from_base + digit;
            if (val > 268435455ULL) {
                too_large = true;
                break;
            }
        }
        
        string res = "";
        if (too_large) {
            res = "ERROR";
        } else {
            if (val == 0) {
                res = "0";
            } else {
                unsigned long long temp_val = val;
                while (temp_val > 0) {
                    int digit = temp_val % to_base;
                    char c = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
                    res = c + res;
                    temp_val /= to_base;
                }
            }
            if (res.length() > 7) {
                res = "ERROR";
            }
        }
        
        cout << setw(7) << res << "\n";
    }
    
    return 0;
}
