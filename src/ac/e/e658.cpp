#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (cin >> T) {
        while (T--) {
            long long n;
            if (!(cin >> n)) break;
            
            long long low = 0, high = 2000000000LL;
            while (low <= high) {
                long long mid = low + (high - low) / 2;
                if (mid * (mid + 1) / 2 <= n) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            cout << high << "\n";
        }
    }
    return 0;
}
