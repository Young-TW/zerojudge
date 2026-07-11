#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        while (n--) {
            long long x;
            cin >> x;
            long long ans = x % 360;
            if (ans < 0) {
                ans += 360;
            }
            cout << ans << "\n";
        }
    }
    
    return 0;
}
