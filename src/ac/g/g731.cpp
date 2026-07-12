#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cctype>

using namespace std;

long long gcd(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        vector<pair<long long, long long>> fracs;
        long long num = 0, den = 0;
        bool in_num = true;
        bool neg = false;
        bool has_frac = false;
        
        for (char c : line) {
            if (isspace(static_cast<unsigned char>(c))) continue;
            if (c == '+') {
                if (neg) num = -num;
                fracs.push_back({num, den});
                num = 0; den = 0; in_num = true; neg = false; has_frac = true;
            } else if (c == '/') {
                in_num = false;
            } else if (c == '-') {
                neg = !neg;
            } else {
                if (in_num) num = num * 10 + (c - '0');
                else den = den * 10 + (c - '0');
                has_frac = true;
            }
        }
        if (has_frac) {
            if (neg) num = -num;
            fracs.push_back({num, den});
        }
        
        if (fracs.size() <= 1) continue;
        
        long long cur_num = fracs[0].first;
        long long cur_den = fracs[0].second;
        
        for (size_t i = 1; i < fracs.size(); ++i) {
            long long a = cur_num, b = cur_den;
            long long c = fracs[i].first, d = fracs[i].second;
            
            long long g1 = gcd(a, b);
            if (g1 != 0) { a /= g1; b /= g1; }
            long long g2 = gcd(c, d);
            if (g2 != 0) { c /= g2; d /= g2; }
            
            long long g = gcd(b, d);
            long long l = b / g * d;
            long long new_num = a * (l / b) + c * (l / d);
            long long new_den = l;
            
            long long g3 = gcd(new_num, new_den);
            if (g3 == 0) g3 = 1;
            new_num /= g3;
            new_den /= g3;
            
            if (new_den < 0) {
                new_num = -new_num;
                new_den = -new_den;
            }
            
            cur_num = new_num;
            cur_den = new_den;
            
            cout << "=" << cur_num << "/" << cur_den;
            for (size_t j = i + 1; j < fracs.size(); ++j) {
                cout << "+" << fracs[j].first << "/" << fracs[j].second;
            }
            cout << "\n";
        }
    }
    
    return 0;
}
