#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        if (n == 0) {
            cout << 0 << "\n";
            continue;
        }
        
        vector<int> h(n);
        for (int i = 0; i < n; ++i) {
            cin >> h[i];
        }
        
        int ans = 1;
        int state = 0; // 0: initial, 1: up, -1: down
        
        for (int i = 1; i < n; ++i) {
            if (h[i] > h[i - 1]) {
                if (state != 1) {
                    ans++;
                    state = 1;
                }
            } else if (h[i] < h[i - 1]) {
                if (state != -1) {
                    ans++;
                    state = -1;
                }
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
