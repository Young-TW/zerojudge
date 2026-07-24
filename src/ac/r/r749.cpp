#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        long long ans = n * (n + 1) / 2 * (n + 2);
        cout << ans << "\n";
    }
    
    return 0;
}
