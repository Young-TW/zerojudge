#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        int ans = 0;
        while (n > 0) {
            ans++;
            n >>= 1;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
