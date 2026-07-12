#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool isNumber(const string& s) {
    if (s.empty()) return false;
    size_t start = 0;
    if (s[0] == '-' || s[0] == '+') {
        if (s.length() == 1) return false;
        start = 1;
    }
    for (size_t i = start; i < s.length(); ++i) {
        if (!isdigit(static_cast<unsigned char>(s[i]))) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (getline(cin, s)) {
        if (!s.empty() && s.back() == '\r') {
            s.pop_back();
        }
        if (s == "stop") break;
        if (isNumber(s)) {
            cout << "print(" << s << ")\n";
        } else {
            cout << "print(\"" << s << "\")\n";
        }
    }
    return 0;
}
