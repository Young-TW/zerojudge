#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string mul2(const string& s) {
    string res = "";
    int carry = 0;
    for (int i = s.length() - 1; i >= 0; --i) {
        int val = (s[i] - '0') * 2 + carry;
        carry = val / 10;
        res += (val % 10) + '0';
    }
    if (carry) {
        res += carry + '0';
    }
    reverse(res.begin(), res.end());
    return res;
}

bool isLess(const string& a, const string& b) {
    if (a.length() != b.length()) {
        return a.length() < b.length();
    }
    return a < b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string n;
    while (cin >> n) {
        while (n.length() > 1 && n[0] == '0') {
            n.erase(0, 1);
        }
        
        string p = "1";
        int k = 0;
        while (isLess(p, n)) {
            p = mul2(p);
            k++;
        }
        cout << k << "\n";
    }
    
    return 0;
}
