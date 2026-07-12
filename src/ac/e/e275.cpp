#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        long long c0 = 0, c1 = 0;
        for (int i = 0; i < n; ++i) {
            long long a;
            cin >> a;
            if (__builtin_popcountll(a) & 1) {
                c1++;
            } else {
                c0++;
            }
        }
        long long ans = c0 * (c0 - 1) / 2 + c1 * (c1 - 1) / 2;
        cout << ans << "\n";
    }
    
    return 0;
}
