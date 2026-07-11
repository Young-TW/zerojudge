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
        
        int a = 0, b = 0;
        char c;
        if (str.back() == 'i') {
            if (str == "i") {
                a = 0; b = 1;
            } else if (str == "-i") {
                a = 0; b = -1;
            } else if (str == "+i") {
                a = 0; b = 1;
            } else if (sscanf(str.c_str(), "%d%di", &a, &b) == 2) {
                // ok
            } else if (sscanf(str.c_str(), "%d%ci", &a, &c) == 2) {
                b = (c == '+' ? 1 : -1);
            }
        } else {
            sscanf(str.c_str(), "%d", &a);
        }
        double ans = sqrt((double)a * a + (double)b * b);
        cout << fixed << setprecision(3) << ans << "\n";
    }
    return 0;
}
