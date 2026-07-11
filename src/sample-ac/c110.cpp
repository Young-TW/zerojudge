#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int a[7];
    while (cin >> a[1] >> a[2] >> a[3] >> a[4] >> a[5] >> a[6]) {
        if (a[1] == 0 && a[2] == 0 && a[3] == 0 && a[4] == 0 && a[5] == 0 && a[6] == 0) {
            break;
        }
        
        int ans = 0;
        
        // 6x6
        ans += a[6];
        
        // 5x5
        ans += a[5];
        a[1] = max(0, a[1] - 11 * a[5]);
        
        // 4x4
        ans += a[4];
        int need2 = 5 * a[4];
        if (a[2] >= need2) {
            a[2] -= need2;
            need2 = 0;
        } else {
            need2 -= a[2];
            a[2] = 0;
        }
        a[1] = max(0, a[1] - 4 * need2);
        
        // 3x3
        ans += a[3] / 4;
        int rem3 = a[3] % 4;
        if (rem3 > 0) {
            ans++;
            if (rem3 == 1) {
                int n2 = 5;
                if (a[2] >= n2) {
                    a[2] -= n2;
                    n2 = 0;
                } else {
                    n2 -= a[2];
                    a[2] = 0;
                }
                a[1] = max(0, a[1] - (4 * n2 + 7));
            } else if (rem3 == 2) {
                int n2 = 3;
                if (a[2] >= n2) {
                    a[2] -= n2;
                    n2 = 0;
                } else {
                    n2 -= a[2];
                    a[2] = 0;
                }
                a[1] = max(0, a[1] - (4 * n2 + 6));
            } else if (rem3 == 3) {
                int n2 = 1;
                if (a[2] >= n2) {
                    a[2] -= n2;
                    n2 = 0;
                } else {
                    n2 -= a[2];
                    a[2] = 0;
                }
                a[1] = max(0, a[1] - (4 * n2 + 5));
            }
        }
        
        // 2x2
        ans += a[2] / 9;
        int rem2 = a[2] % 9;
        if (rem2 > 0) {
            ans++;
            a[1] = max(0, a[1] - (36 - 4 * rem2));
        }
        
        // 1x1
        ans += a[1] / 36;
        if (a[1] % 36 > 0) {
            ans++;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
