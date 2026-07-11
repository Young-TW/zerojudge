#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            string res = "";
            int j = 0;
            int len = s.length();
            while (j < len) {
                if (s[j] == '0') {
                    if (s[j+1] == '0') { res += 'A'; j += 2; }
                    else { res += 'B'; j += 2; }
                } else {
                    if (s[j+1] == '0') {
                        if (s[j+2] == '0') { res += '0'; j += 3; }
                        else { res += '1'; j += 3; }
                    } else {
                        if (s[j+2] == '0') {
                            if (s[j+3] == '0') { res += '2'; j += 4; }
                            else { res += '3'; j += 4; }
                        } else {
                            if (s[j+3] == '0') {
                                if (s[j+4] == '0') { res += '4'; j += 5; }
                                else { res += '5'; j += 5; }
                            } else {
                                if (s[j+4] == '0') {
                                    if (s[j+5] == '0') { res += '6'; j += 6; }
                                    else { res += '7'; j += 6; }
                                } else {
                                    if (s[j+5] == '0') { res += '8'; j += 6; }
                                    else { res += '9'; j += 6; }
                                }
                            }
                        }
                    }
                }
            }
            cout << res.substr(0, 4) << "," << res.substr(4) << "\n";
        }
    }
    return 0;
}
