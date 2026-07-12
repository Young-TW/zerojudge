#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unsigned long long H;
    while (cin >> H) {
        unsigned long long target = H - 1;
        unsigned long long low = 1, high = 65536;
        unsigned long long ans = 0;
        
        while (low <= high) {
            unsigned long long mid = low + (high - low) / 2;
            unsigned long long p = mid * (mid + 1) * (mid + 2) * (mid + 3);
            
            if (p == target) {
                ans = mid;
                break;
            } else if (p < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        
        cout << ans << " " << ans + 1 << " " << ans + 2 << " " << ans + 3 << "\n";
    }
    
    return 0;
}
