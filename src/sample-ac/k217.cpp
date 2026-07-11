#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int n;
            cin >> n;
            if (n == 0) {
                cout << 0 << "\n";
                continue;
            }
            int prev;
            cin >> prev;
            int ans = 1;
            int last_sign = 0;
            for (int i = 1; i < n; ++i) {
                int curr;
                cin >> curr;
                if (curr < prev) {
                    if (last_sign != -1) {
                        ans++;
                        last_sign = -1;
                    }
                } else if (curr > prev) {
                    if (last_sign == -1) {
                        ans++;
                        last_sign = 1;
                    }
                }
                prev = curr;
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
