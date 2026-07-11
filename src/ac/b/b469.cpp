#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        long long ans = 0;
        int prev = 0;
        for (int i = 0; i < n; ++i) {
            int h;
            cin >> h;
            if (h > prev) {
                ans += h - prev;
            }
            prev = h;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
