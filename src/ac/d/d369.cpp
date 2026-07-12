#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int romanToInt(const string& s) {
    unordered_map<char, int> m;
    m['I'] = 1;
    m['V'] = 5;
    m['X'] = 10;
    m['L'] = 50;
    m['C'] = 100;
    m['D'] = 500;
    m['M'] = 1000;
    
    int res = 0;
    for (size_t i = 0; i < s.length(); ++i) {
        if (i + 1 < s.length() && m[s[i]] < m[s[i+1]]) {
            res -= m[s[i]];
        } else {
            res += m[s[i]];
        }
    }
    return res;
}

string intToRoman(int num) {
    int val[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string sym[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    string res = "";
    for (int i = 0; i < 13; ++i) {
        while (num >= val[i]) {
            num -= val[i];
            res += sym[i];
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            int type;
            cin >> type;
            if (type == 1) {
                string s;
                cin >> s;
                cout << romanToInt(s) << "\n";
            } else {
                int num;
                cin >> num;
                cout << intToRoman(num) << "\n";
            }
        }
    }
    return 0;
}
