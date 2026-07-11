#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using ll = long long;
using i128 = __int128;

i128 extgcd(i128 a, i128 b, i128 &x, i128 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i128 x1, y1;
    i128 gcd = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line1, line2;
    while (getline(cin, line1)) {
        if (!line1.empty() && line1.back() == '\r') line1.pop_back();
        if (line1.empty()) continue;
        if (!getline(cin, line2)) break;
        if (!line2.empty() && line2.back() == '\r') line2.pop_back();
        
        stringstream ss1(line1);
        stringstream ss2(line2);
        
        vector<ll> p, k;
        ll val;
        while (ss1 >> val) p.push_back(val);
        while (ss2 >> val) k.push_back(val);
        
        int n = p.size();
        if (n == 0) continue;
        
        i128 M = k[0] % p[0];
        i128 P = p[0];
        
        for (int i = 1; i < n; ++i) {
            i128 a = P;
            i128 b = p[i];
            i128 c = ((k[i] % p[i]) - (M % p[i]) + p[i]) % p[i];
            
            i128 x, y;
            extgcd(a, b, x, y);
            i128 mod = b;
            i128 x0 = (x * c % mod + mod) % mod;
            
            M = M + x0 * P;
            P = P * b;
            M = (M % P + P) % P;
        }
        
        ll max_p = 0;
        for (int i = 0; i < n; ++i) {
            if (p[i] > max_p) max_p = p[i];
        }
        
        ll ans = (ll)M;
        if (ans <= max_p) {
            ans += (ll)P;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
