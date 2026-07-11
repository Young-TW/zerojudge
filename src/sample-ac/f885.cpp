#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long a, x;
        cin >> a >> x;

        long long n = a;
        long long sum = 0;
        while (sum < x) {
            sum += n;
            if (sum >= x) break;
            n++;
        }

        long long low = a, high = 2e9 + 10;
        long long ans = high;
        while (low <= high) {
            long long mid = (low + high) / 2;
            long long total = (mid - a + 1) * (a + mid) / 2;
            if (total >= x) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
