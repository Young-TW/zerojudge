#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long X;
    while (cin >> X) {
        long long L = 0, R = 1000000;
        while (L < R) {
            long long mid = L + (R - L + 1) / 2;
            if (mid * (mid + 1) / 2 <= X) {
                L = mid;
            } else {
                R = mid - 1;
            }
        }
        cout << L << "\n";
    }
    
    return 0;
}
