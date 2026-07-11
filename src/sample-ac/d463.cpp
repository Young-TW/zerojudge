#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unsigned long long N;
    while (cin >> N) {
        unsigned long long l = 1, r = 2642244;
        unsigned long long ans = 0;
        while (l <= r) {
            unsigned long long mid = l + (r - l) / 2;
            unsigned long long cube = mid * mid * mid;
            if (cube == N) {
                ans = mid;
                break;
            } else if (cube < N) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
