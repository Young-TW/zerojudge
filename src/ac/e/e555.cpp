#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    unsigned long long S, D;
    while (cin >> S >> D) {
        unsigned long long low = 0, high = 3000000000ULL;
        while (low < high) {
            unsigned long long mid = low + (high - low + 1) / 2;
            unsigned long long val = mid * (2 * S + mid - 1);
            if (val <= 2 * (D - 1)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        cout << S + low << "\n";
    }
    
    return 0;
}
