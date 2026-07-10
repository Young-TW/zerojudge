#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

static int hexVal(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}
static char hexChar(int v) { return (char)(v < 10 ? '0' + v : 'A' + (v - 10)); }

string octToHex(const string &s) {
    string bin;
    bin.reserve(s.size() * 3);
    for (char c : s) {
        int d = c - '0';
        for (int i = 2; i >= 0; i--) bin += (char)(((d >> i) & 1) + '0');
    }
    while (bin.size() % 4 != 0) bin = "0" + bin;
    string hex;
    hex.reserve(bin.size() / 4);
    for (size_t i = 0; i < bin.size(); i += 4) {
        int val = 0;
        for (int j = 0; j < 4; j++) val = val * 2 + (bin[i + j] - '0');
        hex += hexChar(val);
    }
    size_t pos = hex.find_first_not_of('0');
    if (pos == string::npos) return "0";
    return hex.substr(pos);
}

string addHex(const string &a, const string &b) {
    string res;
    int carry = 0;
    int i = (int)a.size() - 1, j = (int)b.size() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += hexVal(a[i--]);
        if (j >= 0) sum += hexVal(b[j--]);
        res += hexChar(sum % 16);
        carry = sum / 16;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    if (!(cin >> N)) return 0;
    while (N--) {
        string a, b;
        cin >> a >> b;
        string ha = octToHex(a);
        string hb = octToHex(b);
        cout << addHex(ha, hb) << "\n";
    }
    return 0;
}
