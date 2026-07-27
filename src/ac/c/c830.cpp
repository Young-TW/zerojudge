#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<string> inputs;
    string s;
    size_t maxFrac = 0;
    while (cin >> s) {
        inputs.push_back(s);
        size_t dot = s.find('.');
        if (dot != string::npos) {
            size_t len = s.size() - dot - 1;
            if (len > maxFrac) maxFrac = len;
        }
    }
    if (inputs.empty()) return 0;          // no data
    
    vector<int> sum;                       // least significant digit first, base 7
    
    for (const string &orig : inputs) {
        string intPart, fracPart;
        size_t dot = orig.find('.');
        if (dot == string::npos) {
            intPart = orig;
            fracPart = "";
        } else {
            intPart = orig.substr(0, dot);
            fracPart = orig.substr(dot + 1);
        }
        // pad fractional part on the right
        while (fracPart.size() < maxFrac) fracPart.push_back('0');
        string whole = intPart + fracPart; // base‑7 integer representation
        
        // add whole to sum (base 7)
        int carry = 0;
        size_t n = whole.size();
        size_t i = 0;
        for (; i < n || i < sum.size(); ++i) {
            int d = 0;
            if (i < n) d = whole[n - 1 - i] - '0';
            int cur = (i < sum.size() ? sum[i] : 0) + d + carry;
            if (i < sum.size())
                sum[i] = cur % 7;
            else
                sum.push_back(cur % 7);
            carry = cur / 7;
        }
        while (carry) {
            sum.push_back(carry % 7);
            carry /= 7;
        }
    }
    
    // ensure at least maxFrac fractional digits
    while (sum.size() < maxFrac) sum.push_back(0);
    
    // build output string
    string out;
    for (int i = (int)sum.size() - 1; i >= 0; --i)
        out.push_back(char('0' + sum[i]));
    
    if (maxFrac > 0) {
        size_t pos = out.size() - maxFrac;
        out.insert(out.begin() + pos, '.');
    }
    
    // remove leading zeros before dot (keep at least one digit)
    while (out.size() > 1 && out[0] == '0' && out[1] != '.') {
        out.erase(out.begin());
    }
    
    // remove trailing zeros after dot
    size_t dotPos = out.find('.');
    if (dotPos != string::npos) {
        while (!out.empty() && out.back() == '0')
            out.pop_back();
        if (!out.empty() && out.back() == '.')
            out.pop_back();
    }
    
    if (out.empty()) out = "0";
    cout << out << '\n';
    return 0;
}
