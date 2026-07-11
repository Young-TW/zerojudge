#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        int ans = -1;
        for (int d = 1; d <= 99; ++d) {
            int m;
            if (d < 10) {
                m = d * 10;
            } else {
                m = (d % 10) * 10 + (d / 10);
            }
            if (m >= 18 && m <= 99) {
                if (m + n == 2 * (d + n)) {
                    ans = d;
                    break;
                }
            }
        }
        if (ans != -1) {
            cout << ans << "\n";
        } else {
            cout << "no answer\n";
        }
    }
    
    return 0;
}
