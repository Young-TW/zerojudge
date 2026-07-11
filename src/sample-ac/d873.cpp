#include <iostream>
#include <string>

using namespace std;

bool isGreaterThan(const string& s, const string& limit) {
    int start = 0;
    while (start < (int)s.size() - 1 && s[start] == '0') {
        start++;
    }
    string num = s.substr(start);
    
    if (num.size() > limit.size()) return true;
    if (num.size() < limit.size()) return false;
    return num > limit;
}

bool isZero(const string& s) {
    for (char c : s) {
        if (c != '0') return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s1, op, s2;
    string limit = "2147483647";
    
    while (cin >> s1 >> op >> s2) {
        cout << s1 << " " << op << " " << s2 << "\n";
        
        bool b1 = isGreaterThan(s1, limit);
        bool b2 = isGreaterThan(s2, limit);
        
        if (b1) cout << "first number too big\n";
        if (b2) cout << "second number too big\n";
        
        bool result_big = false;
        if (op == "+") {
            if (b1 || b2) {
                result_big = true;
            } else {
                unsigned long long n1 = 0, n2 = 0;
                for (char c : s1) n1 = n1 * 10 + (c - '0');
                for (char c : s2) n2 = n2 * 10 + (c - '0');
                if (n1 + n2 > 2147483647ULL) result_big = true;
            }
        } else if (op == "*") {
            if (isZero(s1) || isZero(s2)) {
                result_big = false;
            } else if (b1 || b2) {
                result_big = true;
            } else {
                unsigned long long n1 = 0, n2 = 0;
                for (char c : s1) n1 = n1 * 10 + (c - '0');
                for (char c : s2) n2 = n2 * 10 + (c - '0');
                if (n1 * n2 > 2147483647ULL) result_big = true;
            }
        }
        
        if (result_big) cout << "result too big\n";
    }
    
    return 0;
}
