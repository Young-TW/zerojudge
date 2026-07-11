#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <cctype>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string line;
    while (getline(cin, line)) {
        string str;
        for (char ch : line) {
            if (!isspace((unsigned char)ch)) {
                str += ch;
            }
        }
        if (str.empty()) continue;
        
        long long a = 0, b = 0;
        size_t ipos = str.find('i');
        if (ipos == string::npos) {
            a = stoll(str);
        } else {
            int split = -1;
            for (int i = 1; i < (int)str.size(); ++i) {
                if (str[i] == '+' || str[i] == '-') {
                    split = i;
                    break;
                }
            }
            if (split != -1) {
                a = stoll(str.substr(0, split));
                string bs = str.substr(split, ipos - split);
                if (bs == "+" || bs == "-") {
                    b = (bs == "+") ? 1 : -1;
                } else {
                    b = stoll(bs);
                }
            } else {
                a = 0;
                string bs = str.substr(0, ipos);
                if (bs.empty() || bs == "+") {
                    b = 1;
                } else if (bs == "-") {
                    b = -1;
                } else {
                    b = stoll(bs);
                }
            }
        }
        long double ans = sqrt((long double)a * a + (long double)b * b);
        cout << fixed << setprecision(3) << ans << "\n";
    }
    return 0;
}
