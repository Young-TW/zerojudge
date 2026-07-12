#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, x, y;
    while (cin >> a >> b >> x >> y) {
        int ans;
        if (a > b) {
            int diff = a - b;
            ans = x + (diff - 1) * min(y, 2 * x);
        } else {
            int diff = b - a;
            ans = x + diff * min(y, 2 * x);
        }
        cout << ans << "\n";
    }

    return 0;
}
