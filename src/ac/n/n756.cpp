#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        for (int i = 1; i <= T; ++i) {
            int R;
            cin >> R;
            cout << "Case " << i << ":\n";
            cout << -9 * R / 4 << " " << 3 * R / 2 << "\n";
            cout << 11 * R / 4 << " " << 3 * R / 2 << "\n";
            cout << 11 * R / 4 << " " << -3 * R / 2 << "\n";
            cout << -9 * R / 4 << " " << -3 * R / 2 << "\n";
        }
    }
    
    return 0;
}
