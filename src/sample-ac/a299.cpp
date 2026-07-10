#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    bool first = true;
    while (cin >> n) {
        vector<int> a(n), b(n), g(n), k(n);
        for (int i = 0; i < n; i++) cin >> a[i] >> b[i] >> g[i] >> k[i];
        int x, y;
        cin >> x >> y;

        int ans = -1;
        for (int i = n - 1; i >= 0; i--) {
            if (x >= a[i] && x <= a[i] + g[i] &&
                y >= b[i] && y <= b[i] + k[i]) {
                ans = i + 1;
                break;
            }
        }
        if (!first) cout << "\n";
        first = false;
        cout << ans << "\n";
    }
    return 0;
}
