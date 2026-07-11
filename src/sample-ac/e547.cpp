#include <iostream>
#include <string>
#include <cctype>

using namespace std;

void parse(const string& s, int& a, int& b) {
    a = 0;
    b = 0;
    int sign = 1;
    size_t i = 0;
    while (i < s.length()) {
        if (s[i] == '+') {
            sign = 1;
            i++;
        } else if (s[i] == '-') {
            sign = -1;
            i++;
        }
        int num = 0;
        bool hasNum = false;
        while (i < s.length() && isdigit(s[i])) {
            num = num * 10 + (s[i] - '0');
            i++;
            hasNum = true;
        }
        if (i < s.length() && s[i] == 'x') {
            if (!hasNum) num = 1;
            a += sign * num;
            i++;
        } else {
            b += sign * num;
        }
    }
}

int main() {
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        string eq;
        if (!(cin >> eq)) break;
        size_t eq_pos = eq.find('=');
        string left = eq.substr(0, eq_pos);
        string right = eq.substr(eq_pos + 1);
        int a1, b1, a2, b2;
        parse(left, a1, b1);
        parse(right, a2, b2);
        int A = a1 - a2;
        int B = b1 - b2;
        if (A == 0) {
            if (B == 0) {
                cout << "IDENTITY" << endl;
            } else {
                cout << "IMPOSSIBLE" << endl;
            }
        } else {
            int val = -B / A;
            if (-B % A != 0 && ((-B < 0) != (A < 0))) {
                val--;
            }
            cout << val << endl;
        }
    }
    return 0;
}
