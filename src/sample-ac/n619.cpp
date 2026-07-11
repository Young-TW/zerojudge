#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        long long prev = 0;
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            long long x;
            cin >> x;
            if (x > prev) {
                ans += x - prev;
            }
            prev = x;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
