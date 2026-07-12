#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cctype>
using namespace std;

bool isNumber(const string& s) {
    if (s.empty()) return false;
    size_t start = 0;
    if (s[0] == '-' || s[0] == '+') start = 1;
    if (start == s.size()) return false;
    for (size_t i = start; i < s.size(); i++) {
        if (!isdigit((unsigned char)s[i])) return false;
    }
    return true;
}

void outputPoly(int n, vector<long long>& coeffs) {
    bool first = true;
    for (int i = 0; i <= n; i++) {
        long long c = coeffs[i];
        if (c == 0) continue;
        int exp = n - i;
        
        if (first) {
            first = false;
            if (c < 0) {
                cout << "-";
                c = -c;
            }
        } else {
            if (c < 0) {
                cout << "-";
                c = -c;
            } else {
                cout << "+";
            }
        }
        
        if (exp == 0) {
            cout << c;
        } else if (exp == 1) {
            if (c == 1) cout << "x";
            else cout << c << "x";
        } else {
            if (c == 1) cout << "x^" << exp;
            else cout << c << "x^" << exp;
        }
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string token;
    while (cin >> token) {
        if (isNumber(token)) {
            int n = atoi(token.c_str());
            vector<long long> coeffs(n + 1);
            for (int i = 0; i <= n; i++) {
                cin >> coeffs[i];
            }
            outputPoly(n, coeffs);
        } else {
            // Chinese label: replace 入 (E5 85 A5) with 出 (E5 87 BA)
            size_t pos = token.find("\xE5\x85\xA5");
            if (pos != string::npos) {
                token.replace(pos, 3, "\xE5\x87\xBA");
            }
            cout << token;
            string num;
            cin >> num;
            cout << " " << num << "\n";
            cin >> token;
            int n = atoi(token.c_str());
            vector<long long> coeffs(n + 1);
            for (int i = 0; i <= n; i++) {
                cin >> coeffs[i];
            }
            outputPoly(n, coeffs);
        }
    }
    return 0;
}
