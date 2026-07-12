#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        unsigned long long ans;
        if (n <= 9) {
            ans = (1ULL << (n + 2)) - 2;
        } else {
            ans = (1ULL << (n - 8)) * 1023ULL;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
