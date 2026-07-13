#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    while (N--) {
        int X, a, b;
        cin >> X >> a >> b;
        int ans = -1;
        for (int y = 0; b * y <= X; y++) {
            int rem = X - b * y;
            if (rem % a == 0) {
                ans = rem / a + y;
                break;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
