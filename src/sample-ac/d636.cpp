#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, b;
    const long long mod = 10007;
    
    while (cin >> a >> b) {
        long long res = 1;
        a %= mod;
        while (b > 0) {
            if (b & 1) {
                res = (res * a) % mod;
            }
            a = (a * a) % mod;
            b >>= 1;
        }
        cout << res << "\n";
    }
    
    return 0;
}
