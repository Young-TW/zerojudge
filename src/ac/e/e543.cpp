#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    string mirror(256, 0);
    mirror['A'] = 'A';
    mirror['E'] = '3';
    mirror['H'] = 'H';
    mirror['I'] = 'I';
    mirror['J'] = 'L';
    mirror['L'] = 'J';
    mirror['M'] = 'M';
    mirror['O'] = 'O';
    mirror['S'] = '2';
    mirror['T'] = 'T';
    mirror['U'] = 'U';
    mirror['V'] = 'V';
    mirror['W'] = 'W';
    mirror['X'] = 'X';
    mirror['Y'] = 'Y';
    mirror['Z'] = '5';
    mirror['1'] = '1';
    mirror['2'] = 'S';
    mirror['3'] = 'E';
    mirror['5'] = 'Z';
    mirror['8'] = '8';
    mirror['0'] = 'O';

    while (cin >> s) {
        bool isPalin = true;
        bool isMirror = true;
        int n = s.length();
        for (int i = 0; i < n; ++i) {
            if (s[i] != s[n - 1 - i]) {
                isPalin = false;
            }
            if (mirror[s[i]] != s[n - 1 - i]) {
                isMirror = false;
            }
        }

        cout << s << " -- is ";
        if (isPalin && isMirror) {
            cout << "a mirrored palindrome.";
        } else if (isMirror) {
            cout << "a mirrored string.";
        } else if (isPalin) {
            cout << "a regular palindrome.";
        } else {
            cout << "not a palindrome.";
        }
        cout << "\n\n";
    }
    return 0;
}
