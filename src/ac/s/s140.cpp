#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, a, b;
    while (cin >> n >> a >> b) {
        long long low = 0, high = 200000000000000LL;
        while (low < high) {
            long long mid = low + (high - low) / 2;
            if (mid / a + mid / b >= n) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        cout << low % 1000007 << "\n";
    }
    
    return 0;
}
