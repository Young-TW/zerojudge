#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int a, b, c, d;
    while (cin >> a >> b >> c >> d) {
        int ans = d;
        ans += c;
        a = max(0, a - 37 * c);
        
        ans += b / 8;
        int rem_2 = b % 8;
        if (rem_2 > 0) {
            ans += 1;
            a = max(0, a - (8 - rem_2) * 8);
        }
        
        ans += (a + 63) / 64;
        cout << ans << "\n";
    }
    return 0;
}
