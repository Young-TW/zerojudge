#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int job, lv;
    while (cin >> job >> lv) {
        if (job == 0) {
            cout << 0 << "\n";
            continue;
        }
        
        int L1 = (job == 2) ? 8 : 10;
        if (lv < L1) {
            cout << 0 << "\n";
            continue;
        }
        
        int ans = 1 + 3 * (lv - L1);
        if (lv >= 30) ans += 1;
        if (lv >= 70) ans += 1;
        if (lv >= 120) ans += 3;
        
        cout << ans << "\n";
    }
    
    return 0;
}
