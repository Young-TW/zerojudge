#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long c[5], p[5];
    while (cin >> c[0] >> c[1] >> c[2] >> c[3] >> c[4] >> p[0] >> p[1] >> p[2] >> p[3] >> p[4]) {
        long long ans = 0;
        for (int i = 0; i < 5; ++i) {
            if (p[i] > 0) {
                ans += c[i] % p[i];
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
