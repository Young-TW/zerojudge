#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        while (T--) {
            long long k;
            cin >> k;
            if (k < 0) k = -k;
            
            long long low = 1, high = 2000000000;
            while (low < high) {
                long long mid = low + (high - low) / 2;
                if (mid * (mid + 1) / 2 >= k) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            
            for (long long n = low; ; n++) {
                long long s = n * (n + 1) / 2;
                if (s >= k && s % 2 == k % 2) {
                    cout << n << "\n";
                    break;
                }
            }
        }
    }
    return 0;
}
