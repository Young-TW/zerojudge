#include <bits/stdc++.h>
using namespace std;

// convert a decimal string (e.g. "1234.56") to cents (integer)
long long toCents(const string &s) {
    bool neg = false;
    size_t i = 0;
    if (i < s.size() && (s[i] == '+' || s[i] == '-')) {
        if (s[i] == '-') neg = true;
        ++i;
    }
    long long dollars = 0;
    while (i < s.size() && isdigit(static_cast<unsigned char>(s[i]))) {
        dollars = dollars * 10 + (s[i] - '0');
        ++i;
    }
    long long cents = 0;
    if (i < s.size() && s[i] == '.') {
        ++i;
        if (i < s.size() && isdigit(static_cast<unsigned char>(s[i]))) {
            cents = (s[i] - '0') * 10;
            ++i;
        }
        if (i < s.size() && isdigit(static_cast<unsigned char>(s[i]))) {
            cents += (s[i] - '0');
        }
    }
    long long total = dollars * 100 + cents;
    return neg ? -total : total;
}

// insert commas into a decimal integer string
string addCommas(const string &num) {
    string res;
    int cnt = 0;
    for (int i = static_cast<int>(num.size()) - 1; i >= 0; --i) {
        res.push_back(num[i]);
        ++cnt;
        if (cnt % 3 == 0 && i != 0)
            res.push_back(',');
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    if (!(cin >> N)) return 0;
    for (int dataset = 1; dataset <= N; ++dataset) {
        long long sumCents = 0;
        for (int i = 0; i < 12; ++i) {
            string s;
            cin >> s;
            sumCents += toCents(s);
        }
        // average rounded half up
        long long avgCents = (sumCents + 6) / 12;   // 6 = 12/2
        
        long long intPart = avgCents / 100;
        int fracPart = static_cast<int>(avgCents % 100);
        
        string intStr = to_string(intPart);
        string formattedInt = addCommas(intStr);
        
        cout << dataset << " $" << formattedInt << '.'
             << setw(2) << setfill('0') << fracPart << "\n";
    }
    return 0;
}
