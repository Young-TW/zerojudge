#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long c, w;
    while (cin >> c >> w) {
        long long ans = min(w, max(0LL, c + w - 2) / 11);
        cout << ans << "\n";
    }
    
    return 0;
}
