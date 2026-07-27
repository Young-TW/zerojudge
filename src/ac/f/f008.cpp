#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        if (n == 1) {
            cout << "1\n0 0 1\n";
        } else if (n == 2) {
            cout << "3\n";
            cout << "0 0 1\n";
            cout << "0 0 2\n";
            cout << "1 1 1\n";
        } else {
            int m = 2 * n - 2;
            cout << m << '\n';
            cout << "0 0 " << n - 1 << '\n';
            cout << "0 1 " << n - 1 << '\n';
            cout << "1 0 " << n - 1 << '\n';
            cout << "1 1 " << n - 1 << '\n';
            for (int k = 2; k <= n - 2; ++k) {
                cout << "0 " << k << " " << n - k << '\n';
                cout << k << " 0 " << n - k << '\n';
            }
        }
    }
    return 0;
}
