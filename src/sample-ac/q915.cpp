#include <iostream>

using namespace std;

unsigned long long isqrt(unsigned long long x) {
    if (x <= 1) return x;
    unsigned long long l = 1, r = x, ans = 0;
    while (l <= r) {
        unsigned long long mid = l + (r - l) / 2;
        if (mid <= x / mid) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            long long n_signed;
            if (!(cin >> n_signed)) break;
            if (n_signed <= 0) {
                cout << "NIE\n";
                continue;
            }
            unsigned long long n = n_signed;
            unsigned long long x = 8 * n + 1;
            unsigned long long s = isqrt(x);
            if (s * s == x && (s - 1) % 2 == 0) {
                cout << "TAK\n";
            } else {
                cout << "NIE\n";
            }
        }
    }
    return 0;
}
