#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    string pw;
    while (cin >> pw) {
        bool hasUpper = false, hasLower = false, hasLetter = false, hasDigitOrSym = false;
        for (char c : pw) {
            if (isupper((unsigned char)c)) { hasUpper = true; hasLetter = true; }
            else if (islower((unsigned char)c)) { hasLower = true; hasLetter = true; }
            else if (isdigit((unsigned char)c)) { hasDigitOrSym = true; }
            else { hasDigitOrSym = true; }
        }
        int cnt = 0;
        if (pw.size() >= 8) cnt++;
        if (hasUpper && hasLower) cnt++;
        if (hasLetter && hasDigitOrSym) cnt++;

        cout << "This password is ";
        if (cnt >= 3) cout << "STRONG";
        else if (cnt == 2) cout << "GOOD";
        else if (cnt == 1) cout << "ACCEPTABLE";
        else cout << "WEAK";
        cout << "\n";
    }
    return 0;
}
