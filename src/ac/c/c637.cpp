#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef __int128 lll;

lll extgcd(lll a, lll b, lll &x, lll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    lll x1, y1;
    lll d = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d;
}

lll mod_inverse(lll a, lll m) {
    lll x, y;
    extgcd(a, m, x, y);
    return (x % m + m) % m;
}

void print_int128(lll x) {
    if (x == 0) {
        cout << 0;
        return;
    }
    string s;
    while (x > 0) {
        s += (char)('0' + (int)(x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line1, line2;
    while (getline(cin, line1)) {
        if (line1.empty()) continue;
        while (getline(cin, line2) && line2.empty());
        if (line2.empty()) break;
        
        stringstream ss1(line1), ss2(line2);
        vector<lll> p, k;
        long long val;
        while (ss1 >> val) p.push_back(val);
        while (ss2 >> val) k.push_back(val);
        
        if (p.empty() || k.empty() || p.size() != k.size()) continue;
        
        lll P = 1;
        for (lll x : p) P *= x;
        
        lll ans = 0;
        for (size_t i = 0; i < p.size(); ++i) {
            lll Mi = P / p[i];
            lll yi = mod_inverse(Mi, p[i]);
            ans = (ans + (k[i] % P) * (Mi % P) % P * yi % P) % P;
        }
        
        lll max_p = *max_element(p.begin(), p.end());
        if (ans <= max_p) {
            ans += P;
        }
        print_int128(ans);
        cout << "\n";
    }
    return 0;
}
