#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

string bits8(unsigned char c) {
    string s;
    for (int i = 7; i >= 0; --i) {
        s += ((c >> i) & 1) ? '1' : '0';
    }
    return s;
}

int main() {
    string s;
    while (cin >> s) {
        string original = s;
        bool negative = false;
        if (s[0] == '-') {
            negative = true;
            s = s.substr(1);
        }
        long double val = stold(original);
        long double abs_val = fabsl(val);
        
        unsigned char byte1, byte2, byte3, byte4;
        unsigned int M = 0;
        int E = 0;
        int display_exp = 0;
        bool is_zero = (abs_val == 0.0L);
        
        if (is_zero) {
            byte1 = 0;
            M = 0;
            E = 0;
            display_exp = 0;
            byte2 = negative ? 0x80 : 0x00;
            byte3 = 0;
            byte4 = 0;
        } else {
            int exp2;
            long double m2 = frexp(abs_val, &exp2);
            long double m = m2 * 2.0L;
            int exp_true = exp2 - 1;
            long double frac = m - 1.0L;
            long double M_ld = frac * 8388608.0L + 1e-12L;
            M = (unsigned int)M_ld;
            if (M >= 8388608) {
                M -= 8388608;
                exp_true++;
            }
            E = exp_true + 129;
            if (E <= 0) {
                E = 0;
                M = 0;
                display_exp = -128;
            } else if (E >= 255) {
                E = 255;
                M = 0;
                display_exp = 127;
            } else {
                display_exp = E - 128;
            }
            byte1 = (unsigned char)E;
            byte2 = (negative ? 0x80 : 0x00) | ((M >> 16) & 0x7F);
            byte3 = (M >> 8) & 0xFF;
            byte4 = M & 0xFF;
        }
        
        cout << "Input a value: " << original << "\n";
        cout << "                 Exponent lst byte 2nd byte 3rd byte\n";
        cout << "Memory Contents= " << bits8(byte1) << " " << bits8(byte2) << " " << bits8(byte3) << " " << bits8(byte4) << "  \n";
        cout << "                 <&H" << hex << uppercase << setw(2) << setfill('0') << (int)byte1
             << ">   <&H" << setw(2) << (int)byte2
             << ">   <&H" << setw(2) << (int)byte3
             << ">   <&H" << setw(2) << (int)byte4 << ">" << dec << nouppercase << "\n";
        
        if (is_zero) {
            cout << "FLOATING POINT FORMAT => " << (negative ? "-" : "") << "0.00000000000000000000000 * 2 ^ 0\n";
        } else {
            string mantissa_str = "1";
            for (int i = 22; i >= 0; --i) {
                mantissa_str += ((M >> i) & 1) ? '1' : '0';
            }
            cout << "FLOATING POINT FORMAT => " << (negative ? "-" : "") << "0." << mantissa_str << " * 2 ^ " << display_exp << "\n";
        }
        cout << "Floating Point Value = " << original << "\n";
        cout << "=================================================================\n";
    }
    return 0;
}
