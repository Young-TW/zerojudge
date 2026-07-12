#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string trim(string s) {
    size_t pos = 0;
    while (pos + 1 < s.length() && s[pos] == '0') pos++;
    if (pos > 0) s.erase(0, pos);
    return s;
}

string div9(string s, int &rem) {
    string q = "";
    q.reserve(s.length());
    rem = 0;
    for (char c : s) {
        int cur = rem * 10 + (c - '0');
        q += (char)(cur / 9 + '0');
        rem = cur % 9;
    }
    size_t pos = 0;
    while (pos + 1 < q.length() && q[pos] == '0') pos++;
    if (pos > 0) q.erase(0, pos);
    return q;
}

string T_op(string s) {
    s = trim(s);
    if (s == "0") return "0";
    string res = "";
    while (s != "0") {
        int rem;
        s = div9(s, rem);
        if (rem >= 4) rem++;
        res += (char)(rem + '0');
    }
    reverse(res.begin(), res.end());
    return res;
}

string mul9_add(string s, int d) {
    int carry = d;
    for (int i = (int)s.length() - 1; i >= 0; i--) {
        int cur = (s[i] - '0') * 9 + carry;
        s[i] = (char)(cur % 10 + '0');
        carry = cur / 10;
    }
    if (carry) {
        s = to_string(carry) + s;
    }
    return s;
}

string F_op(string s) {
    s = trim(s);
    string res = "0";
    for (char c : s) {
        int d = c - '0';
        if (d > 4) d--;
        res = mul9_add(res, d);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    char type;
    string n;
    while (cin >> type >> n) {
        if (type == 'T') {
            cout << T_op(n) << "\n";
        } else {
            cout << F_op(n) << "\n";
        }
    }
    return 0;
}
