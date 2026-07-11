#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        if (n == 21) {
            cout << 1 << "\n";
        } else {
            int k = 2;
            if (n >= 12) {
                k = (n - 12 + 13) / 14;
                if (k < 2) k = 2;
            }
            if (14 * k + 2 <= n && n <= 14 * k + 12) {
                cout << k << "\n";
            } else {
                cout << -1 << "\n";
            }
        }
    }
    return 0;
}
