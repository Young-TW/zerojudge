#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (cin >> s) {
        while (s.size() > 1) {
            string t = to_string((s[0] - '0') * (s[1] - '0'));
            if (s.size() == 3) {
                t += to_string((s[1] - '0') * (s[2] - '0'));
            } else if (s.size() == 4) {
                if (s[2] == '0') t += s[3];
                else t += to_string((s[2] - '0') * (s[3] - '0'));
            }
            size_t p = t.find_first_not_of('0');
            s = (p == string::npos) ? "0" : t.substr(p);
        }
        cout << s << '\n';
    }
    return 0;
}
