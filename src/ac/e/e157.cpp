#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    long long a, b, t;
    cin >> a >> b >> t;
    for (int i = 0; i < n; ++i) {
        long long v;
        int degree;
        cin >> v >> degree;
        long long ans = 2 * a * t;
        cout << ans << "\n";
    }
    return 0;
}
