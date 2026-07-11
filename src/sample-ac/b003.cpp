#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long k;
    while (cin >> k) {
        long long abs_k = k < 0 ? -k : k;
        long long low = 1, high = 100000;
        while (low < high) {
            long long mid = low + (high - low) / 2;
            if (mid * (mid + 1) / 2 >= abs_k) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        long long n = low;
        while ((n * (n + 1) / 2 - k) % 2 != 0) {
            n++;
        }
        cout << n << "\n";
    }
    return 0;
}
