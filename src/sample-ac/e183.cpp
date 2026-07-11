#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n && n) {
        int L = 1;
        while (L * 2 <= n) {
            L *= 2;
        }
        int ans = 2 * (n - L);
        if (ans == 0) {
            ans = n;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
