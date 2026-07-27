#include <bits/stdc++.h>
using namespace std;

// remove leading zeros, keep at least one digit
static string normalize(const string &s) {
    size_t pos = s.find_first_not_of('0');
    if (pos == string::npos) return "0";
    return s.substr(pos);
}

// return true if a > b (both are normalized, no leading zeros)
static bool greaterStr(const string &a, const string &b) {
    if (a.size() != b.size()) return a.size() > b.size();
    return a > b; // lexicographic works when sizes equal
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int S;
    if (!(cin >> S)) return 0;
    while (S--) {
        string a, b, c;
        cin >> a >> b >> c;
        a = normalize(a);
        b = normalize(b);
        c = normalize(c);
        
        string ans = a;
        if (greaterStr(b, ans)) ans = b;
        if (greaterStr(c, ans)) ans = c;
        cout << ans << '\n';
    }
    return 0;
}
