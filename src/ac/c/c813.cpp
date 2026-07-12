#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n && n != 0) {
        long long ans = n % 9;
        if (ans == 0) {
            ans = 9;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
