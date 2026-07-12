#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int a, b;
    int ans = 0;
    
    for (int i = 0; i < 5; ++i) {
        if (cin >> a >> b) {
            if (b > 0) {
                ans += a % b;
            }
        }
    }
    
    cout << ans << "\n";
    return 0;
}
