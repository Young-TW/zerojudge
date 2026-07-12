#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        long long ans = 0;
        while (n >= 5) {
            n /= 5;
            ans += n;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
