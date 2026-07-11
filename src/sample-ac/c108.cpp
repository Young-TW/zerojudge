#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int ans[14];
    for (int k = 1; k <= 13; ++k) {
        int n = 2 * k;
        for (int m = k + 1; ; ++m) {
            int start = 0;
            bool ok = true;
            for (int i = 0; i < k; ++i) {
                start = (start + m - 1) % (n - i);
                if (start < k) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                ans[k] = m;
                break;
            }
        }
    }
    
    int k;
    while (cin >> k && k) {
        cout << ans[k] << "\n";
    }
    
    return 0;
}
