#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    int case_num = 1;
    
    while (cin >> n && n) {
        vector<int> y(n), a(n), b(n);
        int max_a = 0;
        
        for (int i = 0; i < n; ++i) {
            cin >> y[i] >> a[i] >> b[i];
            if (a[i] > max_a) {
                max_a = a[i];
            }
        }
        
        int ans = -1;
        for (int z = max_a; z < 10000; ++z) {
            bool ok = true;
            for (int i = 0; i < n; ++i) {
                if (z < y[i] || (z - y[i]) % (b[i] - a[i]) != 0) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                ans = z;
                break;
            }
        }
        
        cout << "Case #" << case_num << ":\n";
        if (ans != -1) {
            cout << "The actual year is " << ans << ".\n";
        } else {
            cout << "Unknown bugs detected.\n";
        }
        cout << "\n";
        case_num++;
    }
    
    return 0;
}
