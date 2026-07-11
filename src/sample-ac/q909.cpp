#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            long long n, m;
            cin >> n >> m;
            long long ans;
            if (n == m) {
                long long k = (n + 1) / 2;
                ans = k * (k + 1) / 2;
            } else {
                long long kn = (n + 1) / 2;
                long long km = (m + 1) / 2;
                ans = kn * km;
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
