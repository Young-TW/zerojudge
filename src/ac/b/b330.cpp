#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    int x;
    while (cin >> n >> x) {
        long long ans = 0;
        long long base = 1;
        while (base <= n) {
            long long high = n / base / 10;
            long long cur = (n / base) % 10;
            long long low = n % base;
            
            if (x == 0) {
                if (cur > 0) {
                    ans += high * base;
                } else {
                    ans += (high - 1) * base + low + 1;
                }
            } else {
                if (cur > x) {
                    ans += (high + 1) * base;
                } else if (cur == x) {
                    ans += high * base + low + 1;
                } else {
                    ans += high * base;
                }
            }
            
            if (base > n / 10) break;
            base *= 10;
        }
        cout << ans << "\n";
    }
    return 0;
}
