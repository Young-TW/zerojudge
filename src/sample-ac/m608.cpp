#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s) {
        long long p = 0, q = 1;
        size_t dot_pos = s.find('.');
        if (dot_pos == string::npos) {
            for (size_t i = 0; i < s.length(); ++i) {
                if (isdigit(s[i])) {
                    p = p * 10 + (s[i] - '0');
                }
            }
            q = 1;
        } else {
            for (size_t i = 0; i < dot_pos; ++i) {
                if (isdigit(s[i])) {
                    p = p * 10 + (s[i] - '0');
                }
            }
            for (size_t i = dot_pos + 1; i < s.length(); ++i) {
                if (isdigit(s[i])) {
                    p = p * 10 + (s[i] - '0');
                    q *= 10;
                }
            }
        }
        
        long long g = gcd(p, q);
        p /= g;
        q /= g;
        
        vector<long long> ans;
        while (q != 0) {
            ans.push_back(p / q);
            p %= q;
            swap(p, q);
        }
        
        for (size_t i = 0; i < ans.size(); ++i) {
            if (i == 0) {
                cout << ans[i];
            } else if (i == 1) {
                cout << ";" << ans[i];
            } else {
                cout << "," << ans[i];
            }
        }
        cout << "\n";
    }
    
    return 0;
}
