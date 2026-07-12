#include <iostream>
#include <string>

using namespace std;

string strip(string s) {
    int pos = 0;
    while (pos < (int)s.size() - 1 && s[pos] == '0') pos++;
    return s.substr(pos);
}

int compare(const string &a, const string &b) {
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

string sub(string a, string b) {
    while (b.size() < a.size()) b = "0" + b;
    string res = "";
    int carry = 0;
    for (int i = a.size() - 1; i >= 0; --i) {
        int x = a[i] - '0';
        int y = b[i] - '0';
        int diff = x - y - carry;
        if (diff < 0) {
            diff += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        res = (char)('0' + diff) + res;
    }
    return strip(res);
}

string divmod(string a, string b, string &rem) {
    string q = "";
    rem = "";
    for (int i = 0; i < (int)a.size(); ++i) {
        rem += a[i];
        rem = strip(rem);
        int cnt = 0;
        while (compare(rem, b) >= 0) {
            rem = sub(rem, b);
            cnt++;
        }
        q += (char)('0' + cnt);
    }
    return strip(q);
}

string gcd(string a, string b) {
    a = strip(a);
    b = strip(b);
    while (b != "0") {
        string rem;
        divmod(a, b, rem);
        a = b;
        b = rem;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    while (cin >> N) {
        while (N--) {
            string p, slash, q;
            cin >> p >> slash >> q;
            string g = gcd(p, q);
            string rem;
            string p2 = divmod(p, g, rem);
            string q2 = divmod(q, g, rem);
            cout << p2 << " / " << q2 << "\n";
        }
    }
    return 0;
}
