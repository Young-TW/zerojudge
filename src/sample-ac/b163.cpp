#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int p1, p2, p3;
    bool first = true;
    while (cin >> p1 >> p2 >> p3) {
        string s;
        cin >> s;
        string out;
        for (size_t i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == '-' && i > 0 && i + 1 < s.size()) {
                char l = s[i-1];
                char r = s[i+1];
                bool bothDigit = (l >= '0' && l <= '9') && (r >= '0' && r <= '9');
                bool bothLower = (l >= 'a' && l <= 'z') && (r >= 'a' && r <= 'z');
                if ((bothDigit || bothLower) && r > l) {
                    string fill;
                    for (char ch = l + 1; ch < r; ch++) {
                        char fc;
                        if (p1 == 3) {
                            fc = '*';
                        } else if (bothDigit) {
                            fc = ch;
                        } else {
                            if (p1 == 1) fc = ch;
                            else fc = ch - 'a' + 'A';
                        }
                        for (int k = 0; k < p2; k++) fill += fc;
                    }
                    if (p3 == 2) reverse(fill.begin(), fill.end());
                    out += fill;
                } else {
                    out += c;
                }
            } else {
                out += c;
            }
        }
        if (!first) cout << "\n";
        cout << out << "\n";
        first = false;
    }
    return 0;
}
