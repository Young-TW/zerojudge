#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    while (cin >> n) {
        long long ans = 0;
        long long temp = n;
        while (temp > 0) {
            int k = 63 - __builtin_clzll(temp);
            long long p = 1LL << k;
            ans += (long long)k * (p / 2);
            ans += (temp - p + 1);
            temp -= p;
        }
        cout << ans % 1000000000 << "\n";
    }
    
    return 0;
}
