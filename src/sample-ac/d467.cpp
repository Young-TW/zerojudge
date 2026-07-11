#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long a;
    int n, i, k;
    
    while (cin >> a >> n >> i >> k) {
        vector<long long> res;
        res.reserve(7000);
        res.push_back(1);
        
        const long long BASE = 1000000000LL;
        
        for (int p = 0; p < n; ++p) {
            long long carry = 0;
            int len = res.size();
            for (int j = 0; j < len; ++j) {
                long long prod = res[j] * a + carry;
                res[j] = prod % BASE;
                carry = prod / BASE;
            }
            while (carry > 0) {
                res.push_back(carry % BASE);
                carry /= BASE;
            }
        }
        
        string s;
        s.reserve(70000);
        s = to_string(res.back());
        for (int j = (int)res.size() - 2; j >= 0; --j) {
            string part = to_string(res[j]);
            s.append(9 - part.length(), '0');
            s.append(part);
        }
        
        int L = s.length();
        if (i > L) {
            cout << "\n";
        } else {
            int start = i - 1;
            int len = min(k, L - start);
            cout << s.substr(start, len) << "\n";
        }
    }
    
    return 0;
}
