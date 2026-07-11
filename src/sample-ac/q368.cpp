#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m, n;
    while (cin >> m >> n) {
        if (m == 0) {
            cout << n + 1 << "\n";
        } else if (m == 1) {
            cout << n + 2 << "\n";
        } else if (m == 2) {
            cout << 2 * n + 3 << "\n";
        } else if (m == 3) {
            cout << (1 << (n + 3)) - 3 << "\n";
        }
    }
    
    return 0;
}
