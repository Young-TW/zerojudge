#include <iostream>
#include <string>

using namespace std;

int charVal(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
    }
    return 0;
}

int romanToInt(const string& s) {
    int res = 0;
    for (size_t i = 0; i < s.length(); ++i) {
        int curr = charVal(s[i]);
        if (i + 1 < s.length()) {
            int next = charVal(s[i + 1]);
            if (curr < next) {
                res -= curr;
            } else {
                res += curr;
            }
        } else {
            res += curr;
        }
    }
    return res;
}

string intToRoman(int num) {
    string res = "";
    int vals[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string syms[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    for (int i = 0; i < 13; ++i) {
        while (num >= vals[i]) {
            num -= vals[i];
            res += syms[i];
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string h_str, m_str;
    while (cin >> h_str >> m_str) {
        int h = romanToInt(h_str);
        int m = romanToInt(m_str);
        
        m += 30;
        if (m >= 60) {
            m -= 60;
            h += 1;
        }
        h += 7;
        if (h > 24) {
            h -= 24;
        }
        
        cout << intToRoman(h) << "\n";
        cout << intToRoman(m) << "\n";
    }
    
    return 0;
}
