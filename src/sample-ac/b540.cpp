#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a1, a2, a3, a4, a5, a6;
    while (cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6) {
        long long S = a1 + a2 + a3;
        long long ans = S * S - a1 * a1 - a3 * a3 - a5 * a5;
        cout << ans << '\n';
    }
    
    return 0;
}
