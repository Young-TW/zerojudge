#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long k;
    bool first = true;
    while (cin >> k) {
        if (!first) cout << "\n";
        first = false;
        long long ans = 0;
        long long n = 1;
        long long days = 0;
        while (days + n <= k) {
            ans += n * n;
            days += n;
            n++;
        }
        ans += (k - days) * n;
        cout << ans << "\n";
    }
    return 0;
}
