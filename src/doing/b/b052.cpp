#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

string intToBinary(int n) {
    if (n == 0) return "0";
    string res;
    while (n > 0) {
        res += (n % 2) + '0';
        n /= 2;
    }
    reverse(res.begin(), res.end());
    return res;
}

string fracToBinary(double frac, int precision = 24) {
    string res;
    while (frac > 0 && res.size() < precision) {
        frac *= 2;
        if (frac >= 1) {
            res += '1';
            frac -= 1;
        } else {
            res += '0';
        }
    }
    return res;
}

int main() {
    string s;
    while (cin >> s) {
        size_t dot_pos = s.find('.');
        string int_part, frac_part;

        if (dot_pos != string::npos) {
            int_part = s.substr(0, dot_pos);
            frac_part = s.substr(dot_pos + 1);
        } else {
            int_part = s;
            frac_part = "";
        }

        int int_num = 0;
        if (!int_part.empty()) {
            int_num = stoi(int_part);
        }
        string int_binary = intToBinary(int_num);

        string frac_binary;
        if (!frac_part.empty()) {
            double frac_num = stod("0." + frac_part);
            frac_binary = fracToBinary(frac_num);
        }

        if (frac_binary.empty()) {
            cout << int_binary << endl;
        } else {
            cout << int_binary << "." << frac_binary << endl;
        }
    }
    return 0;
}
