#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

static int toVal(char c) { return c - 'A'; }
static char toChar(int v) { return static_cast<char>('A' + v); }

static long long gToNum(const string& s) {
    long long v = 0;
    for (string::size_type i = 0; i < s.size(); ++i)
        v = v * 26 + (s[i] - 'A');
    return v;
}

static string addG(const string& a, const string& b) {
    string::size_type la = a.size(), lb = b.size();
    string::size_type l = max(la, lb);
    string ra(l, 'A'), rb(l, 'A');
    for (string::size_type i = 0; i < la; ++i) ra[l - 1 - i] = a[la - 1 - i];
    for (string::size_type i = 0; i < lb; ++i) rb[l - 1 - i] = b[lb - 1 - i];

    string res(l + 1, 'A');
    int carry = 0;
    for (string::size_type i = l; i-- > 0; ) {
        int s = toVal(ra[i]) + toVal(rb[i]) + carry;
        carry = s / 26;
        res[i + 1] = toChar(s % 26);
    }
    res[0] = toChar(carry);
    if (res.size() > 1 && res[0] == 'A') res.erase(res.begin());
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    while (cin >> line) {
        long long n = gToNum(line);
        if (n == 0) break;
        string a, b;
        cin >> a >> b;
        cout << addG(a, b) << "\n";
    }
    return 0;
}
